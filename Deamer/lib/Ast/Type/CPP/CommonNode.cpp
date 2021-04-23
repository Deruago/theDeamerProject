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

#include "Deamer/Ast/Type/CPP/CommonNode.h"

deamer::ast::type::cpp::CommonNode::CommonNode(
	ReferenceType reference_,
	language::reference::LDO<language::type::definition::object::main::NonTerminal> nonTerminal_)
	: reference(reference_),
	  nonTerminal(nonTerminal_),
	  languageName(reference_.GetDefinition<language::type::definition::property::Type::Identity>()
					   .name->value)
{
}

deamer::file::tool::File deamer::ast::type::cpp::CommonNode::Generate() const
{
	deamer::file::tool::File commonNodeFile(nonTerminal->Name, "h");
	commonNodeFile.SetGenerationLevel(
		file::tool::GenerationLevel::Dont_generate_if_file_already_exists);

	std::string output;
	output += "#ifndef " + languageName + "_AST_COMMON_NODE_" + nonTerminal->Name +
			  "_H\n"
			  "#define " +
			  languageName + "_AST_COMMON_NODE_" + nonTerminal->Name +
			  "_H\n"
			  "\n"
			  "#include <Deamer/External/Cpp/Ast/CommonNodeAPI.h>\n"
			  "\n"
			  "namespace " +
			  languageName +
			  " { namespace ast { namespace common { namespace node {\n"
			  "\n"
			  "\tclass " +
			  nonTerminal->Name + " : public ::deamer::external::cpp::ast::CommonNodeAPI<" +
			  nonTerminal->Name +
			  ">\n"
			  "\t{"
			  "\tprivate:\n"
			  "\tpublic:\n"
			  "\t\t" +
			  nonTerminal->Name +
			  "() = default;\n"
			  "\t\tvirtual ~" +
			  nonTerminal->Name +
			  "() = default;\n"
			  "\tpublic:\n"
			  "\t};"
			  "\n"
			  "}}}}\n"
			  "\n"
			  "#endif // " +
			  languageName + "_AST_COMMON_NODE_" + nonTerminal->Name + "_H\n";

	commonNodeFile.SetFileContent(output);

	return commonNodeFile;
}
