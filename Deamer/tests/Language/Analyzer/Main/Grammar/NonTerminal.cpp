#include "Deamer/Language/Analyzer/Main/Grammar/NonTerminal.h"
#include "../../../../Integration/Language/DefineSimpleLanguage.h"
#include "Deamer/Language/Analyzer/Analyzer.h"
#include "Deamer/Language/Reference/ReverseLookup.h"
#include <Deamer/Language/Reference/PropertyDefinition.h>
#include <gtest/gtest.h>

using Type = deamer::language::type::definition::property::Type;
using namespace deamer::language::reference;

class TestNonTerminal : public testing::Test
{
public:
	using ReferenceType = PropertyDefinition<Type::Lexicon, Type::Grammar>;

protected:
	LanguageDefinition languageDefinition;
	deamer::language::type::definition::Language* language;

	TestNonTerminal()
	{
		language = languageDefinition.GenerateLanguage();
	}

	virtual ~TestNonTerminal()
	{
		delete language;
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

	EXPECT_ANY_THROW(const deamer::language::analyzer::Analyzer<
						 deamer::language::type::definition::object::main::NonTerminal>
						 analyzer(&reference, nullptr););
}
