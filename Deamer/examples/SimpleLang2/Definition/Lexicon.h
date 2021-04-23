#ifndef SIMPLELANG2_DEFINITION_LEXICON_H
#define SIMPLELANG2_DEFINITION_LEXICON_H

#include "Deamer/Language/Generator/Definition/Property/User/Main/Lexicon.h"

namespace simplelang
{
	class Language;

	class Lexicon : public deamer::language::generator::definition::property::user::Lexicon<
						simplelang::Language>
	{
	public:
		const deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			NEWLINE;
		const deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			ESCAPE_CHARS;
		const deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			SPACES;

		const deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			SEMICOLON;
		const deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			EQUAL;

		const deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			FUNCTION_DECLARATION;
		const deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			VAR_DECLARATION;
		const deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			CRASH_PROGRAM;

		const deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			VARNAME;
		const deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			NUMBER;

	public:
		Lexicon(simplelang::Language* language)
			: deamer::language::generator::definition::property::user::Lexicon<
				  simplelang::Language>(language)
		{
			NEWLINE.Set(deamer::language::type::definition::object::main::Terminal(
				"NEWLINE", "[\\n]",
				deamer::language::type::definition::object::main::SpecialType::Delete));
			AddObject(NEWLINE);
			ESCAPE_CHARS.Set(deamer::language::type::definition::object::main::Terminal(
				"ESCAPE_CHARS", "[\\r\\t\\f\\b]",
				deamer::language::type::definition::object::main::SpecialType::Delete));
			AddObject(ESCAPE_CHARS);
			SPACES.Set(deamer::language::type::definition::object::main::Terminal(
				"SPACES", "[ ]+",
				deamer::language::type::definition::object::main::SpecialType::Delete));
			AddObject(SPACES);

			SEMICOLON.Set(deamer::language::type::definition::object::main::Terminal(
				"SEMICOLON", ";",
				deamer::language::type::definition::object::main::SpecialType::Ignore));
			AddObject(SEMICOLON);
			EQUAL.Set(deamer::language::type::definition::object::main::Terminal(
				"EQUAL", "=",
				deamer::language::type::definition::object::main::SpecialType::Ignore));
			AddObject(EQUAL);

			FUNCTION_DECLARATION.Set(deamer::language::type::definition::object::main::Terminal(
				"FUNCTION_DECLARATION", "def",
				deamer::language::type::definition::object::main::SpecialType::Ignore));
			AddObject(FUNCTION_DECLARATION);
			VAR_DECLARATION.Set(deamer::language::type::definition::object::main::Terminal(
				"VAR_DECLARATION", "var",
				deamer::language::type::definition::object::main::SpecialType::Ignore));
			AddObject(VAR_DECLARATION);
			CRASH_PROGRAM.Set(deamer::language::type::definition::object::main::Terminal(
				"CRASH_PROGRAM", "crash_program",
				deamer::language::type::definition::object::main::SpecialType::Crash));
			AddObject(CRASH_PROGRAM);

			VARNAME.Set(deamer::language::type::definition::object::main::Terminal(
				"VARNAME", "[a-zA-Z]+[a-zA-Z0-9_]*"));
			AddObject(VARNAME);
			NUMBER.Set(
				deamer::language::type::definition::object::main::Terminal("NUMBER", "[0-9]+"));
			AddObject(NUMBER);
		}
		~Lexicon() override = default;
	};
}

#endif // SIMPLELANG2_DEFINITION_LEXICON_H
