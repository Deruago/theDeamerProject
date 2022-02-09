#include "Deamer/Language/Type/Definition/Property/Main/Threat.h"
#include <Deamer/Language/Type/Definition/Property/Type.h>
#include <Deamer/Language/Validator/Definition/GetPropertyTypeFromObjectType.h>
#include <gtest/gtest.h>
#include <type_traits>

using Type = deamer::language::type::definition::property::Type;
using namespace deamer::language::type::definition::property::main;
using namespace deamer::language::validator::definition;

class TestGetPropertyTypeFromObjectType : public testing::Test
{
protected:
	TestGetPropertyTypeFromObjectType() = default;
	virtual ~TestGetPropertyTypeFromObjectType() = default;
};

TEST_F(TestGetPropertyTypeFromObjectType, GetPropertyTypeFromObjectType_GiveTerminal_ReturnLexicon)
{
	using expected_type = Lexicon;
	using actual_type = GetPropertyTypeFromObjectType<
		deamer::language::type::definition::object::main::Terminal>::type;

	const auto equality = std::is_same<expected_type, actual_type>::value;
	EXPECT_TRUE(equality);
}

TEST_F(TestGetPropertyTypeFromObjectType,
	   GetPropertyTypeFromObjectType_GiveSpecialType_ReturnLexicon)
{
	using expected_type = Lexicon;
	using actual_type = GetPropertyTypeFromObjectType<
		deamer::language::type::definition::object::main::SpecialType>::type;

	const auto equality = std::is_same<expected_type, actual_type>::value;
	EXPECT_TRUE(equality);
}

TEST_F(TestGetPropertyTypeFromObjectType,
	   GetPropertyTypeFromObjectType_GiveNonTerminal_ReturnGrammar)
{
	using expected_type = Grammar;
	using actual_type = GetPropertyTypeFromObjectType<
		deamer::language::type::definition::object::main::NonTerminal>::type;

	const auto equality = std::is_same<expected_type, actual_type>::value;
	EXPECT_TRUE(equality);
}

TEST_F(TestGetPropertyTypeFromObjectType,
	   GetPropertyTypeFromObjectType_GiveProductionRule_ReturnGrammar)
{
	using expected_type = Grammar;
	using actual_type = GetPropertyTypeFromObjectType<
		deamer::language::type::definition::object::main::ProductionRule>::type;

	const auto equality = std::is_same<expected_type, actual_type>::value;
	EXPECT_TRUE(equality);
}

TEST_F(TestGetPropertyTypeFromObjectType,
	   GetPropertyTypeFromObjectType_GiveNonTerminalAbstraction_ReturnGrammar)
{
	using expected_type = Grammar;
	using actual_type = GetPropertyTypeFromObjectType<
		deamer::language::type::definition::object::main::NonTerminalAbstraction>::type;

	const auto equality = std::is_same<expected_type, actual_type>::value;
	EXPECT_TRUE(equality);
}

TEST_F(TestGetPropertyTypeFromObjectType,
	   GetPropertyTypeFromObjectType_GiveObjectPrecedence_ReturnPrecedence)
{
	using expected_type = Precedence;
	using actual_type = GetPropertyTypeFromObjectType<
		deamer::language::type::definition::object::main::ObjectPrecedence>::type;

	const auto equality = std::is_same<expected_type, actual_type>::value;
	EXPECT_TRUE(equality);
}

TEST_F(TestGetPropertyTypeFromObjectType,
	   GetPropertyTypeFromObjectType_GiveObjectAssociativity_ReturnAssociativity)
{
	using expected_type = Associativity;
	using actual_type = GetPropertyTypeFromObjectType<
		deamer::language::type::definition::object::main::ObjectAssociativity>::type;

	const auto equality = std::is_same<expected_type, actual_type>::value;
	EXPECT_TRUE(equality);
}

TEST_F(TestGetPropertyTypeFromObjectType,
	   GetPropertyTypeFromObjectType_GiveAssociativityType_ReturnAssociativity)
{
	using expected_type = Associativity;
	using actual_type = GetPropertyTypeFromObjectType<
		deamer::language::type::definition::object::main::AssociativityType>::type;

	const auto equality = std::is_same<expected_type, actual_type>::value;
	EXPECT_TRUE(equality);
}

TEST_F(TestGetPropertyTypeFromObjectType, GetPropertyTypeFromObjectType_GiveThreat_ReturnThreat)
{
	using expected_type = Threat;
	using actual_type = GetPropertyTypeFromObjectType<
		deamer::language::type::definition::object::main::threat::Threat>::type;

	const auto equality = std::is_same<expected_type, actual_type>::value;
	EXPECT_TRUE(equality);
}
