#ifndef DST_SETTING_DEFINITION_GRAMMAR_H
#define DST_SETTING_DEFINITION_GRAMMAR_H

#include "Deamer/Language/Generator/Definition/Property/User/Main/Grammar.h"

namespace DST::setting
{
	class Language;

	class Grammar : public deamer::language::generator::definition::property::user::Grammar<
						::DST::setting::Language>
	{
	public:
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			program;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			stmts;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			stmt;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			abstraction;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			special;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			variable_declaration;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			main_assignment;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			keyword_assignment;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			scope;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			user_keyword;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
			dst_keyword;

		// Production rules
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			program_stmts;

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			stmts_stmt_stmts;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			stmts_empty;

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			stmt_abstraction;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			stmt_special;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			abstraction_variable_declaration_EQUAL_main_assignment;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			special_variable_declaration_EQUAL_keyword_assignment;

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			variable_declaration_LEFT_BRACKETS_VARNAME_RIGHT_BRACKETS;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			variable_declaration_LEFT_BRACKETS_VARNAME_scope_RIGHT_BRACKETS;

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			scope_DOT_VARNAME_scope;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			scope_DOT_VARNAME;

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			main_assignment_USER_INPUT;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			keyword_assignment_user_keyword;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			user_keyword_LEFT_SQUARE_BRACKET_VARNAME_RIGHT_SQUARE_BRACKET;

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			keyword_assignment_dst_keyword;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule>
			dst_keyword_INVALID;

	public:
		Grammar(::DST::setting::Language* language);
		~Grammar() override = default;
	};
}

#endif // DST_SETTING_DEFINITION_GRAMMAR_H
