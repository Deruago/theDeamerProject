#include "Grammar.h"
#include "Language.h"

::DST::setting::Grammar::Grammar(::DST::setting::Language* language)
	: deamer::language::generator::definition::property::user::Grammar<DST::setting::Language>(
		  language)
{
	// Non Terminals
	program.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"program", {program_stmts.Pointer()}));

	stmts.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"stmts", {stmts_stmt_stmts.Pointer(), stmts_empty.Pointer()}));

	stmt.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"stmt", {stmt_abstraction.Pointer(), stmt_special.Pointer()},
		deamer::language::type::definition::object::main::NonTerminalAbstraction::Group));

	abstraction.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"abstraction", {abstraction_variable_declaration_EQUAL_main_assignment.Pointer()}));

	special.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"special", {special_variable_declaration_EQUAL_keyword_assignment.Pointer()}));

	variable_declaration.Set(
		new const deamer::language::type::definition::object::main::NonTerminal(
			"variable_declaration",
			{variable_declaration_LEFT_BRACKETS_VARNAME_scope_RIGHT_BRACKETS.Pointer(),
			 variable_declaration_LEFT_BRACKETS_VARNAME_RIGHT_BRACKETS.Pointer()}));

	main_assignment.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"main_assignment", {main_assignment_USER_INPUT.Pointer()}));

	keyword_assignment.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"keyword_assignment",
		{keyword_assignment_dst_keyword.Pointer(), keyword_assignment_user_keyword.Pointer()}));

	scope.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"scope", {scope_DOT_VARNAME_scope.Pointer(), scope_DOT_VARNAME.Pointer()}));

	dst_keyword.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"dst_keyword", {dst_keyword_INVALID.Pointer()},
		deamer::language::type::definition::object::main::NonTerminalAbstraction::Group));

	user_keyword.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"user_keyword", {user_keyword_LEFT_SQUARE_BRACKET_VARNAME_RIGHT_SQUARE_BRACKET.Pointer()}));

	AddObject(program);
	AddObject(stmts);
	AddObject(stmt);
	AddObject(abstraction);
	AddObject(special);
	AddObject(variable_declaration);
	AddObject(main_assignment);
	AddObject(keyword_assignment);
	AddObject(scope);
	AddObject(dst_keyword);
	AddObject(user_keyword);

	// Production Rules
	program_stmts.Set(new const deamer::language::type::definition::object::main::ProductionRule(
		{stmts.Pointer()}));

	stmts_stmt_stmts.Set(new const deamer::language::type::definition::object::main::ProductionRule(
		{stmt.Pointer(), stmts.Pointer()}));

	stmts_empty.Set(new const deamer::language::type::definition::object::main::ProductionRule());

	stmt_abstraction.Set(new const deamer::language::type::definition::object::main::ProductionRule(
		{abstraction.Pointer()}));

	stmt_special.Set(new const deamer::language::type::definition::object::main::ProductionRule(
		{special.Pointer()}));

	abstraction_variable_declaration_EQUAL_main_assignment.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{variable_declaration.Pointer(), language->EQUAL.Pointer(),
			 main_assignment.Pointer()}));

	special_variable_declaration_EQUAL_keyword_assignment.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{variable_declaration.Pointer(), language->EQUAL.Pointer(),
			 keyword_assignment.Pointer()}));

	variable_declaration_LEFT_BRACKETS_VARNAME_RIGHT_BRACKETS.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->LEFT_BRACKETS.Pointer(), language->VARNAME.Pointer(),
			 language->RIGHT_BRACKETS.Pointer()}));

	variable_declaration_LEFT_BRACKETS_VARNAME_scope_RIGHT_BRACKETS.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->LEFT_BRACKETS.Pointer(), language->VARNAME.Pointer(), scope.Pointer(),
			 language->RIGHT_BRACKETS.Pointer()}));

	scope_DOT_VARNAME_scope.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->DOT.Pointer(), language->VARNAME.Pointer(), scope.Pointer()}));

	scope_DOT_VARNAME.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->DOT.Pointer(), language->VARNAME.Pointer()}));

	main_assignment_USER_INPUT.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->USER_INPUT.Pointer()}));

	keyword_assignment_user_keyword.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{user_keyword.Pointer()}));

	user_keyword_LEFT_SQUARE_BRACKET_VARNAME_RIGHT_SQUARE_BRACKET.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->LEFT_SQUARE_BRACKET.Pointer(), language->VARNAME.Pointer(),
			 language->RIGHT_SQUARE_BRACKET.Pointer()}));

	keyword_assignment_dst_keyword.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{dst_keyword.Pointer()}));

	dst_keyword_INVALID.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->INVALID.Pointer()}));

	AddObject(program_stmts);
	AddObject(stmts_stmt_stmts);
	AddObject(stmts_empty);
	AddObject(stmt_abstraction);
	AddObject(stmt_special);
	AddObject(abstraction_variable_declaration_EQUAL_main_assignment);
	AddObject(special_variable_declaration_EQUAL_keyword_assignment);
	AddObject(variable_declaration_LEFT_BRACKETS_VARNAME_RIGHT_BRACKETS);
	AddObject(variable_declaration_LEFT_BRACKETS_VARNAME_scope_RIGHT_BRACKETS);
	AddObject(scope_DOT_VARNAME_scope);
	AddObject(scope_DOT_VARNAME);
	AddObject(main_assignment_USER_INPUT);
	AddObject(keyword_assignment_user_keyword);
	AddObject(user_keyword_LEFT_SQUARE_BRACKET_VARNAME_RIGHT_SQUARE_BRACKET);
	AddObject(keyword_assignment_dst_keyword);
	AddObject(dst_keyword_INVALID);
}
