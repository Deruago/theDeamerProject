#ifndef SIMPLELANG2_DEFINITION_GRAMMAR_H
#define SIMPLELANG2_DEFINITION_GRAMMAR_H

#include "Deamer/Language/Generator/Definition/Property/User/Main/Grammar.h"

namespace simplelang
{
	class Language;

	class Grammar : public deamer::language::generator::definition::property::user::Grammar<
						simplelang::Language>
	{
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			program;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			stmts;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			stmt;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			runtime;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			declaration;

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			program_stmts;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			stmts_stmt_stmts;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			stmts_empty;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			stmt_varname_semicolon;

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			stmt_runtime;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			declaration_function_declaration;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			declaration_variable_declaration;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			runtime_declaration;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			runtime_function_declaration;

	public:
		Grammar(simplelang::Language* language);
		~Grammar() override = default;
	};
}

#endif // SIMPLELANG2_DEFINITION_GRAMMAR_H
