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

#include "Deamer/Ast/Generation/CPP/CPP.h"
#include "Deamer/Ast/Type/CPP/BaseNode.h"
#include "Deamer/Ast/Type/CPP/CommonNode.h"
#include "Deamer/Ast/Type/CPP/EnterExitListener.h"
#include "Deamer/Ast/Type/CPP/Enum.h"
#include "Deamer/Ast/Type/CPP/Listener.h"
#include "Deamer/Ast/Type/CPP/Node.h"
#include "Deamer/Ast/Type/CPP/Reference/Access.h"
#include "Deamer/Ast/Type/CPP/Relation/NodeEnumToText.h"
#include "Deamer/Ast/Type/CPP/Relation/NodeEnumToType.h"
#include "Deamer/Ast/Type/CPP/Relation/NodeIsDeleted.h"
#include "Deamer/Ast/Type/CPP/Relation/NodeIsIgnored.h"
#include "Deamer/Ast/Type/CPP/Relation/NodeIsInlined.h"
#include "Deamer/Ast/Type/CPP/Relation/NodeIsNonTerminal.h"
#include "Deamer/Ast/Type/CPP/Relation/NodeIsTerminal.h"
#include "Deamer/Ast/Type/CPP/Relation/NodeTextToEnum.h"
#include "Deamer/Ast/Type/CPP/Relation/NodeTypeToEnum.h"
#include "Deamer/Ast/Type/CPP/Utility/CreateNode.h"
#include "Deamer/Ast/Type/CPP/Visitor.h"
#include "Deamer/Ast/Type/CPP/Visualisation/Graph.h"

deamer::ast::generation::cpp::CPP::CPP(ReferenceType reference_)
	: Base(tool::type::Tool::DeamerAST),
	  reference(reference_)
{
}

deamer::file::tool::Output deamer::ast::generation::cpp::CPP::Generate()
{
	deamer::file::tool::Output ast_directory("Ast");
	deamer::file::tool::Output ast_node_directory("Ast/Node");
	deamer::file::tool::Output ast_common_node_directory("Ast/Common/Node");
	deamer::file::tool::Output ast_enum_directory("Ast/Enum");
	deamer::file::tool::Output ast_visitor_directory("Ast/Visitor");
	deamer::file::tool::Output ast_listener_directory("Ast/Listener");
	deamer::file::tool::Output ast_visitor_deamer_directory("Ast/Visitor/Deamer");
	deamer::file::tool::Output ast_visitor_tool_directory("Ast/Visitor/Tool");
	deamer::file::tool::Output ast_visitor_user_directory("Ast/Visitor/User");
	deamer::file::tool::Output ast_listener_deamer_directory("Ast/Listener/Deamer");
	deamer::file::tool::Output ast_listener_tool_directory("Ast/Listener/Tool");
	deamer::file::tool::Output ast_listener_user_directory("Ast/Listener/User");
	deamer::file::tool::Output ast_relation_directory("Ast/Relation");
	deamer::file::tool::Output ast_reference_directory("Ast/Reference");
	deamer::file::tool::Output ast_visualisation_directory("Ast/Visualisation");
	deamer::file::tool::Output ast_utility_directory("Ast/Utility");

	type::cpp::Enum enumeration(reference);
	type::cpp::EnterExitListener enterExitListener(reference);
	type::cpp::Listener listener(reference);
	type::cpp::Visitor visitor(reference);
	type::cpp::NodeEnumToType nodeEnumToType(reference);
	type::cpp::NodeEnumToText nodeEnumToText(reference);
	type::cpp::NodeTextToEnum nodeTextToEnum(reference);
	type::cpp::NodeTypeToEnum nodeTypeToEnum(reference);
	type::cpp::NodeIsInlined nodeIsInlined(reference);
	type::cpp::NodeIsNonTerminal nodeIsNonTerminal(reference);
	type::cpp::NodeIsTerminal nodeIsTerminal(reference);
	type::cpp::NodeIsDeleted nodeIsDeleted(reference);
	type::cpp::NodeIsIgnored nodeIsIgnored(reference);
	type::cpp::Access access(reference);
	type::cpp::Graph graph(reference);
	type::cpp::CreateNode createNode(reference);

	const type::cpp::BaseNode baseNode(reference);
	ast_node_directory.AddFileToInclude(baseNode.Generate());

	for (auto* terminal :
		 reference.GetDefinition<language::type::definition::property::Type::Lexicon>().Terminals)
	{
		const type::cpp::Node node(reference, terminal);

		if (!reference.GetDefinition<language::type::definition::property::Type::Generation>()
				 .IsArgumentSet({tool::type::Tool::DeamerAST, "single-ast"}))
		{
			ast_node_directory.AddFileToInclude(node.Generate());
		}

		enumeration.AddTerminal(terminal);
		listener.AddTerminal(terminal);
		enterExitListener.AddTerminal(terminal);
		visitor.AddTerminal(terminal);
	}

	for (auto* nonTerminal :
		 reference.GetDefinition<language::type::definition::property::Type::Grammar>()
			 .NonTerminals)
	{
		const type::cpp::Node node(reference, nonTerminal);

		if (!reference.GetDefinition<language::type::definition::property::Type::Generation>()
				 .IsArgumentSet({tool::type::Tool::DeamerAST, "single-ast"}))
		{
			ast_node_directory.AddFileToInclude(node.Generate());
		}

		enumeration.AddNonTerminal(nonTerminal);
		listener.AddNonTerminal(nonTerminal);
		enterExitListener.AddNonTerminal(nonTerminal);
		visitor.AddNonTerminal(nonTerminal);

		if (!reference.GetDefinition<language::type::definition::property::Type::Generation>()
				 .IsArgumentSet({tool::type::Tool::DeamerAST, "single-ast"}))
		{
			if (nonTerminal->abstraction ==
				language::type::definition::object::main::NonTerminalAbstraction::Group)
			{
				const type::cpp::CommonNode commonNode(reference, nonTerminal);
				ast_common_node_directory.AddFileToInclude(commonNode.Generate());
			}
		}
	}

	ast_enum_directory.AddFileToInclude(enumeration.Generate());
	ast_listener_directory.AddFileToInclude(listener.Generate());
	ast_listener_directory.AddFileToInclude(enterExitListener.Generate());
	ast_visitor_directory.AddFileToInclude(visitor.Generate());
	ast_relation_directory.AddFileToInclude(nodeEnumToType.Generate());
	ast_relation_directory.AddFileToInclude(nodeTypeToEnum.Generate());
	ast_relation_directory.AddFileToInclude(nodeEnumToText.Generate());
	ast_relation_directory.AddFileToInclude(nodeTextToEnum.Generate());
	ast_relation_directory.AddFileToInclude(nodeIsInlined.Generate());
	ast_relation_directory.AddFileToInclude(nodeIsNonTerminal.Generate());
	ast_relation_directory.AddFileToInclude(nodeIsTerminal.Generate());
	ast_relation_directory.AddFileToInclude(nodeIsDeleted.Generate());
	ast_relation_directory.AddFileToInclude(nodeIsIgnored.Generate());
	ast_reference_directory.AddFileToInclude(access.Generate());
	ast_visualisation_directory.AddFileToInclude(graph.Generate());
	ast_utility_directory.AddFileToInclude(createNode.Generate());

	return file::tool::Output::Merge(
		{ast_directory, ast_node_directory, ast_common_node_directory, ast_enum_directory,
		 ast_visitor_directory, ast_visitor_deamer_directory, ast_visitor_tool_directory,
		 ast_visitor_user_directory, ast_listener_directory, ast_listener_deamer_directory,
		 ast_listener_tool_directory, ast_listener_user_directory, ast_relation_directory,
		 ast_reference_directory, ast_visualisation_directory, ast_utility_directory});
}
