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
#include "Deamer/Lexer/Type/Flex/Output.h"
#include <iostream>
#include <utility>

using namespace deamer::language::type::definition::property;

deamer::lexer::generator::flex::Flex::Flex(ReferenceType reference_)
	: Base(tool::type::Tool::Flex),
	  reference(reference_),
	  name(reference.GetDefinition<Type::Identity>().name->value)
{
}

deamer::file::tool::Output deamer::lexer::generator::flex::Flex::Generate()
{
	const auto Identity = reference.GetDefinition<Type::Identity>();
	const auto Lexicon = reference.GetDefinition<Type::Lexicon>();
	file::tool::Output output("Flex");

	type::flex::Output flexFileData(reference);

	for (auto* const terminal : Lexicon.Terminals)
	{
		flexFileData.AddTerminal(*terminal);
	}

	std::cout << flexFileData.Generate() << std::endl;

	const std::string fileName = name + "_lexer";
	const file::tool::File flexFile(fileName, "l", flexFileData.Generate());
	const file::tool::File DeamerLexer_Header("Lexer", "h", GenerateDeamerLexer_HeaderFile());
	output.AddFileToExternal(flexFile);
	output.AddFileToExternal(DeamerLexer_Header);

	return output;
}

std::string deamer::lexer::generator::flex::Flex::GenerateDeamerLexer_HeaderFile() const
{
	return "#ifndef " + name + "_FLEX_LEXER_H\n" + "#define " + name + "_FLEX_LEXER_H\n" +
		   "\n"
		   "#include <Deamer/External/Cpp/Lexer/Interface/Lexer.h>\n"
		   "\n"
		   "namespace " +
		   name +
		   " { namespace lexer {\n"
		   "\n"
		   "\tclass Lexer : public deamer::external::cpp::lexer::Lexer\n"
		   "\t{\n"
		   "\tpublic:\n"
		   "\t\tLexer() = default;\n"
		   "\t\t~Lexer() override = default;\n"
		   "\tpublic:\n"
		   "\t\tstd::vector<const deamer::external::cpp::lexer::TerminalObject*> Tokenize(const "
		   "std::string& "
		   "text) const override;\n"
		   "\t};\n"
		   "\n"
		   "}}\n"
		   "\n"
		   "#endif // " +
		   name + "_FLEX_LEXER_H\n";
}

std::string deamer::lexer::generator::flex::Flex::GenerateDeamerLexer_SourceFile() const
{
	return "";
}
