#include "Grammar.h"
#include "Language.h"

::DST::main::Grammar::Grammar(::DST::main::Language* language)
	: deamer::language::generator::definition::property::user::Grammar<DST::main::Language>(
		  language)
{
	// Non Terminals
	program.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"program", {program_stmts.Pointer()}));

	stmts.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"stmts", {stmts_stmt_stmts.Pointer(), stmts_empty.Pointer()}));

	stmt.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"stmt", {stmt_variable_insertion.Pointer(), stmt_other.Pointer()},
		deamer::language::type::definition::object::main::NonTerminalAbstraction::Group));

	variable_insertion.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"variable_insertion",
		{variable_insertion_LEFT_BRACKETS_variable_RIGHT_BRACKETS.Pointer()}));

	variable.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"variable", {variable_VARNAME_scope.Pointer(), variable_VARNAME.Pointer()}));

	variable_VARNAME_scope.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->VARNAME.Pointer(), scope.Pointer()}));
	variable_VARNAME.Set(new const deamer::language::type::definition::object::main::ProductionRule(
		{language->VARNAME.Pointer()}));

	scope.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"scope", {scope_DOT_VARNAME_scope.Pointer(), scope_DOT_VARNAME.Pointer()}));

	scope_DOT_VARNAME_scope.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->DOT.Pointer(), language->VARNAME.Pointer(), scope.Pointer()}));

	scope_DOT_VARNAME.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->DOT.Pointer(), language->VARNAME.Pointer()}));

	other_symbols.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"other_symbols",
		{other_symbols_ESCAPED_LEFT_BRACKETS.Pointer(),
		 other_symbols_ESCAPED_RIGHT_BRACKETS.Pointer(), other_symbols_LEFT_BRACKETS.Pointer(),
		 other_symbols_RIGHT_BRACKETS.Pointer(), other_symbols_LEFT_BRACKET.Pointer(),
		 other_symbols_RIGHT_BRACKET.Pointer(), other_symbols_OTHER.Pointer(),
		 other_symbols_BACKSLASH.Pointer(), other_symbols_VARNAME.Pointer(),
		 other_symbols_DOT.Pointer()},
		deamer::language::type::definition::object::main::NonTerminalAbstraction::Group));

	// Production Rules
	program_stmts.Set(new const deamer::language::type::definition::object::main::ProductionRule(
		{stmts.Pointer()}));

	stmts_stmt_stmts.Set(new const deamer::language::type::definition::object::main::ProductionRule(
		{stmt.Pointer(), stmts.Pointer()}));

	stmts_empty.Set(new const deamer::language::type::definition::object::main::ProductionRule());

	stmt_variable_insertion.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{variable_insertion.Pointer()}));
	stmt_other.Set(new const deamer::language::type::definition::object::main::ProductionRule(
		{other_symbols.Pointer()}));

	variable_insertion_LEFT_BRACKETS_variable_RIGHT_BRACKETS.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->LEFT_BRACKETS.Pointer(), language->variable.Pointer(),
			 language->RIGHT_BRACKETS.Pointer()}));

	other_symbols_ESCAPED_LEFT_BRACKETS.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->LEFT_BRACKETS_ESCAPED.Pointer()}));
	other_symbols_ESCAPED_RIGHT_BRACKETS.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->RIGHT_BRACKETS_ESCAPED.Pointer()}));
	other_symbols_LEFT_BRACKET.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->LEFT_BRACKET.Pointer()}));
	other_symbols_RIGHT_BRACKET.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->RIGHT_BRACKET.Pointer()}));
	other_symbols_LEFT_BRACKETS.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->LEFT_BRACKETS.Pointer()}));
	other_symbols_RIGHT_BRACKETS.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->RIGHT_BRACKETS.Pointer()}));
	other_symbols_OTHER.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->OTHER.Pointer()}));
	other_symbols_BACKSLASH.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->BACKSLASH.Pointer()}));
	other_symbols_VARNAME.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->VARNAME.Pointer()}));
	other_symbols_DOT.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->DOT.Pointer()}));

	AddObject(program);
	AddObject(stmts);
	AddObject(stmt);
	AddObject(variable_insertion);
	AddObject(other_symbols);
	AddObject(variable);
	AddObject(scope);

	AddObject(program_stmts);
	AddObject(stmts_stmt_stmts);
	AddObject(stmts_empty);
	AddObject(stmt_variable_insertion);
	AddObject(stmt_other);
	AddObject(other_symbols_ESCAPED_LEFT_BRACKETS);
	AddObject(other_symbols_ESCAPED_RIGHT_BRACKETS);
	AddObject(other_symbols_LEFT_BRACKET);
	AddObject(other_symbols_RIGHT_BRACKET);
	AddObject(other_symbols_LEFT_BRACKETS);
	AddObject(other_symbols_RIGHT_BRACKETS);
	AddObject(other_symbols_OTHER);
	AddObject(other_symbols_BACKSLASH);
	AddObject(other_symbols_VARNAME);
	AddObject(other_symbols_DOT);
	AddObject(variable_VARNAME_scope);
	AddObject(variable_VARNAME);
	AddObject(scope_DOT_VARNAME_scope);
	AddObject(scope_DOT_VARNAME);
}
