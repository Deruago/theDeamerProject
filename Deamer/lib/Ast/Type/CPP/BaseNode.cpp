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

#include "Deamer/Ast/Type/CPP/BaseNode.h"

deamer::ast::type::cpp::BaseNode::BaseNode(ReferenceType reference_)
	: reference(reference_),
	  languageName(reference_.GetDefinition<language::type::definition::property::Type::Identity>()
					   .name->value)
{
}

deamer::file::tool::File deamer::ast::type::cpp::BaseNode::Generate() const
{
	deamer::file::tool::File baseNodeFile(languageName, "h");

	std::string output;
	output += "#ifndef " + languageName + "_AST_NODE_" + languageName +
			  "_H\n"
			  "#define " +
			  languageName + "_AST_NODE_" + languageName +
			  "_H\n"
			  "\n"
			  "#include <Deamer/External/Cpp/Ast/TemplateNodeBase.h>\n"
			  "\n"
			  "namespace " +
			  languageName +
			  " { namespace ast { namespace node {\n"
			  "\n"
			  "\ttemplate<typename Derived>\n"
			  "\tclass " +
			  languageName + " : public ::deamer::external::cpp::ast::TemplateNodeBase<" +
			  languageName +
			  "<Derived>, Derived>\n"
			  "\t{\n"
			  "\tprivate:\n"
			  "\t\t\n"
			  "\tpublic:\n"
			  "\t\t" +
			  languageName +
			  "(deamer::external::cpp::ast::NodeInformation information_, "
			  "std::vector<deamer::external::cpp::ast::Node*> nodes_ = {}, "
			  "std::vector<size_t> baseValues_ = {})\n"
			  "\t\t: deamer::external::cpp::ast::TemplateNodeBase<" +
			  languageName +
			  "<Derived>, Derived>(information_, nodes_, baseValues_)\n"
			  "\t\t{\n"
			  "\t\t}\n"
			  "\t};\n"
			  "\n"
			  "}}}\n"
			  "\n"
			  "#endif // " +
			  languageName + "_AST_NODE_" + languageName + "_H\n";

	baseNodeFile.SetFileContent(output);
	return baseNodeFile;
}
