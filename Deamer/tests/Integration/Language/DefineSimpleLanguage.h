#ifndef DEAMER_TESTS_INTEGRATION_LANGUAGE_DEFINESIMPLELANGUAGE_H
#define DEAMER_TESTS_INTEGRATION_LANGUAGE_DEFINESIMPLELANGUAGE_H

#include "Deamer/Language/Generator/Definition/Language.h"
#include "Deamer/Language/Generator/Definition/Property/Standard/Main/Associativity.h"
#include "Deamer/Language/Generator/Definition/Property/Standard/Main/Precedence.h"
#include "Deamer/Language/Generator/Definition/Property/User/Main/Grammar.h"
#include <Deamer/Language/Generator/Definition/Property/User/Main/Lexicon.h>
#include <Deamer/Language/Reference/PropertyDefinition.h>
#include <Deamer/Type/Memory/SafeReserve.h>

class LanguageDefinition;

class GenerateLexicon
	: public deamer::language::generator::definition::property::user::Lexicon<LanguageDefinition>
{
public:
	const deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
		ESCAPE_CHARS;
	const deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
		SPACES;

	const deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
		VARNAME;
	const deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal>
		STRING;

	GenerateLexicon(LanguageDefinition* lang);
};

class GenerateGrammar
	: public deamer::language::generator::definition::property::user::Grammar<LanguageDefinition>
{
public:
	const deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
		prog;
	const deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
		stmts;
	const deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal>
		stmt;

	const deamer::type::SafeReserve<
		deamer::language::type::definition::object::main::ProductionRule>
		prog_stmts;

	const deamer::type::SafeReserve<
		deamer::language::type::definition::object::main::ProductionRule>
		stmts_stmt_stmts;
	const deamer::type::SafeReserve<
		deamer::language::type::definition::object::main::ProductionRule>
		stmts_empty;

	const deamer::type::SafeReserve<
		deamer::language::type::definition::object::main::ProductionRule>
		stmt_VARNAME;
	const deamer::type::SafeReserve<
		deamer::language::type::definition::object::main::ProductionRule>
		stmt_STRING;

	GenerateGrammar(LanguageDefinition* lang);
};

class GeneratePrecedence
	: public deamer::language::generator::definition::property::standard::Precedence<
		  LanguageDefinition>
{
public:
	GeneratePrecedence(LanguageDefinition* lang);
};

class GenerateAssociativity
	: public deamer::language::generator::definition::property::standard::Associativity<
		  LanguageDefinition>
{
public:
	GenerateAssociativity(LanguageDefinition* lang);
};

class LanguageDefinition
	: public deamer::language::generator::definition::Language<LanguageDefinition, GenerateLexicon,
															   GenerateGrammar, GeneratePrecedence,
															   GenerateAssociativity>,
	  public GenerateLexicon,
	  public GenerateGrammar,
	  public GeneratePrecedence,
	  public GenerateAssociativity
{
public:
	int a = 0;
	LanguageDefinition();
	~LanguageDefinition() = default;
};

#endif // DEAMER_TESTS_INTEGRATION_LANGUAGE_DEFINESIMPLELANGUAGE_H
