#ifndef DEAMER_TEST_LANGUAGE_TYPE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_MULTI_DEAMER_LEXICON_USEDTERMINALLANGUAGE_H
#define DEAMER_TEST_LANGUAGE_TYPE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_MULTI_DEAMER_LEXICON_USEDTERMINALLANGUAGE_H

#include "Deamer/Language/Generator/Definition/Language.h"
#include "Deamer/Language/Generator/Definition/Property/User/Main/Grammar.h"
#include "Deamer/Language/Generator/Definition/Property/User/Main/Lexicon.h"
#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/Terminal.h"

namespace deamer::test::language::threat::deamer::unusedterminal
{
	class LanguageDefinitionUsedTerminals;

	class GenerateLexiconUsedTerminals
		: public ::deamer::language::generator::definition::property::user::Lexicon<
			  LanguageDefinitionUsedTerminals>
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

		GenerateLexiconUsedTerminals(LanguageDefinitionUsedTerminals* lang);
	};

	class GenerateGrammarUsedTerminals
		: public ::deamer::language::generator::definition::property::user::Grammar<
			  LanguageDefinitionUsedTerminals>
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
		
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			stmt_VARNAME;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			stmt_STRING;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			stmt_ESCAPE_CHARS;


		GenerateGrammarUsedTerminals(LanguageDefinitionUsedTerminals* lang);
	};

	class LanguageDefinitionUsedTerminals
		: public ::deamer::language::generator::definition::Language<
			  LanguageDefinitionUsedTerminals, GenerateLexiconUsedTerminals,
			  GenerateGrammarUsedTerminals>,
		  public GenerateLexiconUsedTerminals,
		  public GenerateGrammarUsedTerminals
	{
	public:
		LanguageDefinitionUsedTerminals()
			: GenerateLexiconUsedTerminals(this),
			  GenerateGrammarUsedTerminals(this)
		{
		}
		~LanguageDefinitionUsedTerminals() = default;
	};

	inline GenerateLexiconUsedTerminals::GenerateLexiconUsedTerminals(
		LanguageDefinitionUsedTerminals* lang)
		: Lexicon(lang)
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

	inline GenerateGrammarUsedTerminals::GenerateGrammarUsedTerminals(
		LanguageDefinitionUsedTerminals* lang)
		: Grammar(lang)
	{
		prog.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"prog", {prog_stmts.Pointer()}));
		stmts.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"stmts", {stmts_stmt_stmts.Pointer(), stmts_empty.Pointer()}));
		stmt.Set(::deamer::language::type::definition::object::main::NonTerminal("stmt", {stmt_VARNAME.Pointer(), stmt_STRING.Pointer(), stmt_ESCAPE_CHARS.Pointer()}));

		prog_stmts.Set(
			::deamer::language::type::definition::object::main::ProductionRule({stmts.Pointer()}));
		stmts_stmt_stmts.Set(::deamer::language::type::definition::object::main::ProductionRule(
			{stmt.Pointer(), stmts.Pointer()}));
		stmts_empty.Set(::deamer::language::type::definition::object::main::ProductionRule());

		stmt_VARNAME.Set(::deamer::language::type::definition::object::main::ProductionRule({lang->VARNAME.Pointer()}));
		stmt_STRING.Set(::deamer::language::type::definition::object::main::ProductionRule(
			{lang->STRING.Pointer()}));
		stmt_ESCAPE_CHARS.Set(::deamer::language::type::definition::object::main::ProductionRule(
			{lang->ESCAPE_CHARS.Pointer()}));

		AddObject(prog);
		AddObject(stmts);
		AddObject(stmt);

		AddObject(prog_stmts);
		AddObject(stmts_stmt_stmts);
		AddObject(stmts_empty);
		AddObject(stmt_VARNAME);
		AddObject(stmt_STRING);
		AddObject(stmt_ESCAPE_CHARS);
	}
}

#endif // DEAMER_TEST_LANGUAGE_TYPE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_MULTI_DEAMER_LEXICON_USEDTERMINALLANGUAGE_H
