#ifndef DST_MAIN_DEFINITION_GRAMMAR_H
#define DST_MAIN_DEFINITION_GRAMMAR_H

#include "Deamer/Language/Generator/Definition/Property/User/Main/Grammar.h"

namespace DST::main
{
	class Language;

	class Grammar : public deamer::language::generator::definition::property::user::Grammar<
						::DST::main::Language>
	{
	public:
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			program;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			stmts;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			stmt;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			variable_insertion;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			other_symbols;

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			program_stmts;

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			stmts_stmt_stmts;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			stmts_empty;

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			stmt_variable_insertion;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			stmt_other;

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			variable_insertion_LEFT_BRACKETS_VARNAME_RIGHT_BRACKETS;

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			other_symbols_LEFT_BRACKET;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			other_symbols_RIGHT_BRACKET;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			other_symbols_LEFT_BRACKETS;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			other_symbols_RIGHT_BRACKETS;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			other_symbols_ESCAPED_LEFT_BRACKETS;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			other_symbols_ESCAPED_RIGHT_BRACKETS;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			other_symbols_VARNAME;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			other_symbols_BACKSLASH;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			other_symbols_OTHER;

	public:
		Grammar(::DST::main::Language* language);
		~Grammar() override = default;
	};
}

#endif // DST_MAIN_DEFINITION_GRAMMAR_H
