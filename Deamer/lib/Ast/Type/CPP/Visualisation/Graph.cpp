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

#include "Deamer/Ast/Type/CPP/Visualisation/Graph.h"
#include "Deamer/Template/Ast/Type/CPP/Visualisation/Graph/GraphTemplate.h"

deamer::ast::type::cpp::Graph::Graph(ReferenceType reference_)
	: reference(reference_),
	  languageName(reference_.GetDefinition<language::type::definition::property::Type::Identity>()
					   .GetName()
					   ->value)
{
	GraphTemplate = new ::deamer::templates::ast::type::cpp::GraphTemplate();
}

deamer::ast::type::cpp::Graph::~Graph()
{
	delete GraphTemplate;
}

deamer::file::tool::File deamer::ast::type::cpp::Graph::Generate() const
{
	deamer::file::tool::File graph("Graph", "h");

	GraphTemplate->language_name_->Set(languageName);

	for (language::reference::LDO<language::type::definition::object::main::NonTerminal>
			 nonTerminal :
		 reference.GetDefinition<language::type::definition::property::Type::Grammar>()
			 .NonTerminals)
	{
		GraphTemplate->object_->Set(nonTerminal->Name);
		GraphTemplate->listen_object_entry_->ExpandVariableField();
		GraphTemplate->listen_object_exit_->ExpandVariableField();
	}

	for (language::reference::LDO<language::type::definition::object::main::Terminal> terminal :
		 reference.GetDefinition<language::type::definition::property::Type::Lexicon>().Terminals)
	{
		GraphTemplate->object_->Set(terminal->Name);
		GraphTemplate->listen_object_entry_->ExpandVariableField();
	}

	graph.SetFileContent(GraphTemplate->GetOutput());

	return graph;
}
