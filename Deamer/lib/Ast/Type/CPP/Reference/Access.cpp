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

#include "Deamer/Ast/Type/CPP/Reference/Access.h"
#include "Deamer/Language/Analyzer/Main/Grammar/NonTerminal.h"

deamer::ast::type::cpp::Access::Access(ReferenceType reference_)
	: reference(reference_),
	  languageName(reference_.GetDefinition<language::type::definition::property::Type::Identity>()
					   .GetName()
					   ->value)
{
	accessTemplate = new templates::ast::type::cpp::AccessTemplate();
}

deamer::ast::type::cpp::Access::~Access()
{
	delete accessTemplate;
}

deamer::file::tool::File deamer::ast::type::cpp::Access::Generate() const
{
	deamer::file::tool::File access("Access", "h");

	accessTemplate->language_name_->Set(languageName);

	for (const auto* const nonterminal :
		 reference.GetDefinition<language::type::definition::property::Type::Grammar>()
			 .NonTerminals)
	{
		accessTemplate->node_name_->Set(nonterminal->Name);
		auto analyzer = ::deamer::language::analyzer::main::NonTerminal(&reference, nonterminal);
		const auto directAccessibleNodes = analyzer.GetDirectNonTerminalAndTerminals();
		for (auto* const node : directAccessibleNodes)
		{
			if (node->Type_ == language::type::definition::object::Type::NonTerminal)
			{
				const auto target =
					language::reference::LDO<language::type::definition::object::main::NonTerminal>(
						node);
				accessTemplate->node_target_name_->Set(target->Name);
			}
			else
			{
				const auto target =
					language::reference::LDO<language::type::definition::object::main::Terminal>(
						node);
				accessTemplate->node_target_name_->Set(target->Name);
			}

			accessTemplate->target_retrievement_function_declaration_->ExpandVariableField();
			accessTemplate->target_retrievement_function_implementation_->ExpandVariableField();
		}

		accessTemplate->node_access_->ExpandVariableField();
		accessTemplate->node_type_include_->ExpandVariableField();
		accessTemplate->node_access_forward_declaration_->ExpandVariableField();

		accessTemplate->target_retrievement_function_declaration_->Variable_Field()->Set("");
	}

	for (const auto* const terminal :
		 reference.GetDefinition<language::type::definition::property::Type::Lexicon>().Terminals)
	{
		accessTemplate->node_name_->Set(terminal->Name);
		accessTemplate->node_access_->ExpandVariableField();
		accessTemplate->node_type_include_->ExpandVariableField();
		accessTemplate->node_access_forward_declaration_->ExpandVariableField();
	}

	access.SetFileContent(accessTemplate->GetOutput());

	return access;
}
