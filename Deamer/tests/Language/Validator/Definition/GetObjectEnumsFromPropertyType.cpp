#include <Deamer/Language/Type/Definition/Property/Type.h>
#include <Deamer/Language/Validator/Definition/GetObjectEnumsFromPropertyType.h>
#include <gtest/gtest.h>

using Type = deamer::language::type::definition::property::Type;
using namespace deamer::language::type::definition::property::main;
using namespace deamer::language::validator::definition;

class TestGetObjectEnumsFromPropertyType : public testing::Test
{
protected:
	TestGetObjectEnumsFromPropertyType() = default;
	virtual ~TestGetObjectEnumsFromPropertyType() = default;
};

TEST_F(TestGetObjectEnumsFromPropertyType,
	   GetObjectEnumsFromLexicon_ShouldReturn_Terminal_SpecialType)
{
	auto values = std::vector<deamer::language::type::definition::object::Type>(
		GetObjectEnumsFromPropertyType<Lexicon>::value);

	// If True, 26 asserts 27 and 28 are different
	// implying the different enumerations exist
	EXPECT_EQ(2, values.size());
	EXPECT_NE(values.at(0), values.at(1));
	EXPECT_TRUE(values.at(0) == deamer::language::type::definition::object::Type::Terminal ||
				values.at(0) == deamer::language::type::definition::object::Type::SpecialType);
	EXPECT_TRUE(values.at(1) == deamer::language::type::definition::object::Type::Terminal ||
				values.at(1) == deamer::language::type::definition::object::Type::SpecialType);
}

TEST_F(TestGetObjectEnumsFromPropertyType,
	   GetObjectEnumsFromPrecedence_ShouldReturn_ObjectPrecedence)
{
	auto values = std::vector<deamer::language::type::definition::object::Type>(
		GetObjectEnumsFromPropertyType<Precedence>::value);

	EXPECT_EQ(1, values.size());
	EXPECT_TRUE(values.at(0) == deamer::language::type::definition::object::Type::ObjectPrecedence);
}

TEST_F(TestGetObjectEnumsFromPropertyType,
	   GetObjectEnumsFromAssociativity_ShouldReturn_ObjectPrecedence)
{
	auto values = std::vector<deamer::language::type::definition::object::Type>(
		GetObjectEnumsFromPropertyType<Associativity>::value);

	EXPECT_EQ(2, values.size());
	EXPECT_NE(values.at(0), values.at(1));
	EXPECT_TRUE(
		values.at(0) == deamer::language::type::definition::object::Type::ObjectAssociativity ||
		values.at(0) == deamer::language::type::definition::object::Type::AssociativityType);
	EXPECT_TRUE(
		values.at(1) == deamer::language::type::definition::object::Type::ObjectAssociativity ||
		values.at(1) == deamer::language::type::definition::object::Type::AssociativityType);
}
