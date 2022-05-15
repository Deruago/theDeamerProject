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

#include "Deamer/Lexer/Generator/Flex/Flex.h"
#include "Deamer/File/Tool/Action/Builder.h"
#include "Deamer/Template/Lexer/Flex/LexerDefinition/FlexDefinitionTemplate.h"
#include "Deamer/Template/Lexer/Flex/LexerHeader/FlexHeaderTemplate.h"

using namespace deamer::language::type::definition::property;

deamer::lexer::generator::flex::Flex::Flex(ReferenceType reference_)
	: Base(tool::type::Tool::Flex),
	  reference(reference_),
	  name(reference.GetDefinition<Type::Identity>().GetName()->value)
{
}

deamer::file::tool::Output deamer::lexer::generator::flex::Flex::Generate()
{
	const auto Identity = reference.GetDefinition<Type::Identity>();
	const auto Lexicon = reference.GetDefinition<Type::Lexicon>();
	file::tool::Output output("Flex");

	const std::string fileName = name + "_lexer";
	const file::tool::File flexFile(fileName, "l", GenerateFlexInputFile());
	const file::tool::File DeamerLexer_Header("Lexer", "h", GenerateDeamerLexer_HeaderFile());

	output.AddFileToExternal(flexFile);
	output.AddFileToInclude(DeamerLexer_Header);
	output.AddActionToExternal(externalAction());
	output.AddCMakeListsToExternal(externalCMakeLists());

	const bool debug = reference.GetDefinition<Type::Generation>().IsArgumentSet(
		{tool::type::Tool::Flex, "Debug"});
	if (debug)
	{
		output.AddFileToExternal(createDebugMain());
	}

	return output;
}

std::string deamer::lexer::generator::flex::Flex::GenerateFlexInputFile()
{
	auto flexDefinitionTemplate = templates::flex::FlexDefinitionTemplate();
	flexDefinitionTemplate.language_name_->Set(name);

	if (reference.GetDefinition<Type::Generation>().IsArgumentSet(
			{tool::type::Tool::Flex, "Debug"}))
	{
		flexDefinitionTemplate.optional_debug_action_->Set(flexDefinitionTemplate.debug_action_);
	}
	else
	{
		flexDefinitionTemplate.debug_action_->Set("");
	}

	if (reference.GetDefinition<Type::Generation>().IsIntegrationSet(
			{tool::type::Tool::Flex, tool::type::Tool::Bison}))
	{
		flexDefinitionTemplate.optional_flex_yylval_override_->Set("");
		flexDefinitionTemplate.optional_bison_integration_header_->Set(
			flexDefinitionTemplate.bison_integration_header_);
	}
	else
	{
		flexDefinitionTemplate.optional_flex_yylval_override_->Set(
			flexDefinitionTemplate.flex_yylval_override_);
		flexDefinitionTemplate.optional_bison_integration_header_->Set("");
	}

	if (reference.GetDefinition<Type::Generation>().GetOSTarget() ==
			file::tool::OSType::os_windows ||
		reference.GetDefinition<Type::Generation>().GetOSTarget() == file::tool::OSType::all)
	{
		flexDefinitionTemplate.optional_option_interactive_->Set(
			flexDefinitionTemplate.option_interactive_);
		flexDefinitionTemplate.optional_option_unistd_->Set(flexDefinitionTemplate.option_unistd_);
	}

	std::size_t index = 1;
	for (const auto* terminal : reference.GetDefinition<Type::Lexicon>().Terminals)
	{
		flexDefinitionTemplate.node_name_->Set(terminal->Name);
		flexDefinitionTemplate.terminal_name_->Set(terminal->Name);
		flexDefinitionTemplate.terminal_regex_->Set(terminal->Regex);
		flexDefinitionTemplate.terminal_id_->Set(std::to_string(index));

		switch (terminal->Special)
		{
		case language::type::definition::object::main::SpecialType::Standard: {
			flexDefinitionTemplate.terminal_is_transferred_->Set("true");
			flexDefinitionTemplate.terminal_is_deleted_->Set("false");
			break;
		}
		case language::type::definition::object::main::SpecialType::Ignore:
		case language::type::definition::object::main::SpecialType::NoValue: {
			flexDefinitionTemplate.terminal_is_transferred_->Set("true");
			flexDefinitionTemplate.terminal_is_deleted_->Set("true");
			break;
		}
		case language::type::definition::object::main::SpecialType::Delete:
		case language::type::definition::object::main::SpecialType::Crash: {
			flexDefinitionTemplate.terminal_is_transferred_->Set("false");
			flexDefinitionTemplate.terminal_is_deleted_->Set("true");
			break;
		}
		}

		flexDefinitionTemplate.terminal_declaration_->ExpandVariableField();
		flexDefinitionTemplate.terminal_action_->ExpandVariableField();
		flexDefinitionTemplate.ast_include_nonterminal_->ExpandVariableField();

		index++;
	}

	for (const auto* nonTerminal : reference.GetDefinition<Type::Grammar>().NonTerminals)
	{
		flexDefinitionTemplate.node_name_->Set(nonTerminal->Name);
		flexDefinitionTemplate.ast_include_nonterminal_->ExpandVariableField();
	}

	return flexDefinitionTemplate.GetOutput();
}

std::string deamer::lexer::generator::flex::Flex::GenerateDeamerLexer_HeaderFile() const
{
	auto flexHeaderTemplate = templates::flex::FlexHeaderTemplate();
	flexHeaderTemplate.language_name_->Set(name);
	return flexHeaderTemplate.GetOutput();
}

std::string deamer::lexer::generator::flex::Flex::GenerateDeamerLexer_SourceFile() const
{
	return "";
}

std::unique_ptr<deamer::file::tool::action::Action>
deamer::lexer::generator::flex::Flex::externalAction()
{
	auto builder = file::tool::action::Builder();
	builder
		.PlatformSpecificCommand(
			{{file::tool::OSType::os_linux,
			  "flex -P" + name + " --header-file=./" + name + "_lexer.h ./" + name + "_lexer.l"}})
		.MoveFile("./lex." + name + ".c", "./lex." + name + ".cpp");

	return builder.GetAction();
}

std::string deamer::lexer::generator::flex::Flex::externalCMakeLists()
{
	std::string base = "set(source_files ./lex." + name +
					   ".cpp)\n"
					   "" +
					   name +
					   "_add_external_library(Flex ${source_files})\n"
					   "\n";
	const bool debug = reference.GetDefinition<Type::Generation>().IsArgumentSet(
		{tool::type::Tool::Flex, "Debug"});
	if (!debug)
	{
		return base;
	}

	const std::string debug_main =
		"add_executable(Flex_debug \"./main.cpp\")\n"
		"target_link_libraries(Flex_debug " +
		name +
		"_static_library)\n"
		"target_include_directories(Flex_debug PRIVATE \"${" +
		name +
		"_SOURCE_DIR}/include\")\n"
		"\n";

	return base + debug_main;
}

deamer::file::tool::File deamer::lexer::generator::flex::Flex::createDebugMain()
{
	const std::string content = "#include \"" + name +
								"/Flex/Lexer.h\"\n"
								"#include <iostream>\n"
								"#include <string>\n"
								"\n"
								"int main(int argc, char** argv)\n"
								"{\n"
								"\tstd::string test_lexer_in;\n"
								"\n"
								"\tfor (auto i = 1; i < argc; i++)\n"
								"\t{\n"
								"\t\ttest_lexer_in += argv[i];\n"
								"\n"
								"\t\tif (i < argc)\n"
								"\t\t{\n"
								"\t\t\ttest_lexer_in += ' ';\n"
								"\t\t}\n"
								"\t}\n"
								"\n"
								"\tstd::cout << \"Setting up lexer\\n\";\n"
								"\tauto lexer = " +
								name +
								"::lexer::Lexer();\n"
								"\tstd::cout << \"Done\\n\";\n"
								"\n"
								"\tstd::cout << \"Running the lexer with given input: \";\n"
								"\tauto tokens = lexer.Tokenize(test_lexer_in);\n"
								"\tstd::cout << \"Done\\n\";\n"
								"\n"
								"\tstd::cout << \"Now printing the lexemes:\\n\";\n"
								"\tfor (auto* token : tokens)\n"
								"\t{\n"
								"\t\ttoken->Print();\n"
								"\t\tdelete token;\n"
								"\t}\n"
								"\tstd::cout << \"Done\\n\";\n"
								"}\n";
	return file::tool::File("main", "cpp", content);
}
