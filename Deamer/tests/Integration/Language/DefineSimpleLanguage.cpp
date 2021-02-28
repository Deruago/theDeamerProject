#include "DefineSimpleLanguage.h"
#include <gtest/gtest.h>


using Type = deamer::language::type::definition::property::Type;
using namespace deamer::language::reference;
using namespace deamer::language::type::definition::object::main;

class IntegrationTestDefineSimpleLanguage : public testing::Test
{
protected:
	IntegrationTestDefineSimpleLanguage() = default;
	virtual ~IntegrationTestDefineSimpleLanguage() = default;

};

GenerateLexicon::GenerateLexicon(LanguageDefinition* lang) : Lexicon(lang)
{
	ESCAPE_CHARS.Set(Terminal("ESCAPE_CHARS", "[\n\b\t\r\f\a]+"));
	AddObject(ESCAPE_CHARS);
	SPACES.Set(Terminal("SPACES", "[ ]+"));
	AddObject(SPACES);

	VARNAME.Set(Terminal("VARNAME", "[a-zA-Z]+[a-zA-Z_0-9]*"));
	AddObject(VARNAME);
	STRING.Set(Terminal("STRING", R"(["][^"]*["])"));
	AddObject(STRING);
}

GenerateGrammar::GenerateGrammar(LanguageDefinition* lang) : Grammar(lang)
{
	prog.Set(NonTerminal("prog", { prog_stmts.Pointer() }));
	AddObject(prog);
	stmts.Set(NonTerminal("stmts", { stmts_stmt_stmts.Pointer(), stmts_empty.Pointer() }));
	AddObject(stmts);
	stmt.Set(NonTerminal("stmt", { stmt_VARNAME.Pointer(), stmt_STRING.Pointer() }));
	AddObject(stmt);

	prog_stmts.Set(ProductionRule({ stmts.Pointer() }));
	AddObject(prog_stmts);
	stmts_stmt_stmts.Set(ProductionRule({ stmt.Pointer(), stmts.Pointer() }));
	AddObject(stmts_stmt_stmts);
	stmts_empty.Set(ProductionRule());
	AddObject(stmts_empty);
	stmt_VARNAME.Set(ProductionRule({ Language->VARNAME.Pointer() }));
	AddObject(stmt_VARNAME);
	stmt_STRING.Set(ProductionRule({ Language->STRING.Pointer() }));
	AddObject(stmt_STRING);
}

LanguageDefinition::LanguageDefinition() : GenerateLexicon(this), GenerateGrammar(this)
{
}


TEST_F(IntegrationTestDefineSimpleLanguage, CreateLexicon)
{
	auto* tmp = new LanguageDefinition{};
	const auto lexicon = GenerateLexicon(tmp);

	EXPECT_EQ("ESCAPE_CHARS", lexicon.ESCAPE_CHARS->Name);
	EXPECT_EQ("SPACES", lexicon.SPACES->Name);
	EXPECT_EQ("VARNAME", lexicon.VARNAME->Name);
	EXPECT_EQ("STRING", lexicon.STRING->Name);

	EXPECT_EQ("[\n\b\t\r\f\a]+", lexicon.ESCAPE_CHARS->Regex);
	EXPECT_EQ("[ ]+", lexicon.SPACES->Regex);
	EXPECT_EQ("[a-zA-Z]+[a-zA-Z_0-9]*", lexicon.VARNAME->Regex);
	EXPECT_EQ(R"(["][^"]*["])", lexicon.STRING->Regex);

	delete lexicon.ESCAPE_CHARS.Pointer();
	delete lexicon.SPACES.Pointer();
	delete lexicon.VARNAME.Pointer();
	delete lexicon.STRING.Pointer();

	delete tmp->ESCAPE_CHARS.Pointer();
	delete tmp->SPACES.Pointer();
	delete tmp->VARNAME.Pointer();
	delete tmp->STRING.Pointer();
	delete tmp->prog.Pointer();
	delete tmp->stmts.Pointer();
	delete tmp->stmt.Pointer();

	delete tmp->prog_stmts.Pointer();
	delete tmp->stmts_stmt_stmts.Pointer();
	delete tmp->stmts_empty.Pointer();
	delete tmp->stmt_VARNAME.Pointer();
	delete tmp->stmt_STRING.Pointer();
	delete tmp;
}

TEST_F(IntegrationTestDefineSimpleLanguage, CreateGrammar)
{
	auto* tmp = new LanguageDefinition{};
	const auto grammar = GenerateGrammar(tmp);

	EXPECT_EQ("prog", grammar.prog->Name);
	EXPECT_EQ("stmts", grammar.stmts->Name);
	EXPECT_EQ("stmt", grammar.stmt->Name);
	EXPECT_EQ(std::vector<ProductionRule*>{ grammar.prog_stmts.Pointer() }, grammar.prog->ProductionRules);
	
	const auto stmts_production = std::vector<ProductionRule*>{ grammar.stmts_stmt_stmts.Pointer(), grammar.stmts_empty.Pointer() };
	EXPECT_EQ(stmts_production, grammar.stmts->ProductionRules);

	const auto stmt_production = std::vector<ProductionRule*>{ grammar.stmt_VARNAME.Pointer(), grammar.stmt_STRING.Pointer() };
	EXPECT_EQ(stmt_production, grammar.stmt->ProductionRules);

	delete grammar.prog.Pointer();
	delete grammar.stmts.Pointer();
	delete grammar.stmt.Pointer();
	
	delete grammar.prog_stmts.Pointer();
	delete grammar.stmts_stmt_stmts.Pointer();
	delete grammar.stmts_empty.Pointer();
	delete grammar.stmt_VARNAME.Pointer();
	delete grammar.stmt_STRING.Pointer();

	delete tmp->ESCAPE_CHARS.Pointer();
	delete tmp->SPACES.Pointer();
	delete tmp->VARNAME.Pointer();
	delete tmp->STRING.Pointer();
	delete tmp->prog.Pointer();
	delete tmp->stmts.Pointer();
	delete tmp->stmt.Pointer();

	delete tmp->prog_stmts.Pointer();
	delete tmp->stmts_stmt_stmts.Pointer();
	delete tmp->stmts_empty.Pointer();
	delete tmp->stmt_VARNAME.Pointer();
	delete tmp->stmt_STRING.Pointer();
	delete tmp;
}

TEST_F(IntegrationTestDefineSimpleLanguage, GenerateLanguageDefinition_CorrectlyGeneratesLexicon)
{
	auto language = LanguageDefinition{};
	auto* languageDefinition = language.GenerateLanguage();

	const auto reference = PropertyDefinition<Type::Lexicon>(*languageDefinition);
	auto terminals = reference.GetDefinition<Type::Lexicon>().Terminals;

	EXPECT_EQ(4, terminals.size());

	for (auto* terminal : terminals)
	{
		if (terminal->Name == "ESCAPE_CHARS")
		{
			EXPECT_EQ(language.ESCAPE_CHARS.Pointer(), terminal);
		}
		else if (terminal->Name == "SPACES")
		{
			EXPECT_EQ(language.SPACES.Pointer(), terminal);
		}
		else if (terminal->Name == "VARNAME")
		{
			EXPECT_EQ(language.VARNAME.Pointer(), terminal);
		}
		else if (terminal->Name == "STRING")
		{
			EXPECT_EQ(language.STRING.Pointer(), terminal);
		}
		else
		{
			EXPECT_FALSE(true); // Else, the test will fail
		}
	}

	delete languageDefinition;
}

TEST_F(IntegrationTestDefineSimpleLanguage, GenerateLanguageDefinition_CorrectlyGeneratesGrammar)
{
	auto language = LanguageDefinition{};
	auto* languageDefinition = language.GenerateLanguage();

	const auto reference = PropertyDefinition<Type::Grammar>(*languageDefinition);
	const auto& nonterminals = reference.GetDefinition<Type::Grammar>().NonTerminals;
	const auto& productionrules = reference.GetDefinition<Type::Grammar>().ProductionRules;

	EXPECT_EQ(3, nonterminals.size());
	EXPECT_EQ(5, productionrules.size());

	for (auto* nonterminal : nonterminals)
	{
		if (nonterminal->Name == "prog")
		{
			EXPECT_EQ(language.prog.Pointer(), nonterminal);
		}
		else if (nonterminal->Name == "stmts")
		{
			EXPECT_EQ(language.stmts.Pointer(), nonterminal);
		}
		else if (nonterminal->Name == "stmt")
		{
			EXPECT_EQ(language.stmt.Pointer(), nonterminal);
		}
		else
		{
			EXPECT_FALSE(true); // Else, the test will fail
		}
	}

	delete languageDefinition;
}