#ifndef DLDL_LEXER_DEFINITION_GRAMMAR_H
#define DLDL_LEXER_DEFINITION_GRAMMAR_H

#include "Deamer/Language/Generator/Definition/Property/User/Main/Grammar.h"

namespace DLDL::lexer
{
	class Language;

	class Grammar : public deamer::language::generator::definition::property::user::Grammar<
						::DLDL::lexer::Language>
	{
	public:
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			program;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			stmts;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			stmt;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			tokendeclaration;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			abstraction;

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			program_stmts;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			stmts_stmt_stmts;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			stmts_empty;

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			stmt_tokendeclaration;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			tokendeclaration_abstraction_TERMINAL_REGEX;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			tokendeclaration_TERMINAL_REGEX;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			abstraction_DELETE_ABSTRACTION;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			abstraction_IGNORE_ABSTRACTION;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			abstraction_NOVALUE_ABSTRACTION;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			abstraction_CRASH_ABSTRACTION;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			abstraction_STANDARD_ABSTRACTION;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			abstraction_UNKNOWN_ABSTRACTION;

	public:
		Grammar(::DLDL::lexer::Language* language);
		~Grammar() override = default;
	};
}

#endif // DLDL_LEXER_DEFINITION_GRAMMAR_H
