#include "GetFirstDefaultGeneratorInGenerators.h"
#include <gtest/gtest.h>

class TestGetFirstDefaultGeneratorInGenerators : public testing::Test
{
protected:
	TestGetFirstDefaultGeneratorInGenerators() = default;
	virtual ~TestGetFirstDefaultGeneratorInGenerators() = default;
};

TEST_F(TestGetFirstDefaultGeneratorInGenerators, DefaultGenerator_ReturnDefaultGenerator)
{
	using actualType = GetFirstDefaultGeneratorInGenerators <DerivedPrecedence>::type;
	static constexpr bool actual = std::is_same<DerivedPrecedence, actualType>::value;

	EXPECT_TRUE(actual);
}

TEST_F(TestGetFirstDefaultGeneratorInGenerators, NonDefaultGenerator_ReturnVoidType)
{
	using actualType = GetFirstDefaultGeneratorInGenerators <DerivedGrammar>::type;
	static constexpr bool actual = std::is_same<void, actualType>::value;

	EXPECT_TRUE(actual);
}

TEST_F(TestGetFirstDefaultGeneratorInGenerators, SetWithGeneratorsAndDefaultGenerator_ReturnFirstDefaultGenerator)
{
	using actualType = GetFirstDefaultGeneratorInGenerators <DerivedGrammar, DerivedPrecedence>::type;
	static constexpr bool actual = std::is_same<DerivedPrecedence, actualType>::value;

	EXPECT_TRUE(actual);
}

TEST_F(TestGetFirstDefaultGeneratorInGenerators, SetWithGeneratorsAndMultipleOfTheSameDefaultGenerator_ReturnFirstDefaultGenerator)
{
	using actualType = GetFirstDefaultGeneratorInGenerators <DerivedGrammar, DerivedPrecedence, DerivedPrecedence>::type;
	static constexpr bool actual = std::is_same<DerivedPrecedence, actualType>::value;

	EXPECT_TRUE(actual);
}

TEST_F(TestGetFirstDefaultGeneratorInGenerators, SetWithGeneratorsAndDifferentDefaultGenerator_ReturnFirstDefaultGenerator)
{
	using actualType = GetFirstDefaultGeneratorInGenerators <DerivedGrammar, DerivedPrecedence, DerivedPrecedence1>::type;
	static constexpr bool actual = std::is_same<DerivedPrecedence, actualType>::value;

	EXPECT_TRUE(actual);
}

TEST_F(TestGetFirstDefaultGeneratorInGenerators, SetWithGeneratorsAndDefaultGeneratorWithGeneratorsAfterDefaultGenerator_ReturnFirstDefaultGenerator)
{
	using actualType = GetFirstDefaultGeneratorInGenerators <DerivedGrammar, DerivedPrecedence, DerivedLexicon>::type;
	static constexpr bool actual = std::is_same<DerivedPrecedence, actualType>::value;

	EXPECT_TRUE(actual);
}
