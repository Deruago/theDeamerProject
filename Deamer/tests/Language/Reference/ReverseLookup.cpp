#include "Deamer/Language/Reference/ReverseLookup.h"
#include "../../Integration/Language/DefineSimpleLanguage.h"
#include <Deamer/Language/Reference/PropertyDefinition.h>
#include <gtest/gtest.h>

using Type = deamer::language::type::definition::property::Type;
using namespace deamer::language::reference;

class TestReverseLookup : public testing::Test
{
public:
	using ReferenceType = PropertyDefinition<Type::Lexicon, Type::Grammar>;

protected:
	LanguageDefinition languageDefinition;
	deamer::language::type::definition::Language* language;

	TestReverseLookup()
	{
		language = languageDefinition.GenerateLanguage();
	}

	virtual ~TestReverseLookup()
	{
		delete language;
	}
};

TEST_F(TestReverseLookup, ReverseLookupOfNonTerminal_UsesConstantType_ReturnsCorrectNonTerminal)
{
	ReferenceType reference(language);
	const ReverseLookup<deamer::language::type::definition::object::main::NonTerminal>
		reverseLookup(&reference);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");
	const auto* productionRule = nonTerminal->ProductionRules[0];
	const auto result = reverseLookup.Get(productionRule);

	EXPECT_TRUE(result.Success());
	EXPECT_EQ(CacheLocation::Secondary, result.GetCacheLocation());
	EXPECT_EQ(1, result.Size());
	EXPECT_EQ(1, result.GetObjects().size());
	ASSERT_FALSE(result.IsEmpty());
	EXPECT_EQ(nonTerminal, result.GetObject());
}

TEST_F(TestReverseLookup, ReverseLookupOfNonTerminal_UsesVolatileType_ReturnsCorrectNonTerminal)
{
	ReferenceType reference(language);
	const ReverseLookup<deamer::language::type::definition::object::main::NonTerminal>
		reverseLookup(&reference);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");
	volatile auto* productionRule = nonTerminal->ProductionRules[0];
	const auto result = reverseLookup.Get(productionRule);

	EXPECT_TRUE(result.Success());
	EXPECT_EQ(CacheLocation::Secondary, result.GetCacheLocation());
	EXPECT_EQ(1, result.Size());
	EXPECT_EQ(1, result.GetObjects().size());
	ASSERT_FALSE(result.IsEmpty());
	EXPECT_EQ(nonTerminal, result.GetObject());
}

TEST_F(TestReverseLookup, ReverseLookupOfNonTerminal_UsesCVType_ReturnsCorrectNonTerminal)
{
	ReferenceType reference(language);
	const ReverseLookup<deamer::language::type::definition::object::main::NonTerminal>
		reverseLookup(&reference);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");
	const volatile auto* productionRule = nonTerminal->ProductionRules[0];
	const auto result = reverseLookup.Get(productionRule);

	EXPECT_TRUE(result.Success());
	EXPECT_EQ(CacheLocation::Secondary, result.GetCacheLocation());
	EXPECT_EQ(1, result.Size());
	EXPECT_EQ(1, result.GetObjects().size());
	ASSERT_FALSE(result.IsEmpty());
	EXPECT_EQ(nonTerminal, result.GetObject());
}

TEST_F(TestReverseLookup,
	   ReverseLookupOfNonTerminal_UsesCvUnqualifiedType_ReturnsCorrectNonTerminal)
{
	ReferenceType reference(language);
	const ReverseLookup<deamer::language::type::definition::object::main::NonTerminal>
		reverseLookup(&reference);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");
	auto* productionRule = nonTerminal->ProductionRules[0];
	const auto result = reverseLookup.Get(productionRule);

	EXPECT_TRUE(result.Success());
	EXPECT_EQ(CacheLocation::Secondary, result.GetCacheLocation());
	EXPECT_EQ(1, result.Size());
	EXPECT_EQ(1, result.GetObjects().size());
	ASSERT_FALSE(result.IsEmpty());
	EXPECT_EQ(nonTerminal, result.GetObject());
}

TEST_F(
	TestReverseLookup,
	ReverseLookupOfNonTerminal_UsesCvUnqualifiedType_Thrice_ReturnsCorrectNonTerminal_SecondFindShouldComeFromPrimaryCache)
{
	ReferenceType reference(language);

	const auto* nonTerminal = reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");
	auto* productionRule = nonTerminal->ProductionRules[0];

	{
		const ReverseLookup<deamer::language::type::definition::object::main::NonTerminal>
			reverseLookup(&reference);

		const auto result = reverseLookup.Get(productionRule);

		EXPECT_TRUE(result.Success());
		EXPECT_EQ(CacheLocation::Secondary, result.GetCacheLocation());
		EXPECT_EQ(1, result.Size());
		EXPECT_EQ(1, result.GetObjects().size());
		ASSERT_FALSE(result.IsEmpty());
		EXPECT_EQ(nonTerminal, result.GetObject());
	}
	{
		const ReverseLookup<deamer::language::type::definition::object::main::NonTerminal>
			reverseLookup(&reference);

		const auto result = reverseLookup.Get(productionRule);

		EXPECT_TRUE(result.Success());
		EXPECT_EQ(CacheLocation::Primary, result.GetCacheLocation());
		EXPECT_EQ(1, result.Size());
		EXPECT_EQ(1, result.GetObjects().size());
		ASSERT_FALSE(result.IsEmpty());
		EXPECT_EQ(nonTerminal, result.GetObject());
	}
	{
		const ReverseLookup<deamer::language::type::definition::object::main::NonTerminal>
			reverseLookup(&reference);

		const auto result = reverseLookup.Get(productionRule);

		EXPECT_TRUE(result.Success());
		EXPECT_EQ(CacheLocation::Primary, result.GetCacheLocation());
		EXPECT_EQ(1, result.Size());
		EXPECT_EQ(1, result.GetObjects().size());
		ASSERT_FALSE(result.IsEmpty());
		EXPECT_EQ(nonTerminal, result.GetObject());
	}
}

TEST_F(
	TestReverseLookup,
	ReverseLookupOfNonTerminal_UsesCvUnqualifiedType_Thrice_UsingCopiedReference_ReturnsCorrectNonTerminal_SecondFindShouldComeFromPrimaryCache)
{
	ReferenceType reference_initial(language);
	ReferenceType reference_copy(reference_initial);

	const auto* nonTerminal = reference_copy.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");
	auto* productionRule = nonTerminal->ProductionRules[0];
	{
		const ReverseLookup<deamer::language::type::definition::object::main::NonTerminal>
			reverseLookup(&reference_copy);

		const auto result = reverseLookup.Get(productionRule);

		EXPECT_TRUE(result.Success());
		EXPECT_EQ(CacheLocation::Secondary, result.GetCacheLocation());
		EXPECT_EQ(1, result.Size());
		EXPECT_EQ(1, result.GetObjects().size());
		ASSERT_FALSE(result.IsEmpty());
		EXPECT_EQ(nonTerminal, result.GetObject());
	}
	{
		const ReverseLookup<deamer::language::type::definition::object::main::NonTerminal>
			reverseLookup(&reference_copy);

		const auto result = reverseLookup.Get(productionRule);

		EXPECT_TRUE(result.Success());
		EXPECT_EQ(CacheLocation::Primary, result.GetCacheLocation());
		EXPECT_EQ(1, result.Size());
		EXPECT_EQ(1, result.GetObjects().size());
		ASSERT_FALSE(result.IsEmpty());
		EXPECT_EQ(nonTerminal, result.GetObject());
	}
	{
		const ReverseLookup<deamer::language::type::definition::object::main::NonTerminal>
			reverseLookup(&reference_copy);

		const auto result = reverseLookup.Get(productionRule);

		EXPECT_TRUE(result.Success());
		EXPECT_EQ(CacheLocation::Primary, result.GetCacheLocation());
		EXPECT_EQ(1, result.Size());
		EXPECT_EQ(1, result.GetObjects().size());
		ASSERT_FALSE(result.IsEmpty());
		EXPECT_EQ(nonTerminal, result.GetObject());
	}
}

TEST_F(
	TestReverseLookup,
	ReverseLookupOfNonTerminal_UsesCvUnqualifiedType_Thrice_ReuseReverseLookupObject_ReturnsCorrectNonTerminal_SecondFindShouldComeFromPrimaryCache)
{
	ReferenceType reference_initial(language);

	const ReverseLookup<deamer::language::type::definition::object::main::NonTerminal>
		reverseLookup(&reference_initial);

	const auto* nonTerminal =
		reference_initial.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");
	auto* productionRule = nonTerminal->ProductionRules[0];

	{
		const auto result = reverseLookup.Get(productionRule);

		EXPECT_TRUE(result.Success());
		EXPECT_EQ(CacheLocation::Secondary, result.GetCacheLocation());
		EXPECT_EQ(1, result.Size());
		EXPECT_EQ(1, result.GetObjects().size());
		ASSERT_FALSE(result.IsEmpty());
		EXPECT_EQ(nonTerminal, result.GetObject());
	}
	{
		const auto result = reverseLookup.Get(productionRule);

		EXPECT_TRUE(result.Success());
		EXPECT_EQ(CacheLocation::Primary, result.GetCacheLocation());
		EXPECT_EQ(1, result.Size());
		EXPECT_EQ(1, result.GetObjects().size());
		ASSERT_FALSE(result.IsEmpty());
		EXPECT_EQ(nonTerminal, result.GetObject());
	}
	{
		const auto result = reverseLookup.Get(productionRule);

		EXPECT_TRUE(result.Success());
		EXPECT_EQ(CacheLocation::Primary, result.GetCacheLocation());
		EXPECT_EQ(1, result.Size());
		EXPECT_EQ(1, result.GetObjects().size());
		ASSERT_FALSE(result.IsEmpty());
		EXPECT_EQ(nonTerminal, result.GetObject());
	}
}

TEST_F(
	TestReverseLookup,
	ReverseLookupOfNonTerminal_UsesCvUnqualifiedType_Thrice_ReuseReverseLookupObject_CopyReference_ReturnsCorrectNonTerminal_SecondFindShouldComeFromPrimaryCache)
{
	ReferenceType reference_initial(language);
	ReferenceType reference_copy(reference_initial);

	const ReverseLookup<deamer::language::type::definition::object::main::NonTerminal>
		reverseLookup(&reference_copy);

	const auto* nonTerminal =
		reference_initial.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");
	auto* productionRule = nonTerminal->ProductionRules[0];

	{
		const auto result = reverseLookup.Get(productionRule);

		EXPECT_TRUE(result.Success());
		EXPECT_EQ(CacheLocation::Secondary, result.GetCacheLocation());
		EXPECT_EQ(1, result.Size());
		EXPECT_EQ(1, result.GetObjects().size());
		ASSERT_FALSE(result.IsEmpty());
		EXPECT_EQ(nonTerminal, result.GetObject());
	}
	{
		const auto result = reverseLookup.Get(productionRule);

		EXPECT_TRUE(result.Success());
		EXPECT_EQ(CacheLocation::Primary, result.GetCacheLocation());
		EXPECT_EQ(1, result.Size());
		EXPECT_EQ(1, result.GetObjects().size());
		ASSERT_FALSE(result.IsEmpty());
		EXPECT_EQ(nonTerminal, result.GetObject());
	}
	{
		const auto result = reverseLookup.Get(productionRule);

		EXPECT_TRUE(result.Success());
		EXPECT_EQ(CacheLocation::Primary, result.GetCacheLocation());
		EXPECT_EQ(1, result.Size());
		EXPECT_EQ(1, result.GetObjects().size());
		ASSERT_FALSE(result.IsEmpty());
		EXPECT_EQ(nonTerminal, result.GetObject());
	}
}

TEST_F(
	TestReverseLookup,
	ReverseLookupOfNonTerminal_UseNullptr_ReturnsCorrectCacheLocation_SecondFindShouldComeFromPrimaryCache)
{
	ReferenceType reference_initial(language);

	const ReverseLookup<deamer::language::type::definition::object::main::NonTerminal>
		reverseLookup(&reference_initial);

	const auto* nonTerminal =
		reference_initial.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");
	deamer::language::type::definition::object::main::ProductionRule* productionRule = nullptr;

	{
		const auto result = reverseLookup.Get(productionRule);

		EXPECT_TRUE(result.Fail());
		EXPECT_EQ(CacheLocation::None, result.GetCacheLocation());
		EXPECT_EQ(0, result.Size());
		EXPECT_EQ(0, result.GetObjects().size());
		EXPECT_TRUE(result.IsEmpty());
	}
	{
		const auto result = reverseLookup.Get(productionRule);

		EXPECT_TRUE(result.Fail());
		EXPECT_EQ(CacheLocation::None, result.GetCacheLocation());
		EXPECT_EQ(0, result.Size());
		EXPECT_EQ(0, result.GetObjects().size());
		EXPECT_TRUE(result.IsEmpty());
	}
	{
		const auto result = reverseLookup.Get(productionRule);

		EXPECT_TRUE(result.Fail());
		EXPECT_EQ(CacheLocation::None, result.GetCacheLocation());
		EXPECT_EQ(0, result.Size());
		EXPECT_EQ(0, result.GetObjects().size());
		EXPECT_TRUE(result.IsEmpty());
	}
}

TEST_F(
	TestReverseLookup,
	ReverseLookupOfNonTerminal_UseNullptr_ReturnsCorrectCacheLocation_CopyReference_SecondFindShouldComeFromPrimaryCache)
{
	ReferenceType reference_initial(language);
	ReferenceType reference_copy(reference_initial);

	const ReverseLookup<deamer::language::type::definition::object::main::NonTerminal>
		reverseLookup(&reference_copy);

	const auto* nonTerminal =
		reference_initial.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");
	deamer::language::type::definition::object::main::ProductionRule* productionRule = nullptr;

	{
		const auto result = reverseLookup.Get(productionRule);

		EXPECT_TRUE(result.Fail());
		EXPECT_EQ(CacheLocation::None, result.GetCacheLocation());
		EXPECT_EQ(0, result.Size());
		EXPECT_EQ(0, result.GetObjects().size());
		EXPECT_TRUE(result.IsEmpty());
	}
	{
		const auto result = reverseLookup.Get(productionRule);

		EXPECT_TRUE(result.Fail());
		EXPECT_EQ(CacheLocation::None, result.GetCacheLocation());
		EXPECT_EQ(0, result.Size());
		EXPECT_EQ(0, result.GetObjects().size());
		EXPECT_TRUE(result.IsEmpty());
	}
	{
		const auto result = reverseLookup.Get(productionRule);

		EXPECT_TRUE(result.Fail());
		EXPECT_EQ(CacheLocation::None, result.GetCacheLocation());
		EXPECT_EQ(0, result.Size());
		EXPECT_EQ(0, result.GetObjects().size());
		EXPECT_TRUE(result.IsEmpty());
	}
}

TEST_F(
	TestReverseLookup,
	ReverseLookupOfNonTerminal_UseUnknownPointer_ReturnsCorrectCacheLocation_CopyReference_SecondFindShouldComeFromPrimaryCache)
{
	ReferenceType reference_initial(language);
	ReferenceType reference_copy(reference_initial);

	const ReverseLookup<deamer::language::type::definition::object::main::NonTerminal>
		reverseLookup(&reference_copy);

	const auto* nonTerminal =
		reference_initial.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");

	// dangerous, but as we don't access the pointer
	// This should not fail.
	deamer::language::type::definition::object::main::ProductionRule* productionRule =
		(deamer::language::type::definition::object::main::ProductionRule*)nullptr + 1;

	{
		const auto result = reverseLookup.Get(productionRule);

		EXPECT_TRUE(result.Fail());
		EXPECT_EQ(CacheLocation::None, result.GetCacheLocation());
		EXPECT_EQ(0, result.Size());
		EXPECT_EQ(0, result.GetObjects().size());
		EXPECT_TRUE(result.IsEmpty());
	}
	{
		const auto result = reverseLookup.Get(productionRule);

		EXPECT_TRUE(result.Fail());
		EXPECT_EQ(CacheLocation::None, result.GetCacheLocation());
		EXPECT_EQ(0, result.Size());
		EXPECT_EQ(0, result.GetObjects().size());
		EXPECT_TRUE(result.IsEmpty());
	}
	{
		const auto result = reverseLookup.Get(productionRule);

		EXPECT_TRUE(result.Fail());
		EXPECT_EQ(CacheLocation::None, result.GetCacheLocation());
		EXPECT_EQ(0, result.Size());
		EXPECT_EQ(0, result.GetObjects().size());
		EXPECT_TRUE(result.IsEmpty());
	}
}
