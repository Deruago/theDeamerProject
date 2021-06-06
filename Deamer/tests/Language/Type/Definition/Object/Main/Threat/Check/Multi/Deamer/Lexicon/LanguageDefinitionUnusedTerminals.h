#ifndef DEAMER_TEST_LANGUAGE_TYPE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_MULTI_DEAMER_LEXICON_UNUSEDTERMINALLANGUAGE_H
#define DEAMER_TEST_LANGUAGE_TYPE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_MULTI_DEAMER_LEXICON_UNUSEDTERMINALLANGUAGE_H

#include "Deamer/Language/Generator/Definition/Language.h"
#include "Deamer/Language/Generator/Definition/Property/User/Main/Grammar.h"
#include "Deamer/Language/Generator/Definition/Property/User/Main/Lexicon.h"
#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/Terminal.h"

namespace deamer::test::language::threat::deamer::unusedterminal
{
	class LanguageDefinitionUnusedTerminals;

	class GenerateLexiconUnusedTerminals
		: public ::deamer::language::generator::definition::property::user::Lexicon<
			  LanguageDefinitionUnusedTerminals>
	{
	public:
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			STRING;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			VARNAME;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			ESCAPE_CHARS;

		GenerateLexiconUnusedTerminals(LanguageDefinitionUnusedTerminals* lang);
	};

	class GenerateGrammarUnusedTerminals
		: public ::deamer::language::generator::definition::property::user::Grammar<
			  LanguageDefinitionUnusedTerminals>
	{
	public:
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::NonTerminal>
			prog;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::NonTerminal>
			stmts;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::NonTerminal>
			stmt;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			prog_stmts;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			stmts_stmt_stmts;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			stmts_empty;

		GenerateGrammarUnusedTerminals(LanguageDefinitionUnusedTerminals* lang);
	};

	class LanguageDefinitionUnusedTerminals : public ::deamer::language::generator::definition::Language<
								   LanguageDefinitionUnusedTerminals, GenerateLexiconUnusedTerminals, GenerateGrammarUnusedTerminals>,
							   public GenerateLexiconUnusedTerminals,
							   public GenerateGrammarUnusedTerminals
	{
	public:
		LanguageDefinitionUnusedTerminals() : GenerateLexiconUnusedTerminals(this), GenerateGrammarUnusedTerminals(this)
		{
		}
		~LanguageDefinitionUnusedTerminals() = default;
	};

	inline GenerateLexiconUnusedTerminals::GenerateLexiconUnusedTerminals(LanguageDefinitionUnusedTerminals* lang) : Lexicon(lang)
	{
		VARNAME.Set(::deamer::language::type::definition::object::main::Terminal(
			"VARNAME", "[a-zA-Z]+[a-zA-Z_0-9]*"));

		ESCAPE_CHARS.Set(::deamer::language::type::definition::object::main::Terminal(
			"ESCAPE_CHARS", "[\n\r\t\f ]*"));

		STRING.Set(::deamer::language::type::definition::object::main::Terminal("STRING",
																				R"(["][^"]*["])"));

		AddObject(VARNAME);
		AddObject(STRING);
		AddObject(ESCAPE_CHARS);
	}

	inline GenerateGrammarUnusedTerminals::GenerateGrammarUnusedTerminals(LanguageDefinitionUnusedTerminals* lang) : Grammar(lang)
	{
		prog.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"prog", {prog_stmts.Pointer()}));
		stmts.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"stmts", {stmts_stmt_stmts.Pointer(), stmts_empty.Pointer()}));
		stmt.Set(::deamer::language::type::definition::object::main::NonTerminal("stmt", {}));

		prog_stmts.Set(
			::deamer::language::type::definition::object::main::ProductionRule({stmts.Pointer()}));
		stmts_stmt_stmts.Set(::deamer::language::type::definition::object::main::ProductionRule(
			{stmt.Pointer(), stmts.Pointer()}));
		stmts_empty.Set(::deamer::language::type::definition::object::main::ProductionRule());

		AddObject(prog);
		AddObject(stmts);
		AddObject(stmt);

		AddObject(prog_stmts);
		AddObject(stmts_stmt_stmts);
		AddObject(stmts_empty);
	}
}

#endif // DEAMER_TEST_LANGUAGE_TYPE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_MULTI_DEAMER_LEXICON_UNUSEDTERMINALLANGUAGE_H
