#ifndef DEAMER_TEST_LANGUAGE_ANALYZER_MAIN_GRAMMAR_LANGUAGE_ENDINGTERMINALLANGUAGE_H
#define DEAMER_TEST_LANGUAGE_ANALYZER_MAIN_GRAMMAR_LANGUAGE_ENDINGTERMINALLANGUAGE_H

#include "Deamer/Language/Generator/Definition/Language.h"
#include "Deamer/Language/Generator/Definition/Property/Standard/Main/Threat.h"
#include "Deamer/Language/Generator/Definition/Property/User/Main/Grammar.h"
#include "Deamer/Language/Generator/Definition/Property/User/Main/Lexicon.h"
#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/Terminal.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Analyzer/Combined/Deamer/DeamerCore.h"

namespace deamer::test::language::analyzer::grammar::language::nonterminal
{
	class EndingTerminalLanguage;

	class GenerateLexiconUsedTerminals
		: public ::deamer::language::generator::definition::property::user::Lexicon<
			  EndingTerminalLanguage>
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

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			SPACES;

		GenerateLexiconUsedTerminals(EndingTerminalLanguage* lang);
	};

	class GenerateGrammarUsedTerminals
		: public ::deamer::language::generator::definition::property::user::Grammar<
			  EndingTerminalLanguage>
	{
	public:
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::NonTerminal>
			prog;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::NonTerminal>
			stmtalternative;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::NonTerminal>
			stmts;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::NonTerminal>
			stmts2;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::NonTerminal>
			stmts_one_or_more;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::NonTerminal>
			stmt;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			prog_stmts;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			prog_stmtalternative;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			prog_stmts2;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			prog_stmts_one_or_more;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			stmts2_stmt_stmts2_stmts2;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			stmts2_empty;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			stmts_one_or_more_stmt_stmtalternative_stmts_one_or_more;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			stmts_one_or_more_stmt;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			stmts_stmt_stmts;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			stmts_empty;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			stmtalternative_VARNAME;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			stmt_SPACES;

		GenerateGrammarUsedTerminals(EndingTerminalLanguage* lang);
	};

	class GenerateThreat
		: public ::deamer::language::generator::definition::property::standard::Threat<
			  EndingTerminalLanguage, ::deamer::language::type::definition::object::main::threat::
										  analyzer::deamer::DeamerCore>
	{
	public:
		GenerateThreat(EndingTerminalLanguage* language)
			: ::deamer::language::generator::definition::property::standard::Threat<
				  EndingTerminalLanguage, ::deamer::language::type::definition::object::main::
											  threat::analyzer::deamer::DeamerCore>(language)
		{
		}
		~GenerateThreat() override = default;
	};

	class EndingTerminalLanguage : public ::deamer::language::generator::definition::Language<
									   EndingTerminalLanguage, GenerateLexiconUsedTerminals,
									   GenerateGrammarUsedTerminals, GenerateThreat>,
								   public GenerateLexiconUsedTerminals,
								   public GenerateGrammarUsedTerminals,
								   public GenerateThreat
	{
	public:
		EndingTerminalLanguage()
			: GenerateLexiconUsedTerminals(this),
			  GenerateGrammarUsedTerminals(this),
			  GenerateThreat(this)
		{
		}
		~EndingTerminalLanguage() = default;
	};

	inline GenerateLexiconUsedTerminals::GenerateLexiconUsedTerminals(EndingTerminalLanguage* lang)
		: Lexicon(lang)
	{
		VARNAME.Set(::deamer::language::type::definition::object::main::Terminal(
			"VARNAME", "[a-zA-Z]+[a-zA-Z_0-9]*"));

		ESCAPE_CHARS.Set(::deamer::language::type::definition::object::main::Terminal(
			"ESCAPE_CHARS", "[\n\r\t\f]*"));

		STRING.Set(::deamer::language::type::definition::object::main::Terminal("STRING",
																				R"(["][^"]*["])"));

		SPACES.Set(::deamer::language::type::definition::object::main::Terminal(
			"SPACES", "[ ]+",
			::deamer::language::type::definition::object::main::SpecialType::Delete));

		AddObject(VARNAME);
		AddObject(STRING);
		AddObject(ESCAPE_CHARS);
		AddObject(SPACES);
	}

	inline GenerateGrammarUsedTerminals::GenerateGrammarUsedTerminals(EndingTerminalLanguage* lang)
		: Grammar(lang)
	{
		prog.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"prog",
			{prog_stmts.Pointer(), prog_stmts2.Pointer(), prog_stmts_one_or_more.Pointer()}));
		stmts.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"stmts", {stmts_stmt_stmts.Pointer(), stmts_empty.Pointer()}));

		stmts2.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"stmts2", {stmts2_stmt_stmts2_stmts2.Pointer(), stmts2_empty.Pointer()}));
		stmts_one_or_more.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"stmts_one_or_more",
			{stmts_one_or_more_stmt_stmtalternative_stmts_one_or_more.Pointer(),
			 stmts_one_or_more_stmt.Pointer()}));
		stmt.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"stmt", {stmt_SPACES.Pointer()}));
		stmtalternative.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"stmtalternative", {stmtalternative_VARNAME.Pointer()}));

		prog_stmts.Set(
			::deamer::language::type::definition::object::main::ProductionRule({stmts.Pointer()}));
		prog_stmts2.Set(
			::deamer::language::type::definition::object::main::ProductionRule({stmts2.Pointer()}));
		prog_stmts_one_or_more.Set(
			::deamer::language::type::definition::object::main::ProductionRule(
				{stmts_one_or_more.Pointer()}));
		prog_stmtalternative.Set(::deamer::language::type::definition::object::main::ProductionRule(
			{stmtalternative.Pointer()}));

		stmts_one_or_more_stmt_stmtalternative_stmts_one_or_more.Set(
			::deamer::language::type::definition::object::main::ProductionRule(
				{stmt.Pointer(), stmtalternative.Pointer(), stmts_one_or_more.Pointer()}));
		stmts_one_or_more_stmt.Set(
			::deamer::language::type::definition::object::main::ProductionRule({stmt.Pointer()}));

		stmts2_stmt_stmts2_stmts2.Set(
			::deamer::language::type::definition::object::main::ProductionRule(
				{stmt.Pointer(), stmts2.Pointer(), stmts2.Pointer()}));
		stmts2_empty.Set(::deamer::language::type::definition::object::main::ProductionRule());

		stmts_stmt_stmts.Set(::deamer::language::type::definition::object::main::ProductionRule(
			{stmt.Pointer(), stmts.Pointer()}));
		stmts_empty.Set(::deamer::language::type::definition::object::main::ProductionRule());
		stmtalternative_VARNAME.Set(
			::deamer::language::type::definition::object::main::ProductionRule(
				{lang->VARNAME.Pointer()}));
		stmt_SPACES.Set(::deamer::language::type::definition::object::main::ProductionRule(
			{lang->SPACES.Pointer()}));

		AddObject(prog);
		AddObject(stmts);
		AddObject(stmts2);
		AddObject(stmts_one_or_more);
		AddObject(stmt);
		AddObject(stmtalternative);

		AddObject(prog_stmts);
		AddObject(prog_stmts2);
		AddObject(prog_stmtalternative);
		AddObject(prog_stmts_one_or_more);

		AddObject(stmts_one_or_more_stmt_stmtalternative_stmts_one_or_more);
		AddObject(stmts_one_or_more_stmt);

		AddObject(stmts2_stmt_stmts2_stmts2);
		AddObject(stmts2_empty);

		AddObject(stmts_stmt_stmts);
		AddObject(stmts_empty);

		AddObject(stmtalternative_VARNAME);
		AddObject(stmt_SPACES);
	}
}

#endif // DEAMER_TEST_LANGUAGE_ANALYZER_MAIN_GRAMMAR_LANGUAGE_ENDINGTERMINALLANGUAGE_H
