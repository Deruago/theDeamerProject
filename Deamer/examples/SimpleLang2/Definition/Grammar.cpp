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
		"stmt", {stmt_varname_semicolon.Pointer(), stmt_runtime.Pointer()}));

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

	runtime.Set(deamer::language::type::definition::object::main::NonTerminal(
		"runtime", {runtime_declaration.Pointer(), runtime_function_declaration.Pointer()},
		deamer::language::type::definition::object::main::NonTerminalAbstraction::Group));
	declaration.Set(deamer::language::type::definition::object::main::NonTerminal(
		"declaration",
		{declaration_function_declaration.Pointer(), declaration_variable_declaration.Pointer()},
		deamer::language::type::definition::object::main::NonTerminalAbstraction::Group));

	stmt_runtime.Set(
		deamer::language::type::definition::object::main::ProductionRule({runtime.Pointer()}));
	runtime_declaration.Set(
		deamer::language::type::definition::object::main::ProductionRule({declaration.Pointer()}));
	runtime_function_declaration.Set(
		deamer::language::type::definition::object::main::ProductionRule(
			{language->FUNCTION_DECLARATION.Pointer()}));

	declaration_function_declaration.Set(
		deamer::language::type::definition::object::main::ProductionRule(
			{language->FUNCTION_DECLARATION.Pointer()}));
	declaration_variable_declaration.Set(
		deamer::language::type::definition::object::main::ProductionRule(
			{language->VAR_DECLARATION.Pointer()}));

	AddObject(stmt_runtime);
	AddObject(declaration);
	AddObject(declaration_function_declaration);
	AddObject(declaration_variable_declaration);
	AddObject(runtime);
	AddObject(runtime_function_declaration);
	AddObject(runtime_declaration);
}
