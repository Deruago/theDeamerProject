#ifndef DLDL_GRAMMAR_DEFINITION_GRAMMAR_H
#define DLDL_GRAMMAR_DEFINITION_GRAMMAR_H

#include "Deamer/Language/Generator/Definition/Property/User/Main/Grammar.h"

namespace DLDL::grammar
{
	class Language;

	class Grammar : public deamer::language::generator::definition::property::user::Grammar<
						::DLDL::grammar::Language>
	{
	public:
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			program;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			stmts;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			stmt;

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			definition;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			abstraction_declaration;

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			abstraction;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			production_rules;

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			program_stmts;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			stmts_stmt_stmts;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			stmts_empty;

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			stmt_definition;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			stmt_abstraction_declaration;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			definition_abstraction_NONTERMINAL_production_rules;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			definition_NONTERMINAL_production_rules;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			abstraction_declaration_abstraction_NONTERMINAL;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			abstraction_START_ABSTRACTION;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			abstraction_GROUP_ABSTRACTION;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			abstraction_UNKNOWN_ABSTRACTION;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			production_rules_PRODUCTION_RULE_production_rules;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			production_rules_PRODUCTION_RULE;

	public:
		Grammar(::DLDL::grammar::Language* language);
		~Grammar() override = default;
	};
}

#endif // DLDL_GRAMMAR_DEFINITION_GRAMMAR_H
