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

#include "Deamer/Ast/Type/CPP/Relation/NodeIsNonTerminal.h"
#include "Deamer/Template/Ast/Type/CPP/Relation/NodeIsNonTerminal/NodeIsNonTerminalTemplate.h"

deamer::ast::type::cpp::NodeIsNonTerminal::NodeIsNonTerminal(ReferenceType reference_)
	: reference(reference_),
	  languageName(reference_.GetDefinition<language::type::definition::property::Type::Identity>()
					   .name->value)
{
	nodeIsNonTerminalTemplate = new ::deamer::templates::ast::type::cpp::NodeIsNonTerminalTemplate();
}

deamer::ast::type::cpp::NodeIsNonTerminal::~NodeIsNonTerminal()
{
	delete nodeIsNonTerminalTemplate;
}

deamer::file::tool::File deamer::ast::type::cpp::NodeIsNonTerminal::Generate() const
{
	deamer::file::tool::File nodeIsNonTerminal("NodeIsNonTerminal", "h");

	nodeIsNonTerminalTemplate->language_name_->Set(languageName);

	for (const auto* const nonterminal :
		 reference.GetDefinition<language::type::definition::property::Type::Grammar>()
			 .NonTerminals)
	{
		nodeIsNonTerminalTemplate->node_name_->Set(nonterminal->Name);
		nodeIsNonTerminalTemplate->is_nonterminal_->Set("true");

		nodeIsNonTerminalTemplate->node_conversion_->ExpandVariableField();
	}

	nodeIsNonTerminal.SetFileContent(nodeIsNonTerminalTemplate->GetOutput());

	return nodeIsNonTerminal;
}
