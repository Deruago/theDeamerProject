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

#include "Deamer/Ast/Type/CPP/EnterExitListener.h"
#include "Deamer/Template/Ast/Type/CPP/EnterExitListener/EnterExitListenerTemplate.h"

deamer::ast::type::cpp::EnterExitListener::EnterExitListener(ReferenceType reference_)
	: reference(reference_),
	  languageName(reference_.GetDefinition<language::type::definition::property::Type::Identity>()
					   .GetName()
					   ->value)
{
	enterExitTemplate = new deamer::templates::ast::type::cpp::EnterExitListenerTemplate();
}

deamer::ast::type::cpp::EnterExitListener::~EnterExitListener()
{
	delete enterExitTemplate;
}

deamer::file::tool::File deamer::ast::type::cpp::EnterExitListener::Generate() const
{
	deamer::file::tool::File baseListener("EnterExitListener", "h");

	enterExitTemplate->const_qualifier_->Set("");
	enterExitTemplate->language_name_->Set(languageName);

	for (const auto& terminal : terminals)
	{
		enterExitTemplate->terminal_name_->Set(terminal->Name);

		enterExitTemplate->terminal_include_->ExpandVariableField();
		enterExitTemplate->dispatch_entry_terminal_case_->ExpandVariableField();
		enterExitTemplate->dispatch_exit_terminal_case_->ExpandVariableField();
		enterExitTemplate->enter_terminal_listen_->ExpandVariableField();
		enterExitTemplate->exit_terminal_listen_->ExpandVariableField();
	}

	for (const auto& nonterminal : nonTerminals)
	{
		enterExitTemplate->nonterminal_name_->Set(nonterminal->Name);

		enterExitTemplate->nonterminal_include_->ExpandVariableField();
		enterExitTemplate->dispatch_entry_nonterminal_case_->ExpandVariableField();
		enterExitTemplate->dispatch_exit_nonterminal_case_->ExpandVariableField();
		enterExitTemplate->enter_nonterminal_listen_->ExpandVariableField();
		enterExitTemplate->exit_nonterminal_listen_->ExpandVariableField();
	}

	baseListener.SetFileContent(enterExitTemplate->GetOutput());

	return baseListener;
}

void deamer::ast::type::cpp::EnterExitListener::AddTerminal(
	language::type::definition::object::main::Terminal* terminal)
{
	terminals.emplace_back(terminal);
}

void deamer::ast::type::cpp::EnterExitListener::AddNonTerminal(
	language::type::definition::object::main::NonTerminal* nonTerminal)
{
	nonTerminals.emplace_back(nonTerminal);
}
