#ifndef DST_MAIN_DEFINITION_LEXICON_H
#define DST_MAIN_DEFINITION_LEXICON_H

#include "Deamer/Language/Generator/Definition/Property/User/Main/Lexicon.h"

namespace DST::main
{
	class Language;

	class Lexicon : public deamer::language::generator::definition::property::user::Lexicon<
						::DST::main::Language>
	{
	public:
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			LEFT_BRACKETS_ESCAPED; // \{{
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			RIGHT_BRACKETS_ESCAPED; // \}}

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			LEFT_BRACKETS; // {{
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			RIGHT_BRACKETS; // }}

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			LEFT_BRACKET; // {
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			RIGHT_BRACKET; // }

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			BACKSLASH; // \

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			DOT; // .

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			VARNAME; // aaa AbA abbC

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			OTHER; // anything else

	public:
		Lexicon(::DST::main::Language* language)
			: deamer::language::generator::definition::property::user::Lexicon<
				  ::DST::main::Language>(language)
		{
			LEFT_BRACKETS_ESCAPED.Set(
				new const deamer::language::type::definition::object::main::Terminal(
					"LEFT_BRACKETS_ESCAPED", "[\\\\][{][{]"));
			RIGHT_BRACKETS_ESCAPED.Set(
				new const deamer::language::type::definition::object::main::Terminal(
					"RIGHT_BRACKETS_ESCAPED", "[\\\\][}][}]"));
			BACKSLASH.Set(new const deamer::language::type::definition::object::main::Terminal(
				"BACKSLASH", "[\\\\]"));

			LEFT_BRACKETS.Set(new const deamer::language::type::definition::object::main::Terminal(
				"LEFT_BRACKETS", "[{][{]"));
			RIGHT_BRACKETS.Set(new const deamer::language::type::definition::object::main::Terminal(
				"RIGHT_BRACKETS", "[}][}]"));

			LEFT_BRACKET.Set(new const deamer::language::type::definition::object::main::Terminal(
				"LEFT_BRACKET", "[{]"));
			RIGHT_BRACKET.Set(new const deamer::language::type::definition::object::main::Terminal(
				"RIGHT_BRACKET", "[}]"));
			DOT.Set(new const deamer::language::type::definition::object::main::Terminal("DOT",
																						 "[\\.]"));

			VARNAME.Set(new const deamer::language::type::definition::object::main::Terminal(
				"VARNAME", "[a-zA-Z]+[a-zA-Z_0-9]*"));

			OTHER.Set(new const deamer::language::type::definition::object::main::Terminal(
				"OTHER", "[^{}\\\\\\.]*"));

			AddObject(DOT);
			AddObject(LEFT_BRACKETS_ESCAPED);
			AddObject(RIGHT_BRACKETS_ESCAPED);

			AddObject(LEFT_BRACKETS);
			AddObject(RIGHT_BRACKETS);

			AddObject(LEFT_BRACKET);
			AddObject(RIGHT_BRACKET);

			AddObject(VARNAME);
			AddObject(BACKSLASH);
			AddObject(OTHER);
		}

		~Lexicon() override = default;
	};
}

#endif // DST_MAIN_DEFINITION_LEXICON_H
