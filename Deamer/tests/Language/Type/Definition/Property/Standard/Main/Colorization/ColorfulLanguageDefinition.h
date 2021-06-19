#ifndef DEAMER_TEST_LANGUAGE_TYPE_DEFINITION_PROPERTY_STANDARD_MAIN_COLORIZATION_COLORFULLLANGUAGEDEFINITION_H
#define DEAMER_TEST_LANGUAGE_TYPE_DEFINITION_PROPERTY_STANDARD_MAIN_COLORIZATION_COLORFULLLANGUAGEDEFINITION_H

#include "Deamer/Language/Generator/Definition/Language.h"
#include "Deamer/Language/Generator/Definition/Property/Standard/Main/Colorization.h"
#include "Deamer/Language/Generator/Definition/Property/Standard/Main/Threat.h"
#include "Deamer/Language/Generator/Definition/Property/User/Main/Grammar.h"
#include "Deamer/Language/Generator/Definition/Property/User/Main/Lexicon.h"
#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/Terminal.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Analyzer/Combined/Deamer/DeamerCore.h"

namespace deamer::test::language::threat::standard::generator
{
	class ColorfulLanguageDefinition;

	class GenerateLexicon
		: public ::deamer::language::generator::definition::property::user::Lexicon<
			  ColorfulLanguageDefinition>
	{
	public:
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			INTEGER_TYPE;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			STRING_TYPE;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			FUNCTION;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			VARNAME;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			NUMBER;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			STRING;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			LEFT_PARANTHESIS;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			RIGHT_PARANTHESIS;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			LEFT_BRACKET;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			RIGHT_BRACKET;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			LEFT_SQUARE_BRACKET;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			RIGHT_SQUARE_BRACKET;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			ADD;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			MINUS;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			EQ;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			EQ_EQ;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			SEMICOLON;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			COMMA;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			ESCAPE_CHARS;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::Terminal>
			SPACES;

		GenerateLexicon(ColorfulLanguageDefinition* lang);
	};

	class GenerateGrammar
		: public ::deamer::language::generator::definition::property::user::Grammar<
			  ColorfulLanguageDefinition>
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
			variable_declaration;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::NonTerminal>
			function_declaration;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::NonTerminal>
			value;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::NonTerminal>
			type;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::NonTerminal>
			function_block;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::NonTerminal>
			parameters;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::NonTerminal>
			parameter;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::NonTerminal>
			parameter_one_or_more;

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
			stmt_variable_declaration;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			stmt_function_declaration;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			variable_declaration_type_VARNAME_EQ_value_SEMICOLON;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			function_declaration_VARNAME_LEFT_PARANTHESIS_parameters_RIGHT_PARANTHESIS_type_function_block;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			value_NUMBER;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			value_VARNAME;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			value_STRING;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			type_INTEGER_TYPE;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			type_STRING_TYPE;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			parameters_parameter_COMMA_parameter_one_or_more;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			parameters_EMPTY;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			parameter_one_or_more_parameter_COMMA_parameter_one_or_more;
		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			parameter_one_or_more_parameter;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			parameter_type_VARNAME;

		const ::deamer::type::SafeReserve<
			::deamer::language::type::definition::object::main::ProductionRule>
			function_block_LEFT_BRACKET_stmts_RIGHT_BRACKET;

		GenerateGrammar(ColorfulLanguageDefinition* lang);
	};

	class GenerateThreat
		: public ::deamer::language::generator::definition::property::standard::Threat<
			  ColorfulLanguageDefinition, ::deamer::language::type::definition::object::main::
											  threat::analyzer::deamer::DeamerCore>
	{
	public:
		GenerateThreat(ColorfulLanguageDefinition* language)
			: ::deamer::language::generator::definition::property::standard::Threat<
				  ColorfulLanguageDefinition, ::deamer::language::type::definition::object::main::
												  threat::analyzer::deamer::DeamerCore>(language)
		{
		}
		~GenerateThreat() override = default;
	};

	class GenerateColors
		: public ::deamer::language::generator::definition::property::standard::Colorization<
			  ColorfulLanguageDefinition>
	{
	public:
		GenerateColors(ColorfulLanguageDefinition* language, bool colorSymbolsEqual = false)
			: ::deamer::language::generator::definition::property::standard::Colorization<
				  ColorfulLanguageDefinition>(language, colorSymbolsEqual)
		{
		}
		~GenerateColors() override = default;
	};

	class ColorfulLanguageDefinition : public ::deamer::language::generator::definition::Language<
										   ColorfulLanguageDefinition, GenerateLexicon,
										   GenerateGrammar, GenerateThreat, GenerateColors>,
									   public GenerateLexicon,
									   public GenerateGrammar,
									   public GenerateThreat,
									   public GenerateColors
	{
	public:
		ColorfulLanguageDefinition(bool colorSymbolsEqual = false)
			: GenerateLexicon(this),
			  GenerateGrammar(this),
			  GenerateThreat(this),
			  GenerateColors(this, colorSymbolsEqual)
		{
		}
		~ColorfulLanguageDefinition() = default;
	};

	inline GenerateLexicon::GenerateLexicon(ColorfulLanguageDefinition* lang) : Lexicon(lang)
	{
		INTEGER_TYPE.Set(::deamer::language::type::definition::object::main::Terminal(
			"INTEGER_TYPE", "Integer"));
		STRING_TYPE.Set(
			::deamer::language::type::definition::object::main::Terminal("STRING_TYPE", "String"));

		FUNCTION.Set(
			::deamer::language::type::definition::object::main::Terminal("FUNCTION", "Function"));

		STRING.Set(::deamer::language::type::definition::object::main::Terminal("STRING",
																				R"(["][^"]*["])"));
		VARNAME.Set(::deamer::language::type::definition::object::main::Terminal(
			"VARNAME", "[a-zA-Z]+[a-zA-Z_0-9]*"));
		NUMBER.Set(
			::deamer::language::type::definition::object::main::Terminal("NUMBER", "[0-9]+"));

		LEFT_PARANTHESIS.Set(::deamer::language::type::definition::object::main::Terminal(
			"LEFT_PARANTHESIS", R"([(])"));
		RIGHT_PARANTHESIS.Set(::deamer::language::type::definition::object::main::Terminal(
			"RIGHT_PARANTHESIS", R"([)])"));
		LEFT_BRACKET.Set(
			::deamer::language::type::definition::object::main::Terminal("LEFT_BRACKET", R"([{])"));
		RIGHT_BRACKET.Set(::deamer::language::type::definition::object::main::Terminal(
			"RIGHT_BRACKET", R"([}])"));
		LEFT_SQUARE_BRACKET.Set(::deamer::language::type::definition::object::main::Terminal(
			"LEFT_SQUARE_BRACKET", R"([\[])"));
		RIGHT_SQUARE_BRACKET.Set(::deamer::language::type::definition::object::main::Terminal(
			"RIGHT_SQUARE_BRACKET", R"([\]])"));
		ADD.Set(::deamer::language::type::definition::object::main::Terminal("ADD", R"([+])"));
		MINUS.Set(::deamer::language::type::definition::object::main::Terminal("MINUS", R"([-])"));
		EQ.Set(::deamer::language::type::definition::object::main::Terminal("EQ", R"([=])"));
		EQ_EQ.Set(
			::deamer::language::type::definition::object::main::Terminal("EQ_EQ", R"([=][=])"));
		SEMICOLON.Set(::deamer::language::type::definition::object::main::Terminal(
			"SEMICOLON", R"([;])"));
		COMMA.Set(::deamer::language::type::definition::object::main::Terminal("COMMA", R"([,])"));

		ESCAPE_CHARS.Set(::deamer::language::type::definition::object::main::Terminal(
			"ESCAPE_CHARS", "[\n\r\t\f]*"));
		SPACES.Set(::deamer::language::type::definition::object::main::Terminal(
			"SPACES", "[ ]+",
			::deamer::language::type::definition::object::main::SpecialType::Delete));

		AddObject(INTEGER_TYPE);
		AddObject(STRING_TYPE);
		AddObject(FUNCTION);
		AddObject(STRING);
		AddObject(VARNAME);
		AddObject(NUMBER);
		AddObject(LEFT_PARANTHESIS);
		AddObject(RIGHT_PARANTHESIS);
		AddObject(LEFT_BRACKET);
		AddObject(RIGHT_BRACKET);
		AddObject(LEFT_SQUARE_BRACKET);
		AddObject(RIGHT_SQUARE_BRACKET);
		AddObject(ADD);
		AddObject(MINUS);
		AddObject(EQ);
		AddObject(EQ_EQ);
		AddObject(SEMICOLON);
		AddObject(COMMA);
		AddObject(ESCAPE_CHARS);
		AddObject(SPACES);
	}

	inline GenerateGrammar::GenerateGrammar(ColorfulLanguageDefinition* lang) : Grammar(lang)
	{
		prog.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"prog", {prog_stmts.Pointer()}));
		stmts.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"stmts", {stmts_stmt_stmts.Pointer(), stmts_empty.Pointer()}));
		stmt.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"stmt", {stmt_variable_declaration.Pointer(), stmt_function_declaration.Pointer()}));

		variable_declaration.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"variable_declaration",
			{variable_declaration_type_VARNAME_EQ_value_SEMICOLON.Pointer()}));
		function_declaration.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"function_declaration",
			{function_declaration_VARNAME_LEFT_PARANTHESIS_parameters_RIGHT_PARANTHESIS_type_function_block
				 .Pointer()}));
		value.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"value", {value_VARNAME.Pointer(), value_STRING.Pointer(), value_NUMBER.Pointer()}));
		type.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"type", {type_STRING_TYPE.Pointer(), type_INTEGER_TYPE.Pointer()}));
		function_block.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"function_block", {function_block_LEFT_BRACKET_stmts_RIGHT_BRACKET.Pointer()}));
		parameters.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"parameters", {parameters_parameter_COMMA_parameter_one_or_more.Pointer(),
						   parameters_EMPTY.Pointer()}));
		parameter.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"parameter", {parameter_type_VARNAME.Pointer()}));
		parameter_one_or_more.Set(::deamer::language::type::definition::object::main::NonTerminal(
			"parameter_one_or_more",
			{parameter_one_or_more_parameter.Pointer(),
			 parameter_one_or_more_parameter_COMMA_parameter_one_or_more.Pointer()}));

		prog_stmts.Set(
			::deamer::language::type::definition::object::main::ProductionRule({stmts.Pointer()}));
		stmts_stmt_stmts.Set(::deamer::language::type::definition::object::main::ProductionRule(
			{stmt.Pointer(), stmts.Pointer()}));
		stmts_empty.Set(::deamer::language::type::definition::object::main::ProductionRule());

		stmt_variable_declaration.Set(
			::deamer::language::type::definition::object::main::ProductionRule(
				{variable_declaration.Pointer()}));
		stmt_function_declaration.Set(
			::deamer::language::type::definition::object::main::ProductionRule(
				{function_declaration.Pointer()}));
		variable_declaration_type_VARNAME_EQ_value_SEMICOLON.Set(
			::deamer::language::type::definition::object::main::ProductionRule(
				{type.Pointer(), lang->VARNAME.Pointer(), lang->EQ.Pointer(), value.Pointer(),
				 lang->SEMICOLON.Pointer()}));
		function_declaration_VARNAME_LEFT_PARANTHESIS_parameters_RIGHT_PARANTHESIS_type_function_block
			.Set(::deamer::language::type::definition::object::main::ProductionRule(
				{lang->VARNAME.Pointer(), lang->LEFT_PARANTHESIS.Pointer(), parameters.Pointer(),
				 lang->RIGHT_PARANTHESIS.Pointer(), type.Pointer(), function_block.Pointer()}));
		value_NUMBER.Set(::deamer::language::type::definition::object::main::ProductionRule(
			{lang->NUMBER.Pointer()}));
		value_VARNAME.Set(::deamer::language::type::definition::object::main::ProductionRule(
			{lang->VARNAME.Pointer()}));
		value_STRING.Set(::deamer::language::type::definition::object::main::ProductionRule(
			{lang->STRING.Pointer()}));
		type_INTEGER_TYPE.Set(::deamer::language::type::definition::object::main::ProductionRule(
			{lang->INTEGER_TYPE.Pointer()}));
		type_STRING_TYPE.Set(::deamer::language::type::definition::object::main::ProductionRule(
			{lang->STRING_TYPE.Pointer()}));
		parameters_parameter_COMMA_parameter_one_or_more.Set(
			::deamer::language::type::definition::object::main::ProductionRule(
				{parameter.Pointer(), lang->COMMA.Pointer(), parameter_one_or_more.Pointer()}));
		parameters_EMPTY.Set(::deamer::language::type::definition::object::main::ProductionRule());
		parameter_one_or_more_parameter_COMMA_parameter_one_or_more.Set(
			::deamer::language::type::definition::object::main::ProductionRule(
				{parameter.Pointer(), lang->COMMA.Pointer(), parameter_one_or_more.Pointer()}));
		parameter_one_or_more_parameter.Set(
			::deamer::language::type::definition::object::main::ProductionRule(
				{parameter.Pointer()}));
		parameter_type_VARNAME.Set(
			::deamer::language::type::definition::object::main::ProductionRule(
				{type.Pointer(), lang->VARNAME.Pointer()}));
		function_block_LEFT_BRACKET_stmts_RIGHT_BRACKET.Set(
			::deamer::language::type::definition::object::main::ProductionRule(
				{function_block.Pointer(), lang->LEFT_BRACKET.Pointer(), stmts.Pointer(),
				 lang->RIGHT_BRACKET.Pointer()}));

		AddObject(prog);
		AddObject(stmts);
		AddObject(stmt);
		AddObject(variable_declaration);
		AddObject(function_declaration);

		AddObject(value);
		AddObject(type);
		AddObject(function_block);
		AddObject(parameters);
		AddObject(parameter);
		AddObject(parameter_one_or_more);

		AddObject(prog_stmts);

		AddObject(stmts_stmt_stmts);
		AddObject(stmts_empty);

		AddObject(stmt_variable_declaration);
		AddObject(stmt_function_declaration);

		AddObject(variable_declaration_type_VARNAME_EQ_value_SEMICOLON);

		AddObject(
			function_declaration_VARNAME_LEFT_PARANTHESIS_parameters_RIGHT_PARANTHESIS_type_function_block);

		AddObject(value_NUMBER);
		AddObject(value_VARNAME);
		AddObject(value_STRING);

		AddObject(type_INTEGER_TYPE);
		AddObject(type_STRING_TYPE);

		AddObject(parameters_parameter_COMMA_parameter_one_or_more);
		AddObject(parameters_EMPTY);
		AddObject(parameter_one_or_more_parameter_COMMA_parameter_one_or_more);
		AddObject(parameter_one_or_more_parameter);

		AddObject(parameter_type_VARNAME);

		AddObject(function_block_LEFT_BRACKET_stmts_RIGHT_BRACKET);
	}
}

#endif // DEAMER_TEST_LANGUAGE_TYPE_DEFINITION_PROPERTY_STANDARD_MAIN_COLORIZATION_COLORFULLLANGUAGEDEFINITION_H
