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

#include "Deamer/Ast/Type/CPP/Utility/CreateNode.h"

deamer::ast::type::cpp::CreateNode::CreateNode(ReferenceType reference_)
	: reference(reference_),
	  languageName(reference_.GetDefinition<language::type::definition::property::Type::Identity>()
					   .GetName()
					   ->value)
{
	createNodeTemplate = new templates::ast::type::cpp::CreateNodeTemplate();
}

deamer::ast::type::cpp::CreateNode::~CreateNode()
{
	delete createNodeTemplate;
}

deamer::file::tool::File deamer::ast::type::cpp::CreateNode::Generate() const
{
	deamer::file::tool::File access("CreateNode", "h");

	createNodeTemplate->language_name_->Set(languageName);

	if (reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsArgumentSet({tool::type::Tool::DeamerAST, "single-ast"}))
	{
		createNodeTemplate->get_node_create_node_->Set(
			createNodeTemplate->single_get_node_create_node_);
		createNodeTemplate->node_type_include_section_->Set(
			createNodeTemplate->single_type_node_include_section_);
	}
	else
	{
		createNodeTemplate->get_node_create_node_->Set(
			createNodeTemplate->multi_get_node_create_node_);
		createNodeTemplate->node_type_include_section_->Set(
			createNodeTemplate->multi_type_node_include_section_);
	}

	for (language::reference::LDO<language::type::definition::object::main::Terminal> terminal :
		 reference.GetDefinition<language::type::definition::property::Type::Lexicon>().Terminals)
	{
		createNodeTemplate->node_name_->Set(terminal->Name);
		createNodeTemplate->arguments_dispatcher_->Set(createNodeTemplate->terminal_arguments_);

		createNodeTemplate->node_type_include_->ExpandVariableField();
		createNodeTemplate->get_node_create_node_->ExpandVariableField();
	}

	for (language::reference::LDO<language::type::definition::object::main::NonTerminal>
			 nonTerminal :
		 reference.GetDefinition<language::type::definition::property::Type::Grammar>()
			 .NonTerminals)
	{
		createNodeTemplate->node_name_->Set(nonTerminal->Name);
		createNodeTemplate->arguments_dispatcher_->Set(createNodeTemplate->nonterminal_arguments_);

		createNodeTemplate->node_type_include_->ExpandVariableField();
		createNodeTemplate->get_node_create_node_->ExpandVariableField();
	}

	access.SetFileContent(createNodeTemplate->GetOutput());

	return access;
}
