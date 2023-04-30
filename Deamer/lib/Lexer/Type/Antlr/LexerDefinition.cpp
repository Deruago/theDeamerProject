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

#include "Deamer/Lexer/Type/Antlr/LexerDefinition.h"
#include "Deamer/Language/Reference/LDO.h"
#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/Terminal.h"
#include "Deamer/Template/Lexer/Antlr/LexiconDefinitionTemplate.h"
#include <iostream>

deamer::lexer::type::antlr::LexerDefinition::LexerDefinition(ReferenceType reference_)
	: reference(reference_)
{
}

std::string deamer::lexer::type::antlr::LexerDefinition::Generate() const
{
	auto AntlrRegex = [](std::string deamerRegex) {
		std::string antlrRegex;
		bool insideRegex = false;
		bool encounterSlash = false;

		for (std::size_t i = 0; i < deamerRegex.size(); i++)
		{
			auto currentCharacter = deamerRegex[i];
			if (insideRegex)
			{
				antlrRegex += currentCharacter;
				if (encounterSlash)
				{
					encounterSlash = false;
				}
				else if (currentCharacter == '\\')
				{
					// Ensures that the next character will not be checked
					encounterSlash = true;
				}
				else if (currentCharacter == ']')
				{
					insideRegex = false;
				}
			}
			else if (currentCharacter == '[')
			{
				antlrRegex += currentCharacter;
				insideRegex = true;
			}
			else
			{
				antlrRegex += std::string("[") + currentCharacter + std::string("]");
			}
		}
		return antlrRegex;
	};

	const auto language_name =
		reference.GetDefinition<language::type::definition::property::Type::Identity>()
			.GetName()
			->value;

	auto lexiconDefinition = templates::antlr::lexer::LexiconDefinitionTemplate();
	lexiconDefinition.language_name_->Set(language_name);

	for (language::reference::LDO<language::type::definition::object::main::Terminal> terminal :
		 reference.GetDefinition<language::type::definition::property::Type::Lexicon>().Terminals)
	{
		switch (terminal->Special)
		{
		case language::type::definition::object::main::SpecialType::Standard:
		case language::type::definition::object::main::SpecialType::Ignore:
		case language::type::definition::object::main::SpecialType::NoValue:
			lexiconDefinition.terminal_declaration_->Set(lexiconDefinition.standard_terminal_);
			break;
		case language::type::definition::object::main::SpecialType::Delete:
			lexiconDefinition.terminal_declaration_->Set(lexiconDefinition.deleted_terminal_);
			break;
		case language::type::definition::object::main::SpecialType::Crash:
			lexiconDefinition.terminal_declaration_->Set(lexiconDefinition.crash_terminal_);
			break;
		}

		lexiconDefinition.terminal_name_->Set(terminal->Name);
		lexiconDefinition.terminal_regex_->Set(AntlrRegex(terminal->Regex));

		lexiconDefinition.terminal_declaration_->ExpandVariableField();
	}

	return lexiconDefinition.GetOutput();
}
