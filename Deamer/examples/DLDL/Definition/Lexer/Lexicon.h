#ifndef DLDL_LEXER_DEFINITION_LEXICON_H
#define DLDL_LEXER_DEFINITION_LEXICON_H

#include "Deamer/Language/Generator/Definition/Property/User/Main/Lexicon.h"

namespace DLDL::lexer
{
	class Language;

	class Lexicon : public deamer::language::generator::definition::property::user::Lexicon<
						::DLDL::lexer::Language>
	{
	public:
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			COMMENT;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			DELETE_ABSTRACTION;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			IGNORE_ABSTRACTION;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			NOVALUE_ABSTRACTION;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			CRASH_ABSTRACTION;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			STANDARD_ABSTRACTION;

		// Used to find unknown abstractions.
		// In later stages error can be throwed for invalid abstraction usage.
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			UNKNOWN_ABSTRACTION;

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			TERMINAL;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal> REGEX;

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			ESCAPE_CHARS;

	public:
		Lexicon(::DLDL::lexer::Language* language)
			: deamer::language::generator::definition::property::user::Lexicon<
				  ::DLDL::lexer::Language>(language)
		{
			COMMENT.Set(new const deamer::language::type::definition::object::main::Terminal(
				"COMMENT", "[/][^\\r\\n]*",
				deamer::language::type::definition::object::main::SpecialType::Delete));

			DELETE_ABSTRACTION.Set(
				new const deamer::language::type::definition::object::main::Terminal(
					"DELETE_ABSTRACTION", "[Dd]elete[:][ ]*",
					deamer::language::type::definition::object::main::SpecialType::NoValue));
			IGNORE_ABSTRACTION.Set(
				new const deamer::language::type::definition::object::main::Terminal(
					"IGNORE_ABSTRACTION", "[Ii]gnore[:][ ]*",
					deamer::language::type::definition::object::main::SpecialType::NoValue));
			NOVALUE_ABSTRACTION.Set(
				new const deamer::language::type::definition::object::main::Terminal(
					"NOVALUE_ABSTRACTION", "(([Nn]o[Vv]alue)|([Vv]alue[Ll]ess))[:][ ]*",
					deamer::language::type::definition::object::main::SpecialType::NoValue));
			CRASH_ABSTRACTION.Set(
				new const deamer::language::type::definition::object::main::Terminal(
					"CRASH_ABSTRACTION", "[Cc]rash[:][ ]*",
					deamer::language::type::definition::object::main::SpecialType::NoValue));
			STANDARD_ABSTRACTION.Set(
				new const deamer::language::type::definition::object::main::Terminal(
					"STANDARD_ABSTRACTION", "[Ss]tandard[:][ ]*",
					deamer::language::type::definition::object::main::SpecialType::NoValue));
			UNKNOWN_ABSTRACTION.Set(
				new const deamer::language::type::definition::object::main::Terminal(
					"UNKNOWN_ABSTRACTION", "[a-zA-Z0-9_\\\\$?!-+=]*[:][ ]*"));

			TERMINAL.Set(new const deamer::language::type::definition::object::main::Terminal(
				"TERMINAL", "[a-zA-Z_]+"));
			REGEX.Set(new const deamer::language::type::definition::object::main::Terminal(
				"REGEX", "[ \\t][^\\r\\n]*"));
			ESCAPE_CHARS.Set(new const deamer::language::type::definition::object::main::Terminal(
				"ESCAPE_CHARS", "[\\n\\r\\t\\f\\b\\a\\v]",
				deamer::language::type::definition::object::main::SpecialType::Delete));

			AddObject(COMMENT);

			AddObject(DELETE_ABSTRACTION);
			AddObject(IGNORE_ABSTRACTION);
			AddObject(NOVALUE_ABSTRACTION);
			AddObject(CRASH_ABSTRACTION);
			AddObject(STANDARD_ABSTRACTION);

			AddObject(UNKNOWN_ABSTRACTION);

			AddObject(TERMINAL);
			AddObject(REGEX);
			AddObject(ESCAPE_CHARS);
		}

		~Lexicon() override = default;
	};
}

#endif // DLDL_LEXER_DEFINITION_LEXICON_H
