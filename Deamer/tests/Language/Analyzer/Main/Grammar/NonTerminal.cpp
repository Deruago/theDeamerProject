#include "Deamer/Language/Analyzer/Main/Grammar/NonTerminal.h"
#include "../../../../Integration/Language/DefineSimpleLanguage.h"
#include "Deamer/Language/Analyzer/Analyzer.h"
#include "Deamer/Language/Reference/ReverseLookup.h"
#include "Language/EndingTerminalLanguage.h"
#include <Deamer/Language/Reference/PropertyDefinition.h>
#include <gtest/gtest.h>

using Type = deamer::language::type::definition::property::Type;
using namespace deamer::language::reference;
using namespace deamer::test::language::analyzer::grammar::language::nonterminal;

class TestNonTerminal : public testing::Test
{
public:
	using ReferenceType = PropertyDefinition<Type::Lexicon, Type::Grammar>;

protected:
	LanguageDefinition languageDefinition;
	EndingTerminalLanguage endingTerminalLanguageDefinition;

	deamer::language::type::definition::Language* language;
	deamer::language::type::definition::Language* endingTerminalLanguage;

	TestNonTerminal()
	{
		language = languageDefinition.GenerateLanguage();
		endingTerminalLanguage = endingTerminalLanguageDefinition.GenerateLanguage();
	}

	virtual ~TestNonTerminal()
	{
		delete language;
		delete endingTerminalLanguage;
	}
};

TEST_F(TestNonTerminal, IsDirectRecursive_RecursiveNonTerminal_ShouldReturnTrue)
{
	{
		const ReferenceType reference(language);

		const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");

		const deamer::language::analyzer::Analyzer<
			deamer::language::type::definition::object::main::NonTerminal>
			analyzer(&reference, nonTerminal);

		const bool isRecursive = analyzer->IsDirectRecursive();

		EXPECT_TRUE(isRecursive);
	}
	{
		const ReferenceType reference(language);

		const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");

		const deamer::language::analyzer::Analyzer<
			deamer::language::type::definition::object::main::NonTerminal>
			analyzer(&reference, nonTerminal);

		const bool isRecursive = analyzer->IsDirectRecursive();

		EXPECT_TRUE(isRecursive);
	}
}

TEST_F(TestNonTerminal, IsDirectRecursive_NonRecursiveNonTerminal_ShouldReturnFalse)
{
	{
		const ReferenceType reference(language);

		const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmt");

		const deamer::language::analyzer::Analyzer<
			deamer::language::type::definition::object::main::NonTerminal>
			analyzer(&reference, nonTerminal);

		const bool isRecursive = analyzer->IsDirectRecursive();

		EXPECT_FALSE(isRecursive);
	}
	{
		const ReferenceType reference(language);

		const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmt");

		const deamer::language::analyzer::Analyzer<
			deamer::language::type::definition::object::main::NonTerminal>
			analyzer(&reference, nonTerminal);

		const bool isRecursive = analyzer->IsDirectRecursive();

		EXPECT_FALSE(isRecursive);
	}
}

TEST_F(TestNonTerminal, IsDirectRecursive_NullptrNonTerminal_ShouldThrowException)
{
	const ReferenceType reference(language);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmt");
	const deamer::language::type::definition::object::main::ProductionRule* nullptr_production =
		nullptr;

	EXPECT_ANY_THROW(const deamer::language::analyzer::Analyzer<
						 deamer::language::type::definition::object::main::NonTerminal>
						 analyzer(&reference, nullptr_production););
}

// clang-format off
#define EXPECT_TERMINAL_IN_SET(expectedBase, bases) { const bool found = bases.find(const_cast<::deamer::language::type::definition::object::Base*>( static_cast<const ::deamer::language::type::definition::object::Base*>(expectedBase))) != bases.end(); EXPECT_TRUE(found); }

#define EXPECT_TERMINAL_NOT_IN_SET(expectedBase, bases) { const bool found = bases.find(const_cast<::deamer::language::type::definition::object::Base*>( static_cast<const ::deamer::language::type::definition::object::Base*>(expectedBase))) != bases.end(); EXPECT_FALSE(found); }

#define EXPECT_TOKEN_IN_SET(expectedBase, bases) { const bool found = bases.find(const_cast<::deamer::language::type::definition::object::Base*>( static_cast<const ::deamer::language::type::definition::object::Base*>(expectedBase))) != bases.end(); EXPECT_TRUE(found); }

#define EXPECT_TOKEN_NOT_IN_SET(expectedBase, bases) { const bool found = bases.find(const_cast<::deamer::language::type::definition::object::Base*>( static_cast<const ::deamer::language::type::definition::object::Base*>(expectedBase))) != bases.end(); EXPECT_FALSE(found); }
// clang-format on

TEST_F(TestNonTerminal, GetEndingTerminalsOfAliasNonTerminal_ShouldGiveCorrectEndingTerminals)
{
	const ReferenceType reference(language);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmt");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::NonTerminal>
		analyzer(&reference, nonTerminal);

	std::set<LDO<deamer::language::type::definition::object::main::Terminal>> endingTerminals;
	analyzer->GetEndingTerminals(endingTerminals);

	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME"),
						   endingTerminals);
	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
						   endingTerminals);

	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS"),
							   endingTerminals);
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("SPACES"),
							   endingTerminals);
}

TEST_F(TestNonTerminal, GetEndingTerminalsOfSTMTS_ShouldGiveCorrectEndingTerminals)
{
	const ReferenceType reference(language);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::NonTerminal>
		analyzer(&reference, nonTerminal);

	std::set<LDO<deamer::language::type::definition::object::main::Terminal>> endingTerminals;
	analyzer->GetEndingTerminals(endingTerminals);

	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME"),
						   endingTerminals);
	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
						   endingTerminals);

	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS"),
							   endingTerminals);
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("SPACES"),
							   endingTerminals);
}

TEST_F(TestNonTerminal, GetEndingTerminalsOfTopLevelNonTerminal_ShouldGiveCorrectEndingTerminals)
{
	const ReferenceType reference(language);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("prog");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::NonTerminal>
		analyzer(&reference, nonTerminal);

	std::set<LDO<deamer::language::type::definition::object::main::Terminal>> endingTerminals;
	analyzer->GetEndingTerminals(endingTerminals);

	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME"),
						   endingTerminals);
	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
						   endingTerminals);

	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS"),
							   endingTerminals);
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("SPACES"),
							   endingTerminals);
}

TEST_F(TestNonTerminal, GetEndingTerminalsInDoubleRecursiveNonTerminal_CorrectlyGiveTerminals)
{
	const ReferenceType reference(endingTerminalLanguage);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts2");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::NonTerminal>
		analyzer(&reference, nonTerminal);

	std::set<LDO<deamer::language::type::definition::object::main::Terminal>> endingTerminals;
	analyzer->GetEndingTerminals(endingTerminals);

	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("SPACES"),
						   endingTerminals);

	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
							   endingTerminals);
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS"),
							   endingTerminals);
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
							   endingTerminals);
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME"),
							   endingTerminals);
}

TEST_F(TestNonTerminal, GetEndingTerminalsOfDisjointNonTerminal_CorrectlyGiveTerminals)
{
	const ReferenceType reference(endingTerminalLanguage);

	const auto* nonTerminal =
		reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmtalternative");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::NonTerminal>
		analyzer(&reference, nonTerminal);

	std::set<LDO<deamer::language::type::definition::object::main::Terminal>> endingTerminals;
	analyzer->GetEndingTerminals(endingTerminals);

	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME"),
						   endingTerminals);

	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
							   endingTerminals);
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS"),
							   endingTerminals);
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
							   endingTerminals);
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("SPACES"),
							   endingTerminals);
}

TEST_F(TestNonTerminal,
	   GetEndingTerminalsOfOneOrMoreNonTerminalWithoutEmptyEnding_CorrectlyGiveTerminals)
{
	const ReferenceType reference(endingTerminalLanguage);

	const auto* nonTerminal =
		reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts_one_or_more");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::NonTerminal>
		analyzer(&reference, nonTerminal);

	std::set<LDO<deamer::language::type::definition::object::main::Terminal>> endingTerminals;
	analyzer->GetEndingTerminals(endingTerminals);

	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("SPACES"),
						   endingTerminals);

	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
							   endingTerminals);
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS"),
							   endingTerminals);
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
							   endingTerminals);
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME"),
							   endingTerminals);
}

TEST_F(TestNonTerminal, GetStartingTerminalsOfAliasNonTerminal_ShouldGiveCorrectStartingTerminals)
{
	const ReferenceType reference(language);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmt");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::NonTerminal>
		analyzer(&reference, nonTerminal);

	std::set<LDO<deamer::language::type::definition::object::main::Terminal>> startingTerminals;
	analyzer->GetStartingTerminals(startingTerminals);

	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME"),
						   startingTerminals);
	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
						   startingTerminals);

	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS"),
							   startingTerminals);
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("SPACES"),
							   startingTerminals);
}

TEST_F(TestNonTerminal, GetStartingTerminalsOfSTMTS_ShouldGiveCorrectStartingTerminals)
{
	const ReferenceType reference(language);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::NonTerminal>
		analyzer(&reference, nonTerminal);

	std::set<LDO<deamer::language::type::definition::object::main::Terminal>> startingTerminals;
	analyzer->GetStartingTerminals(startingTerminals);

	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME"),
						   startingTerminals);
	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
						   startingTerminals);

	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS"),
							   startingTerminals);
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("SPACES"),
							   startingTerminals);
}

TEST_F(TestNonTerminal,
	   GetStartingTerminalsOfTopLevelNonTerminal_ShouldGiveCorrectStartingTerminals)
{
	const ReferenceType reference(language);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("prog");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::NonTerminal>
		analyzer(&reference, nonTerminal);

	std::set<LDO<deamer::language::type::definition::object::main::Terminal>> endingTerminals;
	analyzer->GetEndingTerminals(endingTerminals);

	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME"),
						   endingTerminals);
	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
						   endingTerminals);

	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS"),
							   endingTerminals);
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("SPACES"),
							   endingTerminals);
}

TEST_F(TestNonTerminal, GetStartingTerminalsInDoubleRecursiveNonTerminal_CorrectlyGiveTerminals)
{
	const ReferenceType reference(endingTerminalLanguage);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts2");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::NonTerminal>
		analyzer(&reference, nonTerminal);

	std::set<LDO<deamer::language::type::definition::object::main::Terminal>> startingTerminals;
	analyzer->GetStartingTerminals(startingTerminals);

	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("SPACES"),
						   startingTerminals);

	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
							   startingTerminals);
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS"),
							   startingTerminals);
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME"),
							   startingTerminals);
}

TEST_F(TestNonTerminal, GetStartingTerminalsOfDisjointNonTerminal_CorrectlyGiveTerminals)
{
	const ReferenceType reference(endingTerminalLanguage);

	const auto* nonTerminal =
		reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmtalternative");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::NonTerminal>
		analyzer(&reference, nonTerminal);

	std::set<LDO<deamer::language::type::definition::object::main::Terminal>> startingTerminals;
	analyzer->GetStartingTerminals(startingTerminals);

	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME"),
						   startingTerminals);

	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
							   startingTerminals);
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS"),
							   startingTerminals);
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("SPACES"),
							   startingTerminals);
}

TEST_F(TestNonTerminal,
	   GetStartingTerminalsOfOneOrMoreNonTerminalWithoutEmptyEnding_CorrectlyGiveTerminals)
{
	const ReferenceType reference(endingTerminalLanguage);

	const auto* nonTerminal =
		reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts_one_or_more");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::NonTerminal>
		analyzer(&reference, nonTerminal);

	std::set<LDO<deamer::language::type::definition::object::main::Terminal>> startingTerminals;
	analyzer->GetStartingTerminals(startingTerminals);

	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("SPACES"),
						   startingTerminals);

	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
							   startingTerminals);
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS"),
							   startingTerminals);
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME"),
							   startingTerminals);
}

TEST_F(TestNonTerminal, CheckIfNonTerminalHasEmptyNode_NtDirectlyEndsWithEmpty_CorrectlyReturnTrue)
{
	const ReferenceType reference(endingTerminalLanguage);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::NonTerminal>
		analyzer(&reference, nonTerminal);

	std::set<LDO<deamer::language::type::definition::object::main::Terminal>> endingTerminals;
	EXPECT_TRUE(analyzer->DoesNonTerminalHaveEmptyAsItsNode());
}

TEST_F(TestNonTerminal, CheckIfNonTerminalHasEmptyNode_NtDoesntEndWithEmpty_CorrectlyReturnFalse)
{
	const ReferenceType reference(endingTerminalLanguage);

	const auto* nonTerminal =
		reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts_one_or_more");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::NonTerminal>
		analyzer(&reference, nonTerminal);

	std::set<LDO<deamer::language::type::definition::object::main::Terminal>> endingTerminals;
	EXPECT_FALSE(analyzer->DoesNonTerminalHaveEmptyAsItsNode());
}

TEST_F(
	TestNonTerminal,
	CheckIfNonTerminalHasEmptyNode_NtDoesntEndWithEmptyAndOnlyHasOneMatchingTerminal_CorrectlyReturnFalse)
{
	const ReferenceType reference(endingTerminalLanguage);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmt");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::NonTerminal>
		analyzer(&reference, nonTerminal);

	std::set<LDO<deamer::language::type::definition::object::main::Terminal>> endingTerminals;
	EXPECT_FALSE(analyzer->DoesNonTerminalHaveEmptyAsItsNode());
}

TEST_F(TestNonTerminal, CheckIfNonTerminalHasEmptyNode_NtIndirectlyEndWithEmpty_CorrectlyReturnTrue)
{
	const ReferenceType reference(endingTerminalLanguage);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("prog");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::NonTerminal>
		analyzer(&reference, nonTerminal);

	std::set<LDO<deamer::language::type::definition::object::main::Terminal>> endingTerminals;
	EXPECT_TRUE(analyzer->DoesNonTerminalHaveEmptyAsItsNode());
}

TEST_F(TestNonTerminal, GetLeftTokensFromNT_ShouldCorrectlyGiveAllTokensThatCanBeLeftOfThisNT)
{
	const ReferenceType reference(endingTerminalLanguage);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmt");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::NonTerminal>
		analyzer(&reference, nonTerminal);

	std::set<deamer::language::type::definition::object::Base*> neighboringTokens;
	analyzer->GetLeftNeighboringTokens(neighboringTokens);

	EXPECT_TOKEN_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts2"),
						neighboringTokens)
	EXPECT_TOKEN_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmt"),
						neighboringTokens)
	EXPECT_TOKEN_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmtalternative"),
						neighboringTokens)

	EXPECT_TOKEN_NOT_IN_SET(
		reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts_one_or_more"),
		neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("prog"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME"),
							neighboringTokens)
}

TEST_F(TestNonTerminal,
	   GetLeftTokensFromRecursiveNT_ShouldCorrectlyGiveAllTokensThatCanBeLeftOfThisNT)
{
	const ReferenceType reference(endingTerminalLanguage);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts2");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::NonTerminal>
		analyzer(&reference, nonTerminal);

	std::set<deamer::language::type::definition::object::Base*> neighboringTokens;
	analyzer->GetLeftNeighboringTokens(neighboringTokens);

	EXPECT_TOKEN_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts2"),
						neighboringTokens)
	EXPECT_TOKEN_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmt"),
						neighboringTokens)

	EXPECT_TOKEN_NOT_IN_SET(
		reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmtalternative"),
		neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(
		reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts_one_or_more"),
		neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("prog"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME"),
							neighboringTokens)
}

TEST_F(TestNonTerminal, GetLeftTokensFromTopNtWithoutLeftNTs_ShouldReturnNothing)
{
	const ReferenceType reference(endingTerminalLanguage);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("prog");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::NonTerminal>
		analyzer(&reference, nonTerminal);

	std::set<deamer::language::type::definition::object::Base*> neighboringTokens;
	analyzer->GetLeftNeighboringTokens(neighboringTokens);

	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts2"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmt"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(
		reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmtalternative"),
		neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(
		reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts_one_or_more"),
		neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("prog"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME"),
							neighboringTokens)
}

TEST_F(TestNonTerminal, GetRightTokensFromNT_ShouldCorrectlyGiveAllTokensThatCanBeRightOfThisNT)
{
	const ReferenceType reference(endingTerminalLanguage);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmt");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::NonTerminal>
		analyzer(&reference, nonTerminal);

	std::set<deamer::language::type::definition::object::Base*> neighboringTokens;
	analyzer->GetRightNeighboringTokens(neighboringTokens);

	EXPECT_TOKEN_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts2"),
						neighboringTokens)
	EXPECT_TOKEN_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts"),
						neighboringTokens)
	EXPECT_TOKEN_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmtalternative"),
						neighboringTokens)

	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmt"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(
		reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts_one_or_more"),
		neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("prog"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME"),
							neighboringTokens)
}

TEST_F(TestNonTerminal,
	   GetRightTokensFromRecursiveNT_ShouldCorrectlyGiveAllTokensThatCanBeRightOfThisNT)
{
	const ReferenceType reference(endingTerminalLanguage);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts2");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::NonTerminal>
		analyzer(&reference, nonTerminal);

	std::set<deamer::language::type::definition::object::Base*> neighboringTokens;
	analyzer->GetRightNeighboringTokens(neighboringTokens);

	EXPECT_TOKEN_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts2"),
						neighboringTokens)

	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmt"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(
		reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmtalternative"),
		neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(
		reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts_one_or_more"),
		neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("prog"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME"),
							neighboringTokens)
}

TEST_F(TestNonTerminal, GetRightTokensFromTopNtWithoutLeftNTs_ShouldReturnNothing)
{
	const ReferenceType reference(endingTerminalLanguage);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("prog");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::NonTerminal>
		analyzer(&reference, nonTerminal);

	std::set<deamer::language::type::definition::object::Base*> neighboringTokens;
	analyzer->GetRightNeighboringTokens(neighboringTokens);

	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts2"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmt"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(
		reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmtalternative"),
		neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(
		reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts_one_or_more"),
		neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Grammar>().GetNonTerminal("prog"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS"),
							neighboringTokens)
	EXPECT_TOKEN_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME"),
							neighboringTokens)
}
