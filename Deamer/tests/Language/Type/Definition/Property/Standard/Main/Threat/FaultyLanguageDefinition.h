#ifndef DEAMER_TEST_LANGUAGE_TYPE_DEFINITION_PROPERTY_STANDARD_MAIN_THREAT_FAULTYLANGUAGEDEFINITION_H
#define DEAMER_TEST_LANGUAGE_TYPE_DEFINITION_PROPERTY_STANDARD_MAIN_THREAT_FAULTYLANGUAGEDEFINITION_H

#include "Deamer/Language/Generator/Definition/Language.h"
#include "Deamer/Language/Generator/Definition/Property/Standard/Main/Threat.h"
#include "Deamer/Language/Generator/Definition/Property/User/Main/Grammar.h"
#include "Deamer/Language/Generator/Definition/Property/User/Main/Lexicon.h"
#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/Terminal.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Analyzer/Combined/Deamer/DeamerCore.h"

namespace deamer::test::language::threat::standard::generator
{
	class FaultyLanguageDefinition;

	class GenerateLexiconUsedTerminals
		: public ::deamer::language::generator::definition::property::user::Lexicon<
			  FaultyLanguageDefinition>
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

		GenerateLexiconUsedTerminals(FaultyLanguageDefinition* lang);
	};

	class GenerateGrammarUsedTerminals
		: public ::deamer::language::generator::definition::property::user::Grammar<
			  FaultyLanguageDefinition>
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
			stmt_SPACES;

		GenerateGrammarUsedTerminals(FaultyLanguageDefinition* lang);
	};

	class GenerateThreat
		: public ::deamer::language::generator::definition::property::standard::Threat<
			  FaultyLanguageDefinition, ::deamer::language::type::definition::object::main::threat::
											analyzer::deamer::DeamerCore>
	{
	public:
		GenerateThreat(FaultyLanguageDefinition* language)
			: ::deamer::language::generator::definition::property::standard::Threat<
				  FaultyLanguageDefinition, ::deamer::language::type::definition::object::main::
												threat::analyzer::deamer::DeamerCore>(language)
		{
		}
		~GenerateThreat() override = default;
	};

	class FaultyLanguageDefinition : public ::deamer::language::generator::definition::Language<
										 FaultyLanguageDefinition, GenerateLexiconUsedTerminals,
										 GenerateGrammarUsedTerminals, GenerateThreat>,
									 public GenerateLexiconUsedTerminals,
									 public GenerateGrammarUsedTerminals,
									 public GenerateThreat
	{
	public:
		FaultyLanguageDefinition()
			: GenerateLexiconUsedTerminals(this),
			  GenerateGrammarUsedTerminals(this),
			  GenerateThreat(this)
		{
		}
		~FaultyLanguageDefinition() = default;
	};

	inline GenerateLexiconUsedTerminals::GenerateLexiconUsedTerminals(
		FaultyLanguageDefinition* lang)
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

	inline GenerateGrammarUsedTerminals::GenerateGrammarUsedTerminals(
		FaultyLanguageDefinition* lang)
		: Grammar(lang)
	{
		prog.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"prog", {prog_stmts.Pointer()}));
		stmts.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"stmts", {stmts_stmt_stmts.Pointer(), stmts_empty.Pointer()}));
		stmt.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"stmt", {stmt_SPACES.Pointer()}));

		prog_stmts.Set(
			::deamer::language::type::definition::object::main::ProductionRule({stmts.Pointer()}));
		stmts_stmt_stmts.Set(::deamer::language::type::definition::object::main::ProductionRule(
			{stmt.Pointer(), stmts.Pointer()}));
		stmts_empty.Set(::deamer::language::type::definition::object::main::ProductionRule());
		stmt_SPACES.Set(::deamer::language::type::definition::object::main::ProductionRule(
			{lang->SPACES.Pointer()}));

		AddObject(prog);
		AddObject(stmts);
		AddObject(stmt);

		AddObject(prog_stmts);
		AddObject(stmts_stmt_stmts);
		AddObject(stmts_empty);
		AddObject(stmt_SPACES);
	}
}

#endif // DEAMER_TEST_LANGUAGE_TYPE_DEFINITION_PROPERTY_STANDARD_MAIN_THREAT_FAULTYLANGUAGEDEFINITION_H
