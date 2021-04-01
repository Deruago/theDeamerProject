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

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			program_stmts;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			stmts_stmt_stmts;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			stmts_empty;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			stmt_varname_semicolon;

	public:
		Grammar(simplelang::Language* language);
		~Grammar() override = default;
	};
}

#endif // SIMPLELANG2_DEFINITION_GRAMMAR_H
