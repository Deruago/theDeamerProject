/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
/*
 * Part of the DeamerProject.
 * For more information go to: https://github.com/Deruago/theDeamerProject
 */

#include "Deamer/Parser/Generator/Antlr_Parser/Antlr_Parser.h"
#include "Deamer/File/Tool/Action/Builder.h"
#include "Deamer/File/Tool/LoadFilesystem.h"
#include "Deamer/Lexer/Type/Antlr/LexerDefinition.h"
#include "Deamer/Parser/Type/Antlr/ParserDefinition.h"
#include "Deamer/Template/Parser/Antlr/Import/ImportParserHeaderTemplate.h"
#include "Deamer/Template/Parser/Antlr/Import/ImportParserSourceTemplate.h"
#include "Deamer/Template/Parser/Antlr/Import/ListenerTranslateSourceTemplate.h"
#include "Deamer/Template/Parser/Antlr/Import/ListenerTranslateTemplate.h"
#include "Deamer/Template/Parser/Antlr/Runtime/Antlr4GeneratorCmakeTemplate.h"
#include "Deamer/Template/Parser/Antlr/Runtime/Antlr4RuntimeCmakeTemplate.h"
#include "Deamer/Template/Parser/Antlr/Runtime/ExternalAntlr4CppTemplate.h"
#include "Deamer/Template/Parser/Antlr/Runtime/FindAntlrTemplate.h"
#include <filesystem>

deamer::parser::generator::antlr_parser::Antlr_Parser::Antlr_Parser(const ReferenceType reference_)
	: Base(tool::type::Tool::Antlr_Parser),
	  reference(reference_),
	  name(reference.GetDefinition<language::type::definition::property::Type::Identity>()
			   .GetName()
			   ->value)
{
}

deamer::file::tool::Output deamer::parser::generator::antlr_parser::Antlr_Parser::Generate()
{
	if (reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsArgumentSet({tool::type::Tool::Antlr_Parser, "imported-grammar"}))
	{
		output.AddActionToExternal(externalAction());
		output.AddFileToExternal(ListenerTranslate());
		output.AddFileToExternal(ListenerTranslateSource());

		output.AddFileToInclude(ImportParserHeader());
		output.AddFileToLibrary(ImportParserSource());

		output.AddCMakeListsToExternal({externalCMakeLists()});

		output.AddDirectoryToExternal(CmakeDirectory());
	}
	else
	{
		const auto parserDefinitionGenerator =
			::deamer::parser::type::antlr::ParserDefinition(reference);
		const auto parserDefinition =
			file::tool::File(name + "Parser", "g4", parserDefinitionGenerator.Generate(),
							 file::tool::GenerationLevel::Always_regenerate);

		const auto lexerDefinitionGenerator =
			::deamer::lexer::type::antlr::LexerDefinition(reference);
		const auto lexerDefinition =
			file::tool::File(name + "Lexer", "g4", lexerDefinitionGenerator.Generate(),
							 file::tool::GenerationLevel::Always_regenerate);

		output.AddFileToExternal(lexerDefinition);

		output.AddActionToExternal(externalAction(lexerDefinition, parserDefinition, false));
		output.AddFileToExternal(parserDefinition);
		output.AddFileToExternal(lexerDefinition);

		output.AddFileToExternal(ListenerTranslate());
		output.AddFileToExternal(ListenerTranslateSource());

		output.AddFileToInclude(ImportParserHeader());
		output.AddFileToLibrary(ImportParserSource());

		output.AddCMakeListsToExternal({externalCMakeLists()});
		output.AddDirectoryToExternal(CmakeDirectory());
	}

	return output;
}

std::unique_ptr<deamer::file::tool::action::Action>
deamer::parser::generator::antlr_parser::Antlr_Parser::externalAction(
	std::optional<deamer::file::tool::File> lexiconFile,
	std::optional<deamer::file::tool::File> grammarFile, bool imported)
{
	auto projectDirectoryRelative = file::tool::LoadFilesystem::GetDeamerDir();
	if (!projectDirectoryRelative.has_value())
	{
		// This logic is dependent on the .deamer directory. There is no alternative for finding the
		// root project directory.
		return {};
	}
	file::tool::Directory out;
	auto fileSystem = file::tool::LoadFilesystem(out, projectDirectoryRelative.value());
	std::optional<file::tool::File> lexer = lexiconFile;
	std::optional<file::tool::File> parser = grammarFile;
	std::string antlrJarFile;
	fileSystem.Enter("extra").Enter("antlr4");
	fileSystem.DirectLoad();
	for (auto file : out.GetFiles())
	{
		if (file.GetFilename().find(name) == 0 && file.GetExtension() == "g4")
		{
			std::string lowered;
			for (auto character : file.GetFilename().substr(name.size()))
			{
				if (std::isalpha(character))
				{
					lowered += std::tolower(character);
				}
				else
				{
					lowered += character;
				}
			}
			if (lowered.find("lexer") != std::string::npos)
			{
				lexer = file;
			}
			else if (lowered.find("lexicon") != std::string::npos)
			{
				lexer = file;
			}
			else if (lowered.find("parser") != std::string::npos)
			{
				parser = file;
			}
			else if (lowered.find("grammar") != std::string::npos)
			{
				parser = file;
			}
			else
			{
				std::cout << "ANTLR_PARSER: Unknown file\n";
			}
		}
		else if (file.GetFilename().find("antlr") != std::string::npos &&
				 file.GetExtension() == "jar")
		{
			antlrJarFile = file.GetCompleteFileName();
		}
	}

	if (!lexer.has_value() || !parser.has_value())
	{
		// Invalid
		std::cout << "ANTLR_PARSER: Not all required files are available\n";
		return {};
	}

	if (imported)
	{
		output.AddFileToExternal(lexer.value());
		output.AddFileToExternal(parser.value());
	}

	auto antlrPath = std::filesystem::absolute(fileSystem.GetPath()).generic_string();
	auto jarFilePath = antlrPath + "/" + antlrJarFile;
	auto builder = file::tool::action::Builder();

	std::string atnDot = "";
	if (reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsArgumentSet({tool::type::Tool::Antlr_Parser, "enable_atn_dot"}))
	{
		atnDot = " -atn ";
	}

	builder.CopyFile(jarFilePath, "./")
		.CrossPlatformCommand("java -jar " + jarFilePath + atnDot + " -Dlanguage=Cpp " +
							  lexer->GetCompleteFileName() + " " + parser->GetCompleteFileName());

	return builder.GetAction();
}

std::string deamer::parser::generator::antlr_parser::Antlr_Parser::externalCMakeLists()
{
	std::string lexerSource = "./" + name + "Lexer.cpp";
	std::string parserSource = "./" + name + "Parser.cpp";
	std::string baseListenerSource = "./" + name + "ParserBaseListener.cpp";
	std::string listenerSource = "./" + name + "ParserListener.cpp";
	std::string listenerTranslateSource = "./ListenerTranslate.cpp";

	std::string lexerHeader = "./" + name + "Lexer.h";
	std::string parserHeader = "./" + name + "Parser.h";
	std::string baseListenerHeader = "./" + name + "ParserBaseListener.h";
	std::string listenerHeader = "./" + name + "ParserListener.h";
	std::string listenerTranslateHeader = "./ListenerTranslate.h";

	std::string sourceList = "set(source_files \"" + lexerSource + "\" \"" + parserSource +
							 "\" \"" + baseListenerSource + "\" \"" + listenerSource + "\" \"" +
							 listenerTranslateSource + "\")\n";

	std::string headerList = "set(header_files \"" + lexerHeader + "\" \"" + parserHeader +
							 "\" \"" + baseListenerHeader + "\" \"" + listenerHeader + "\" \"" +
							 listenerTranslateHeader + "\")\n";

	std::string lexerBuild = name + "_add_external_library(AntlrParser1 \"" + lexerSource +
							 "\" \"" + lexerHeader + "\")\n";
	std::string parserBuild = name + "_add_external_library(AntlrParser2 \"" + parserSource +
							  "\" \"" + parserHeader + "\")\n";
	std::string baseListenerBuild = name + "_add_external_library(AntlrParser3 \"" +
									baseListenerSource + "\" \"" + baseListenerHeader + "\")\n";
	std::string listenerBuild = name + "_add_external_library(AntlrParser4 \"" + listenerSource +
								"\" \"" + listenerHeader + "\")\n";
	std::string listenerTranslateBuild = name + "_add_external_library(AntlrParser5 \"" +
										 listenerTranslateSource + "\" \"" +
										 listenerTranslateHeader + "\")\n";

	std::string antlrSetup =
		"list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)\n"
		"add_definitions(-DANTLR4CPP_STATIC)\n"
		"set(ANTLR4_WITH_STATIC_CRT OFF)\n"
		"set(ANTLR4_TAG 4.11.1)\n"
		"set(ANTLR4_ZIP_REPOSITORY "
		"https://github.com/antlr/antlr4/archive/refs/tags/4.11.1.zip)\n"
		"include(ExternalAntlr4Cpp)\n"
		"include_directories(${ANTLR4_INCLUDE_DIRS})\n"
		"set(ANTLR_EXECUTABLE "
		"${PROJECT_SOURCE_DIR}/../extra/antlr4/antlr-4.11.1-complete.jar)\n"
		"find_package(ANTLR REQUIRED)\n"
		"\n"
		"include_directories(${ANTLR_Lexer_OUTPUT_DIR})\n"
		"include_directories(${ANTLR_Parser_OUTPUT_DIR})\n";

	std::string library =
		lexerBuild + parserBuild + baseListenerBuild + listenerBuild + listenerTranslateBuild;
	std::string staticLinkAntlr = "target_link_libraries(" + name + " PUBLIC antlr4_static)\n";

	return antlrSetup + sourceList + headerList + library + staticLinkAntlr;
}

deamer::file::tool::File deamer::parser::generator::antlr_parser::Antlr_Parser::ListenerTranslate()
{
	deamer::file::tool::File file("ListenerTranslate", "h");
	auto listenerTranslateTemplate = templates::antlr::parser::ListenerTranslateTemplate();
	listenerTranslateTemplate.language_name_->Set(name);

	for (const auto& nonTerminal :
		 reference.GetDefinition<language::type::definition::property::Type::Grammar>()
			 .NonTerminals)
	{
		if (nonTerminal->IsInlined())
		{
			// It is provided by DLDL and not by Antlr.
			continue;
		}

		listenerTranslateTemplate.nonterminal_->Set(nonTerminal->Name);

		for (std::size_t productionRuleId = 0;
			 productionRuleId < nonTerminal->ProductionRules.size(); productionRuleId++)
		{
			listenerTranslateTemplate.productionrule_id_->Set(std::to_string(productionRuleId));

			listenerTranslateTemplate.production_rule_enter_impl_->ExpandVariableField();
			listenerTranslateTemplate.production_rule_exit_impl_->ExpandVariableField();
		}
	}

	file.SetFileContent(listenerTranslateTemplate.GetOutput());
	return file;
}

deamer::file::tool::File deamer::parser::generator::antlr_parser::Antlr_Parser::ImportParserHeader()
{
	deamer::file::tool::File file("Parser", "h");
	auto importParserHeader = templates::antlr::parser::ImportParserHeaderTemplate();
	importParserHeader.language_name_->Set(name);

	file.SetFileContent(importParserHeader.GetOutput());
	return file;
}

deamer::file::tool::File deamer::parser::generator::antlr_parser::Antlr_Parser::ImportParserSource()
{
	deamer::file::tool::File file("Parser", "cpp");
	auto importParserSource = templates::antlr::parser::ImportParserSourceTemplate();
	importParserSource.language_name_->Set(name);

	file.SetFileContent(importParserSource.GetOutput());
	return file;
}

deamer::file::tool::File
deamer::parser::generator::antlr_parser::Antlr_Parser::ListenerTranslateSource()
{
	deamer::file::tool::File file("ListenerTranslate", "cpp");
	auto importParserSource = templates::antlr::parser::ListenerTranslateSourceTemplate();
	importParserSource.language_name_->Set(name);

	importParserSource.start_nonterminal_->Set(
		reference.GetDefinition<language::type::definition::property::Type::Grammar>()
			.NonTerminals[0]
			->Name);

	file.SetFileContent(importParserSource.GetOutput());
	return file;
}

deamer::file::tool::Directory
deamer::parser::generator::antlr_parser::Antlr_Parser::CmakeDirectory()
{
	deamer::file::tool::Directory cmake("cmake");
	cmake.AddFile(
		file::tool::File("ExternalAntlr4Cpp", "cmake",
						 templates::antlr::parser::ExternalAntlr4CppTemplate().GetOutput()));
	cmake.AddFile(file::tool::File("FindANTLR", "cmake",
								   templates::antlr::parser::FindAntlrTemplate().GetOutput()));
	cmake.AddFile(
		file::tool::File("antlr4-generator.cmake", "in",
						 templates::antlr::parser::Antlr4GeneratorCmakeTemplate().GetOutput()));
	cmake.AddFile(
		file::tool::File("antlr4-runtime.cmake", "in",
						 templates::antlr::parser::Antlr4RuntimeCmakeTemplate().GetOutput()));
	return cmake;
}
