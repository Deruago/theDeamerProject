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

#include "Deamer/Parser/Generator/Bison/Bison.h"
#include "Deamer/Parser/Type/Bison/Output.h"

deamer::parser::generator::bison::Bison::Bison(const ReferenceType reference_)
	: Base(tool::type::Tool::Bison),
	  reference(reference_),
	  name(reference.GetDefinition<language::type::definition::property::Type::Identity>()
			   .name->value)
{
}

deamer::file::tool::Output deamer::parser::generator::bison::Bison::Generate()
{
	file::tool::Output output("Bison");
	type::bison::Output bisonFileData(reference);

	const auto& lexicon =
		reference.GetDefinition<language::type::definition::property::Type::Lexicon>();
	const auto& grammar =
		reference.GetDefinition<language::type::definition::property::Type::Grammar>();
	const auto& identity =
		reference.GetDefinition<language::type::definition::property::Type::Identity>();

	for (language::reference::LDO<language::type::definition::object::main::Terminal> terminal :
		 lexicon.Terminals)
	{
		bisonFileData.AddTerminal(terminal);
	}

	for (language::reference::LDO<language::type::definition::object::main::NonTerminal>
			 nonTerminal : grammar.NonTerminals)
	{
		bisonFileData.AddNonTerminal(nonTerminal);
	}

	std::cout << bisonFileData.Generate() << '\n';

	const std::string fileName = identity.name->value + "_parser";
	const file::tool::File bisonFile(fileName, "y", bisonFileData.Generate());
	const file::tool::File bisonParser("Parser", "h", bisonParserFile());

	output.AddFileToExternal(bisonFile);
	output.AddFileToInclude(bisonParser);
	output.AddActionToExternal(externalAction(), file::tool::OSType::os_linux);
	output.AddActionToExternal(externalAction(), file::tool::OSType::os_windows);
	output.AddCMakeListsToExternal(externalCMakeLists());

	return output;
}

std::string deamer::parser::generator::bison::Bison::bisonParserFile() const
{
	return "#ifndef " + name +
		   "_BISON_PARSER_H\n"
		   "#define " +
		   name +
		   "_BISON_PARSER_H\n"
		   "\n"
		   "#include <Deamer/External/Cpp/Parser/Interface/Parser.h>\n"
		   "\n"
		   "namespace " +
		   name +
		   "{ namespace parser {\n"
		   "\n"
		   "\t class Parser : public deamer::external::cpp::parser::Parser\n"
		   "\t{\n"
		   "\tpublic:\n"
		   "\t\tParser() = default;\n"
		   "\t\t~Parser() override = default;\n"
		   "\n"
		   "\tpublic:\n"
		   "\t\tdeamer::external::cpp::ast::Tree* Parse(const std::string& text) const override;\n"
		   "\t};\n"
		   "\n"
		   "}}\n"
		   "\n"
		   "#endif // " +
		   name + "_BISON_PARSER_H\n";
}

deamer::file::tool::Action deamer::parser::generator::bison::Bison::externalAction()
{
	return "bison -p" + name + " -d ./" + name + "_parser.y" + " ; mv ./" + name +
		   "_parser.tab.c ./" + name + "_parser.tab.cpp";
}

std::string deamer::parser::generator::bison::Bison::externalCMakeLists()
{
	return "set(source_files ./" + name + "_parser.tab.cpp)\n" + name +
		   "_add_external_library(Bison ${source_files})\n";
}
