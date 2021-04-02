#include "Deamer/Language/Analyzer/Main/Grammar/ProductionRule.h"
#include "../../../../Integration/Language/DefineSimpleLanguage.h"
#include "Deamer/Language/Analyzer/Analyzer.h"
#include "Deamer/Language/Reference/ReverseLookup.h"
#include <Deamer/Language/Reference/PropertyDefinition.h>
#include <gtest/gtest.h>

using Type = deamer::language::type::definition::property::Type;
using namespace deamer::language::reference;

class TestProductionRule : public testing::Test
{
public:
	using ReferenceType = PropertyDefinition<Type::Lexicon, Type::Grammar>;

protected:
	LanguageDefinition languageDefinition;
	deamer::language::type::definition::Language* language;

	TestProductionRule()
	{
		language = languageDefinition.GenerateLanguage();
	}

	virtual ~TestProductionRule()
	{
		delete language;
	}
};

TEST_F(TestProductionRule, IsRecursive_RecursiveProductionRule_ShouldReturnTrue)
{
	{
		const ReferenceType reference(language);

		const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");
		const auto* productionRule = nonTerminal->ProductionRules[0];

		const deamer::language::analyzer::Analyzer<
			deamer::language::type::definition::object::main::ProductionRule>
			analyzer(&reference, productionRule);

		const bool isRecursive = analyzer->IsDirectRecursive();

		EXPECT_TRUE(isRecursive);
	}
	{
		const ReferenceType reference(language);

		const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");
		const auto* productionRule = nonTerminal->ProductionRules[0];

		const deamer::language::analyzer::Analyzer<
			deamer::language::type::definition::object::main::ProductionRule>
			analyzer(&reference, productionRule);

		const bool isRecursive = analyzer->IsDirectRecursive();

		EXPECT_TRUE(isRecursive);
	}
}

TEST_F(TestProductionRule, IsRecursive_NonRecursiveProductionRule_ShouldReturnFalse)
{
	const ReferenceType reference(language);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");
	const auto* productionRule = nonTerminal->ProductionRules[1];

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::ProductionRule>
		analyzer(&reference, productionRule);

	const bool isRecursive = analyzer->IsDirectRecursive();

	EXPECT_FALSE(isRecursive);
}

TEST_F(TestProductionRule, IsRecursive_RecursiveProductionRule_GiveNonTerminal_ShouldReturnTrue)
{
	const ReferenceType reference(language);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");
	const auto* productionRule = nonTerminal->ProductionRules[0];

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::ProductionRule>
		analyzer(&reference, productionRule);

	const bool isRecursive = analyzer->IsDirectRecursive(nonTerminal);

	EXPECT_TRUE(isRecursive);
}

TEST_F(TestProductionRule, IsRecursive_NonRecursiveProductionRule_GiveNonTerminal_ShouldReturnFalse)
{
	const ReferenceType reference(language);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");
	const auto* productionRule = nonTerminal->ProductionRules[1];

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::ProductionRule>
		analyzer(&reference, productionRule);

	const bool isRecursive = analyzer->IsDirectRecursive(nonTerminal);

	EXPECT_FALSE(isRecursive);
}

TEST_F(TestProductionRule, IsRecursive_RecursiveProductionRule_NullptrNonTerminal_ShouldReturnFalse)
{
	const ReferenceType reference(language);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");
	const auto* productionRule = nonTerminal->ProductionRules[0];

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::ProductionRule>
		analyzer(&reference, productionRule);

	const bool isRecursive = analyzer->IsDirectRecursive(
		static_cast<const deamer::language::type::definition::object::main::NonTerminal*>(nullptr));

	EXPECT_FALSE(isRecursive);
}

TEST_F(TestProductionRule,
	   IsRecursive_NonRecursiveProductionRule_NullptrNonTerminal_ShouldReturnFalse)
{
	const ReferenceType reference(language);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");
	const auto* productionRule = nonTerminal->ProductionRules[1];

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::ProductionRule>
		analyzer(&reference, productionRule);

	const bool isRecursive = analyzer->IsDirectRecursive(
		static_cast<const deamer::language::type::definition::object::main::NonTerminal*>(nullptr));

	EXPECT_FALSE(isRecursive);
}

TEST_F(TestProductionRule, IsRecursive_NullptrProductionRule_ShouldThrow)
{
	const ReferenceType reference(language);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");
	EXPECT_ANY_THROW(const deamer::language::analyzer::Analyzer<
					 deamer::language::type::definition::object::main::ProductionRule>
						 analyzer(&reference, nullptr));
}
