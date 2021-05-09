#include "Grammar.h"
#include "Language.h"

::DLDL::lexer::Grammar::Grammar(::DLDL::lexer::Language* language)
	: deamer::language::generator::definition::property::user::Grammar<DLDL::lexer::Language>(
		  language)
{
	program.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"program", {program_stmts.Pointer()}));
	stmts.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"stmts", {stmts_stmt_stmts.Pointer(), stmts_empty.Pointer()}));
	stmt.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"stmt", {stmt_tokendeclaration.Pointer()},
		deamer::language::type::definition::object::main::NonTerminalAbstraction::Group));
	tokendeclaration.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"tokendeclaration", {tokendeclaration_abstraction_TERMINAL_REGEX.Pointer(),
							 tokendeclaration_TERMINAL_REGEX.Pointer()}));
	abstraction.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"abstraction",
		{abstraction_DELETE_ABSTRACTION.Pointer(), abstraction_IGNORE_ABSTRACTION.Pointer(),
		 abstraction_CRASH_ABSTRACTION.Pointer(), abstraction_NOVALUE_ABSTRACTION.Pointer(),
		 abstraction_STANDARD_ABSTRACTION.Pointer(), abstraction_UNKNOWN_ABSTRACTION.Pointer()},
		deamer::language::type::definition::object::main::NonTerminalAbstraction::Group));

	AddObject(program);
	AddObject(stmts);
	AddObject(stmt);
	AddObject(tokendeclaration);
	AddObject(abstraction);

	program_stmts.Set(new const deamer::language::type::definition::object::main::ProductionRule(
		{stmts.Pointer()}));
	stmts_stmt_stmts.Set(new const deamer::language::type::definition::object::main::ProductionRule(
		{stmt.Pointer(), stmts.Pointer()}));
	stmts_empty.Set(new const deamer::language::type::definition::object::main::ProductionRule());
	stmt_tokendeclaration.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{tokendeclaration.Pointer()}));
	tokendeclaration_abstraction_TERMINAL_REGEX.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{abstraction.Pointer(), language->TERMINAL.Pointer(), language->REGEX.Pointer()}));
	tokendeclaration_TERMINAL_REGEX.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->TERMINAL.Pointer(), language->REGEX.Pointer()}));

	abstraction_DELETE_ABSTRACTION.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->DELETE_ABSTRACTION.Pointer()}));
	abstraction_IGNORE_ABSTRACTION.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->IGNORE_ABSTRACTION.Pointer()}));
	abstraction_NOVALUE_ABSTRACTION.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->NOVALUE_ABSTRACTION.Pointer()}));
	abstraction_CRASH_ABSTRACTION.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->CRASH_ABSTRACTION.Pointer()}));
	abstraction_STANDARD_ABSTRACTION.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->STANDARD_ABSTRACTION.Pointer()}));
	abstraction_UNKNOWN_ABSTRACTION.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->UNKNOWN_ABSTRACTION.Pointer()}));

	AddObject(program_stmts);
	AddObject(stmts_stmt_stmts);
	AddObject(stmts_empty);
	AddObject(stmt_tokendeclaration);
	AddObject(tokendeclaration_abstraction_TERMINAL_REGEX);
	AddObject(tokendeclaration_TERMINAL_REGEX);

	AddObject(abstraction_DELETE_ABSTRACTION);
	AddObject(abstraction_IGNORE_ABSTRACTION);
	AddObject(abstraction_NOVALUE_ABSTRACTION);
	AddObject(abstraction_CRASH_ABSTRACTION);
	AddObject(abstraction_STANDARD_ABSTRACTION);
	AddObject(abstraction_UNKNOWN_ABSTRACTION);
}
