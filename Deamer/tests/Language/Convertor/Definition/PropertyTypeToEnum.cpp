#include <Deamer/Language/Convertor/Definition/PropertyTypeToEnum.h>
#include <Deamer/Language/Type/Definition/Property/Type.h>
#include <gtest/gtest.h>

using Type = deamer::language::type::definition::property::Type;
using namespace deamer::language::convertor::definition;
using namespace deamer::language::type::definition::property::main;

class TestPropertyTypeToEnum : public testing::Test
{
protected:
	TestPropertyTypeToEnum() = default;
	virtual ~TestPropertyTypeToEnum() = default;

};

TEST_F(TestPropertyTypeToEnum, ConvertTypeToEnum_CorrectEnumIsReturned)
{
	EXPECT_EQ(Type::Associativity,		PropertyTypeToEnum<Associativity>::value);
	EXPECT_EQ(Type::AstOptimization,	PropertyTypeToEnum<AstOptimization>::value);
	EXPECT_EQ(Type::AstTranslation,		PropertyTypeToEnum<AstTranslation>::value);
	EXPECT_EQ(Type::Colorization,		PropertyTypeToEnum<Colorization>::value);
	EXPECT_EQ(Type::Documentation,		PropertyTypeToEnum<Documentation>::value);
	EXPECT_EQ(Type::Formatting,			PropertyTypeToEnum<Formatting>::value);
	EXPECT_EQ(Type::Precendence,		PropertyTypeToEnum<Precendence>::value);
	EXPECT_EQ(Type::Lexicon,			PropertyTypeToEnum<Lexicon>::value);
	EXPECT_EQ(Type::Grammar,			PropertyTypeToEnum<Grammar>::value);
	EXPECT_EQ(Type::Semantic,			PropertyTypeToEnum<Semantic>::value);
}

TEST_F(TestPropertyTypeToEnum, ConvertUnknownPropertyTypeToEnum_ShouldReturnUnknown)
{
	EXPECT_EQ(Type::Unknown, PropertyTypeToEnum<int>::value);
	EXPECT_EQ(Type::Unknown, PropertyTypeToEnum<double>::value);
	EXPECT_EQ(Type::Unknown, PropertyTypeToEnum<long>::value);
	EXPECT_EQ(Type::Unknown, PropertyTypeToEnum<char>::value);
}