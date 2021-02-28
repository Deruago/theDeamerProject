#ifndef DEAMER_TESTS_INTEGRATION_LANGUAGE_DEFINESIMPLELANGUAGE_H
#define DEAMER_TESTS_INTEGRATION_LANGUAGE_DEFINESIMPLELANGUAGE_H

#include "Deamer/Language/Generator/Definition/Language.h"
#include <Deamer/Language/Reference/PropertyDefinition.h>
#include "Deamer/Language/Generator/Definition/Property/Grammar.h"
#include <Deamer/Language/Generator/Definition/Property/Lexicon.h>
#include <Deamer/Type/Memory/SafeReserve.h>

class LanguageDefinition;

class GenerateLexicon : public deamer::language::generator::definition::property::Lexicon<LanguageDefinition>
{
public:
	const deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal> ESCAPE_CHARS;
	const deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal> SPACES;

	const deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal> VARNAME;
	const deamer::type::SafeReserve<deamer::language::type::definition::object::main::Terminal> STRING;

	GenerateLexicon(LanguageDefinition* lang);
};

class GenerateGrammar : public deamer::language::generator::definition::property::Grammar<LanguageDefinition>
{
public:
	const deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal> prog;
	const deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal> stmts;
	const deamer::type::SafeReserve<deamer::language::type::definition::object::main::NonTerminal> stmt;

	const deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule> prog_stmts;
	
	const deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule> stmts_stmt_stmts;
	const deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule> stmts_empty;

	const deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule> stmt_VARNAME;
	const deamer::type::SafeReserve<deamer::language::type::definition::object::main::ProductionRule> stmt_STRING;

	GenerateGrammar(LanguageDefinition* lang);
};

class LanguageDefinition : public deamer::language::generator::definition::Language<LanguageDefinition, GenerateLexicon, GenerateGrammar>, public GenerateLexicon, public GenerateGrammar
{
public:
	int a = 0;
	LanguageDefinition();
	~LanguageDefinition() = default;
};

#endif //DEAMER_TESTS_INTEGRATION_LANGUAGE_DEFINESIMPLELANGUAGE_H