#ifndef DST_SETTING_DEFINITION_LEXICON_H
#define DST_SETTING_DEFINITION_LEXICON_H

#include "Deamer/Language/Generator/Definition/Property/User/Main/Lexicon.h"

namespace DST::setting
{
	class Language;

	class Lexicon : public deamer::language::generator::definition::property::user::Lexicon<
						::DST::setting::Language>
	{
	public:
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			LEFT_BRACKETS; // {{
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			RIGHT_BRACKETS; // }}

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			DOT; // .
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			ADD_ASSIGNMENT; // +=
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			EQUAL; // =

		// Standard top-level keywords
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			INVALID; // [invalid] [Invalid]

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			LEFT_SQUARE_BRACKET; // [
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			RIGHT_SQUARE_BRACKET; // ]

		// User input
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			USER_INPUT; // <anything>

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			VARNAME; // aaa AbA abbC

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			OTHER; // aaa AbA abbC

	public:
		Lexicon(::DST::setting::Language* language)
			: deamer::language::generator::definition::property::user::Lexicon<
				  ::DST::setting::Language>(language)
		{
			LEFT_BRACKETS.Set(new const deamer::language::type::definition::object::main::Terminal(
				"LEFT_BRACKETS", "[{][{]"));
			RIGHT_BRACKETS.Set(new const deamer::language::type::definition::object::main::Terminal(
				"RIGHT_BRACKETS", "[}][}]"));

			DOT.Set(new const deamer::language::type::definition::object::main::Terminal("DOT",
																						 "[\\.]"));
			EQUAL.Set(new const deamer::language::type::definition::object::main::Terminal("EQUAL",
																						   "[=]"));
			ADD_ASSIGNMENT.Set(new const deamer::language::type::definition::object::main::Terminal(
				"ADD_ASSIGNMENT", "[+][=]"));

			INVALID.Set(new const deamer::language::type::definition::object::main::Terminal(
				"INVALID", "[\\[][Ii]nvalid[\\]]"));

			LEFT_SQUARE_BRACKET.Set(
				new const deamer::language::type::definition::object::main::Terminal(
					"LEFT_SQUARE_BRACKET", "[\\[]"));
			RIGHT_SQUARE_BRACKET.Set(
				new const deamer::language::type::definition::object::main::Terminal(
					"RIGHT_SQUARE_BRACKET", "[\\]]"));

			USER_INPUT.Set(new const deamer::language::type::definition::object::main::Terminal(
				"USER_INPUT", "[<][^>]*[>]"));

			VARNAME.Set(new const deamer::language::type::definition::object::main::Terminal(
				"VARNAME", "[a-zA-Z]+[a-zA-Z_0-9]*"));

			OTHER.Set(new const deamer::language::type::definition::object::main::Terminal(
				"OTHER", "[\\n\\r\\t\\b\\f\\v\\a ]*",
				deamer::language::type::definition::object::main::SpecialType::Delete));

			AddObject(LEFT_BRACKETS);
			AddObject(RIGHT_BRACKETS);

			AddObject(DOT);
			AddObject(ADD_ASSIGNMENT);
			AddObject(EQUAL);

			AddObject(INVALID);

			AddObject(LEFT_SQUARE_BRACKET);
			AddObject(RIGHT_SQUARE_BRACKET);

			AddObject(USER_INPUT);

			AddObject(VARNAME);

			AddObject(OTHER);
		}

		~Lexicon() override = default;
	};
}

#endif // DST_SETTING_DEFINITION_LEXICON_H
