#ifndef DLDL_GRAMMAR_DEFINITION_LEXICON_H
#define DLDL_GRAMMAR_DEFINITION_LEXICON_H

#include "Deamer/Language/Generator/Definition/Property/User/Main/Lexicon.h"

namespace DLDL::grammar
{
	class Language;

	class Lexicon : public deamer::language::generator::definition::property::user::Lexicon<
						::DLDL::grammar::Language>
	{
	public:
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			COMMENT;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			START_ABSTRACTION;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			GROUP_ABSTRACTION;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			UNKNOWN_ABSTRACTION;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			NONTERMINAL;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			PRODUCTION_RULE;

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
			ESCAPE_CHARS;

	public:
		Lexicon(::DLDL::grammar::Language* language)
			: deamer::language::generator::definition::property::user::Lexicon<
				  ::DLDL::grammar::Language>(language)
		{
			COMMENT.Set(new const deamer::language::type::definition::object::main::Terminal(
				"COMMENT", "[/][^\\n]*",
				deamer::language::type::definition::object::main::SpecialType::Delete));
			START_ABSTRACTION.Set(
				new const deamer::language::type::definition::object::main::Terminal(
					"START_ABSTRACTION", "[Ss]tart[:][ \\t]*",
					deamer::language::type::definition::object::main::SpecialType::NoValue));
			GROUP_ABSTRACTION.Set(
				new const deamer::language::type::definition::object::main::Terminal(
					"GROUP_ABSTRACTION", "[Gg]roup[:][ \\t]*",
					deamer::language::type::definition::object::main::SpecialType::NoValue));
			UNKNOWN_ABSTRACTION.Set(
				new const deamer::language::type::definition::object::main::Terminal(
					"UNKNOWN_ABSTRACTION", "[a-zA-Z0-9_\\\\$?!-+=]*[:][ \\t]*"));

			NONTERMINAL.Set(new const deamer::language::type::definition::object::main::Terminal(
				"NONTERMINAL", "[a-zA-Z_]+"));
			PRODUCTION_RULE.Set(
				new const deamer::language::type::definition::object::main::Terminal(
					"PRODUCTION_RULE", "[ \\t]+[^\\r\\n]*"));

			ESCAPE_CHARS.Set(new const deamer::language::type::definition::object::main::Terminal(
				"ESCAPE_CHARS", "[\\n\\r\\b\\v\\a\\f\\t ]",
				deamer::language::type::definition::object::main::SpecialType::Delete));

			AddObject(COMMENT);

			AddObject(START_ABSTRACTION);
			AddObject(GROUP_ABSTRACTION);
			AddObject(UNKNOWN_ABSTRACTION);

			AddObject(NONTERMINAL);
			AddObject(PRODUCTION_RULE);

			AddObject(ESCAPE_CHARS);
		}

		~Lexicon() override = default;
	};
}

#endif // DLDL_GRAMMAR_DEFINITION_LEXICON_H
