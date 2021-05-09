#include "Grammar.h"
#include "Language.h"

::DLDL::grammar::Grammar::Grammar(::DLDL::grammar::Language* language)
	: deamer::language::generator::definition::property::user::Grammar<DLDL::grammar::Language>(
		  language)
{
	program.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"program", {program_stmts.Pointer()}));
	stmts.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"stmts", {stmts_stmt_stmts.Pointer(), stmts_empty.Pointer()}));
	stmt.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"stmt", {stmt_abstraction_declaration.Pointer(), stmt_definition.Pointer()}));

	abstraction_declaration.Set(
		new const deamer::language::type::definition::object::main::NonTerminal(
			"abstraction_declaration",
			{abstraction_declaration_abstraction_NONTERMINAL.Pointer()}));
	abstraction.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"abstraction",
		{abstraction_GROUP_ABSTRACTION.Pointer(), abstraction_START_ABSTRACTION.Pointer(),
		 abstraction_UNKNOWN_ABSTRACTION.Pointer()}));

	definition.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"definition", {definition_abstraction_NONTERMINAL_production_rules.Pointer(),
					   definition_NONTERMINAL_production_rules.Pointer()}));

	production_rules.Set(new const deamer::language::type::definition::object::main::NonTerminal(
		"production_rules", {production_rules_PRODUCTION_RULE_production_rules.Pointer(),
							 production_rules_PRODUCTION_RULE.Pointer()}));

	AddObject(program);
	AddObject(stmts);
	AddObject(stmt);

	AddObject(abstraction_declaration);
	AddObject(abstraction);
	AddObject(definition);
	AddObject(production_rules);

	program_stmts.Set(new const deamer::language::type::definition::object::main::ProductionRule(
		{stmts.Pointer()}));
	stmts_stmt_stmts.Set(new const deamer::language::type::definition::object::main::ProductionRule(
		{stmt.Pointer(), stmts.Pointer()}));
	stmts_empty.Set(new const deamer::language::type::definition::object::main::ProductionRule());

	stmt_abstraction_declaration.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{abstraction_declaration.Pointer()}));
	stmt_definition.Set(new const deamer::language::type::definition::object::main::ProductionRule(
		{definition.Pointer()}));

	abstraction_declaration_abstraction_NONTERMINAL.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{abstraction.Pointer(), language->NONTERMINAL.Pointer()}));
	abstraction_GROUP_ABSTRACTION.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->GROUP_ABSTRACTION.Pointer()}));
	abstraction_START_ABSTRACTION.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->START_ABSTRACTION.Pointer()}));
	abstraction_UNKNOWN_ABSTRACTION.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->UNKNOWN_ABSTRACTION.Pointer()}));

	production_rules_PRODUCTION_RULE_production_rules.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->PRODUCTION_RULE.Pointer(), production_rules.Pointer()}));
	production_rules_PRODUCTION_RULE.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->PRODUCTION_RULE.Pointer()}));

	definition_abstraction_NONTERMINAL_production_rules.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{abstraction.Pointer(), language->NONTERMINAL.Pointer(), production_rules.Pointer()}));
	definition_NONTERMINAL_production_rules.Set(
		new const deamer::language::type::definition::object::main::ProductionRule(
			{language->NONTERMINAL.Pointer(), production_rules.Pointer()}));

	AddObject(program_stmts);
	AddObject(stmts_stmt_stmts);
	AddObject(stmts_empty);

	AddObject(stmt_abstraction_declaration);
	AddObject(stmt_definition);
	AddObject(abstraction_declaration_abstraction_NONTERMINAL);
	AddObject(abstraction_GROUP_ABSTRACTION);
	AddObject(abstraction_START_ABSTRACTION);
	AddObject(abstraction_UNKNOWN_ABSTRACTION);
	AddObject(production_rules_PRODUCTION_RULE_production_rules);
	AddObject(production_rules_PRODUCTION_RULE);
	AddObject(definition_abstraction_NONTERMINAL_production_rules);
	AddObject(definition_NONTERMINAL_production_rules);
}
