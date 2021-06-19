#ifndef DEAMER_TEST_LANGUAGE_ANALYZER_MAIN_GRAMMAR_LANGUAGE_TERMINALNEIGHBORS_H
#define DEAMER_TEST_LANGUAGE_ANALYZER_MAIN_GRAMMAR_LANGUAGE_TERMINALNEIGHBORS_H

#include "Deamer/Language/Generator/Definition/Language.h"
#include "Deamer/Language/Generator/Definition/Property/Standard/Main/Threat.h"
#include "Deamer/Language/Generator/Definition/Property/User/Main/Grammar.h"
#include "Deamer/Language/Generator/Definition/Property/User/Main/Lexicon.h"
#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/Terminal.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Analyzer/Combined/Deamer/DeamerCore.h"

namespace deamer::test::language::analyzer::grammar::language::terminal
{
	class TerminalNeighbors;

	class GenerateLexiconUsedTerminals
		: public ::deamer::language::generator::definition::property::user::Lexicon<
			  TerminalNeighbors>
	{
	public:
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			VARNAME;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			EQUAL;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			INTEGER_TYPE;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			DOUBLE_TYPE;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			FLOAT_TYPE;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			NUMBER;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			STRING;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			ESCAPE_CHARS;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			SPACES;

		GenerateLexiconUsedTerminals(TerminalNeighbors* lang);
	};

	class GenerateGrammarUsedTerminals
		: public ::deamer::language::generator::definition::property::user::Grammar<
			  TerminalNeighbors>
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
			::deamer::language::type::definition::object::main::NonTerminal>
			variable_initialization;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::NonTerminal>
			type;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::NonTerminal>
			value;

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
			stmt_variable_initialization;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			variable_initialization_type_VARNAME_EQUAL_value;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			type_INTEGER_TYPE;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			type_DOUBLE_TYPE;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			type_FLOAT_TYPE;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			value_STRING;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			value_VARNAME;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			value_NUMBER;

		GenerateGrammarUsedTerminals(TerminalNeighbors* lang);
	};

	class GenerateThreat
		: public ::deamer::language::generator::definition::property::standard::Threat<
			  TerminalNeighbors, ::deamer::language::type::definition::object::main::threat::
									 analyzer::deamer::DeamerCore>
	{
	public:
		GenerateThreat(TerminalNeighbors* language)
			: ::deamer::language::generator::definition::property::standard::Threat<
				  TerminalNeighbors, ::deamer::language::type::definition::object::main::threat::
										 analyzer::deamer::DeamerCore>(language)
		{
		}
		~GenerateThreat() override = default;
	};

	class GenerateColorization
		: public ::deamer::language::generator::definition::property::standard::Colorization<
			  TerminalNeighbors>
	{
	public:
		GenerateColorization(TerminalNeighbors* language) : Colorization(language)
		{
		}
		~GenerateColorization() override = default;
	};

	class TerminalNeighbors
		: public ::deamer::language::generator::definition::Language<
			  TerminalNeighbors, GenerateLexiconUsedTerminals, GenerateGrammarUsedTerminals,
			  GenerateThreat, GenerateColorization>,
		  public GenerateLexiconUsedTerminals,
		  public GenerateGrammarUsedTerminals,
		  public GenerateThreat,
		  public GenerateColorization
	{
	public:
		TerminalNeighbors()
			: GenerateLexiconUsedTerminals(this),
			  GenerateGrammarUsedTerminals(this),
			  GenerateThreat(this),
			  GenerateColorization(this)
		{
		}
		~TerminalNeighbors() = default;
	};

	inline GenerateLexiconUsedTerminals::GenerateLexiconUsedTerminals(TerminalNeighbors* lang)
		: Lexicon(lang)
	{
		EQUAL.Set(::deamer::language::type::definition::object::main::Terminal("EQUAL", "[=]"));

		INTEGER_TYPE.Set(
			::deamer::language::type::definition::object::main::Terminal("INTEGER_TYPE", "Int"));
		DOUBLE_TYPE.Set(
			::deamer::language::type::definition::object::main::Terminal("DOUBLE_TYPE", "Double"));
		FLOAT_TYPE.Set(
			::deamer::language::type::definition::object::main::Terminal("FLOAT_TYPE", "Float"));

		STRING.Set(::deamer::language::type::definition::object::main::Terminal("STRING",
																				R"(["][^"]*["])"));
		NUMBER.Set(
			::deamer::language::type::definition::object::main::Terminal("NUMBER", "[0-9]+"));
		VARNAME.Set(::deamer::language::type::definition::object::main::Terminal(
			"VARNAME", "[a-zA-Z]+[a-zA-Z_0-9]*"));

		SPACES.Set(::deamer::language::type::definition::object::main::Terminal(
			"SPACES", "[ ]+",
			::deamer::language::type::definition::object::main::SpecialType::Delete));
		ESCAPE_CHARS.Set(::deamer::language::type::definition::object::main::Terminal(
			"ESCAPE_CHARS", "[\n\r\t\f]*",
			::deamer::language::type::definition::object::main::SpecialType::Delete));

		AddObject(EQUAL);
		AddObject(INTEGER_TYPE);
		AddObject(DOUBLE_TYPE);
		AddObject(FLOAT_TYPE);
		AddObject(STRING);
		AddObject(NUMBER);
		AddObject(VARNAME);
		AddObject(SPACES);
		AddObject(ESCAPE_CHARS);
	}

	inline GenerateGrammarUsedTerminals::GenerateGrammarUsedTerminals(TerminalNeighbors* lang)
		: Grammar(lang)
	{
		prog.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"prog", {prog_stmts.Pointer()}));
		stmts.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"stmts", {stmts_stmt_stmts.Pointer(), stmts_empty.Pointer()}));
		stmt.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"stmt", {stmt_variable_initialization.Pointer()}));
		variable_initialization.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"variable_initialization",
			{variable_initialization_type_VARNAME_EQUAL_value.Pointer()}));
		type.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"type",
			{type_INTEGER_TYPE.Pointer(), type_DOUBLE_TYPE.Pointer(), type_FLOAT_TYPE.Pointer()}));
		value.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"value", {value_NUMBER.Pointer(), value_STRING.Pointer(), value_VARNAME.Pointer()}));

		prog_stmts.Set(
			::deamer::language::type::definition::object::main::ProductionRule({stmts.Pointer()}));

		stmts_stmt_stmts.Set(::deamer::language::type::definition::object::main::ProductionRule(
			{stmt.Pointer(), stmts.Pointer()}));
		stmts_empty.Set(::deamer::language::type::definition::object::main::ProductionRule());

		stmt_variable_initialization.Set(
			::deamer::language::type::definition::object::main::ProductionRule(
				{variable_initialization.Pointer()}));

		variable_initialization_type_VARNAME_EQUAL_value.Set(
			::deamer::language::type::definition::object::main::ProductionRule(
				{type.Pointer(), lang->VARNAME.Pointer(), lang->EQUAL.Pointer(), value.Pointer()}));

		type_INTEGER_TYPE.Set(::deamer::language::type::definition::object::main::ProductionRule(
			{lang->INTEGER_TYPE.Pointer()}));
		type_DOUBLE_TYPE.Set(::deamer::language::type::definition::object::main::ProductionRule(
			{lang->DOUBLE_TYPE.Pointer()}));
		type_FLOAT_TYPE.Set(::deamer::language::type::definition::object::main::ProductionRule(
			{lang->FLOAT_TYPE.Pointer()}));

		value_NUMBER.Set(::deamer::language::type::definition::object::main::ProductionRule(
			{lang->NUMBER.Pointer()}));
		value_STRING.Set(::deamer::language::type::definition::object::main::ProductionRule(
			{lang->STRING.Pointer()}));
		value_VARNAME.Set(::deamer::language::type::definition::object::main::ProductionRule(
			{lang->VARNAME.Pointer()}));

		AddObject(prog);
		AddObject(stmts);
		AddObject(stmt);
		AddObject(variable_initialization);
		AddObject(type);
		AddObject(value);

		AddObject(prog_stmts);

		AddObject(stmts_stmt_stmts);
		AddObject(stmts_empty);

		AddObject(stmt_variable_initialization);

		AddObject(variable_initialization_type_VARNAME_EQUAL_value);

		AddObject(type_INTEGER_TYPE);
		AddObject(type_DOUBLE_TYPE);
		AddObject(type_FLOAT_TYPE);

		AddObject(value_NUMBER);
		AddObject(value_STRING);
		AddObject(value_VARNAME);
	}
}

#endif // DEAMER_TEST_LANGUAGE_ANALYZER_MAIN_GRAMMAR_LANGUAGE_TERMINALNEIGHBORS_H
