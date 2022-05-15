
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

#include "Deamer/Ast/Type/CPP/Enum.h"

deamer::ast::type::cpp::Enum::Enum(ReferenceType reference_)
	: reference(reference_),
	  languageName(reference_.GetDefinition<language::type::definition::property::Type::Identity>()
					   .GetName()
					   ->value)
{
}

deamer::file::tool::File deamer::ast::type::cpp::Enum::Generate()
{
	deamer::file::tool::File enumFile("Type", "h");

	typeTemplate.language_name_->Set(languageName);

	enumFile.SetFileContent(typeTemplate.GetOutput());

	return enumFile;
}

void deamer::ast::type::cpp::Enum::AddTerminal(
	language::reference::LDO<language::type::definition::object::main::Terminal> terminal)
{
	typeTemplate.enum_name_->Set(terminal->Name);
	typeTemplate.terminal_enumeration_->ExpandVariableField();
}

void deamer::ast::type::cpp::Enum::AddNonTerminal(
	language::reference::LDO<language::type::definition::object::main::NonTerminal> nonTerminal)

{
	typeTemplate.enum_name_->Set(nonTerminal->Name);
	typeTemplate.nonterminal_enumeration_->ExpandVariableField();
}
