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

#include "Deamer/Lexer/Type/Flex/TerminalAction.h"

deamer::lexer::type::flex::TerminalAction::TerminalAction(
	const language::type::definition::object::main::Terminal& terminal_,
	const ReferenceType reference_)
	: Data(terminal_, reference_),
	  terminalAnalyzer(&reference, &terminal)
{
}

std::string deamer::lexer::type::flex::TerminalAction::Generate() const
{
	return braces(terminal.Name) + '\t' + braces(GetDebug() + OptionalAction() + OptionalReturn()) +
		   '\n';
}

std::string deamer::lexer::type::flex::TerminalAction::GetDebug() const
{
	if (generation.IsArgumentSet({tool::type::Tool::Flex, "Debug"}))
	{
		return "std::cout << yytext << \" is a " + terminal.Name + "\" << '\\n';";
	}

	return "";
}

std::string deamer::lexer::type::flex::TerminalAction::GetAction() const
{
	if (generation.IsIntegrationSet({tool::type::Tool::Flex, tool::type::Tool::Bison}) ||
		generation.IsArgumentSet({tool::type::Tool::Flex, "Output-terminal-objects"}))
	{
		switch (terminal.Special)
		{
		case language::type::definition::object::main::SpecialType::Standard:
			return identity.name->value +
				   "lval.Terminal = new deamer::external::cpp::lexer::TerminalObject(yyval, "
				   "yylineno);";
		case language::type::definition::object::main::SpecialType::Ignore:
		case language::type::definition::object::main::SpecialType::NoValue:
			return identity.name->value +
				   "lval.Terminal = new deamer::external::cpp::lexer::TerminalObject(\"\", "
				   "yylineno);";
		case language::type::definition::object::main::SpecialType::Delete:
			return "";
		case language::type::definition::object::main::SpecialType::Crash:
			return R"(std::cout << "Encountered illegal token: " << yytext << '\n'; exit (EXIT_FAILURE);)";
		}
	}
	switch (terminal.Special)
	{
	case language::type::definition::object::main::SpecialType::Crash:
		return R"(std::cout << "Encountered illegal token: " << yytext << '\n'; exit (EXIT_FAILURE);)";
	case language::type::definition::object::main::SpecialType::Standard:
	case language::type::definition::object::main::SpecialType::Delete:
	case language::type::definition::object::main::SpecialType::Ignore:
	case language::type::definition::object::main::SpecialType::NoValue:
		return "";
	}

	return "";
}

std::string deamer::lexer::type::flex::TerminalAction::OptionalAction() const
{
	switch (terminal.Special)
	{
	case language::type::definition::object::main::SpecialType::Standard:
		return "if (local_store) store(new deamer::external::cpp::lexer::TerminalObject(yyval, "
			   "yylineno));"
			   "else " +
			   GetAction() + ';';
	case language::type::definition::object::main::SpecialType::Ignore:
	case language::type::definition::object::main::SpecialType::NoValue:
		return "if (local_store) store(new deamer::external::cpp::lexer::TerminalObject(\"\", "
			   "yylineno));"
			   "else " +
			   GetAction() + ';';
	case language::type::definition::object::main::SpecialType::Delete:
		return "";
	case language::type::definition::object::main::SpecialType::Crash:
		return "";
	}

	return "";
}

std::string deamer::lexer::type::flex::TerminalAction::ReturnValue() const
{
	if (generation.IsIntegrationSet({tool::type::Tool::Flex, tool::type::Tool::Bison}))
	{
		switch (terminal.Special)
		{
		case language::type::definition::object::main::SpecialType::Standard:
		case language::type::definition::object::main::SpecialType::Ignore:
		case language::type::definition::object::main::SpecialType::NoValue:
			return "return " + parenthesis(terminal.Name) + ";";
		case language::type::definition::object::main::SpecialType::Delete:
		case language::type::definition::object::main::SpecialType::Crash:
			return "";
		}
	}

	return "";
}

std::string deamer::lexer::type::flex::TerminalAction::OptionalReturn() const
{
	return "if (!local_store) " + ReturnValue() + ";";
}
