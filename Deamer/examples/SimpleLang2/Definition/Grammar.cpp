#include "Grammar.h"
#include "Language.h"

simplelang::Grammar::Grammar(simplelang::Language* language)
	: deamer::language::generator::definition::property::user::Grammar<simplelang::Language>(
		  language)
{
	program.Set(deamer::language::type::definition::object::main::NonTerminal(
		"Program", {program_stmts.Pointer()}));
	stmts.Set(deamer::language::type::definition::object::main::NonTerminal(
		"stmts", {stmts_stmt_stmts.Pointer(), stmts_empty.Pointer()}));
	stmt.Set(deamer::language::type::definition::object::main::NonTerminal(
		"stmt", {stmt_varname_semicolon.Pointer()}));

	program_stmts.Set(
		deamer::language::type::definition::object::main::ProductionRule({stmts.Pointer()}));
	stmts_stmt_stmts.Set(deamer::language::type::definition::object::main::ProductionRule(
		{stmt.Pointer(), stmts.Pointer()}));
	stmts_empty.Set(deamer::language::type::definition::object::main::ProductionRule{});
	stmt_varname_semicolon.Set(deamer::language::type::definition::object::main::ProductionRule(
		{language->VARNAME.Pointer(), language->SEMICOLON.Pointer()}));

	AddObject(program);
	AddObject(stmts);
	AddObject(stmt);
	AddObject(program_stmts);
	AddObject(stmts_stmt_stmts);
	AddObject(stmts_empty);
	AddObject(stmt_varname_semicolon);
}
