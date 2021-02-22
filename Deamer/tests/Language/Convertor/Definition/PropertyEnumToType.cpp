#include <Deamer/Language/Convertor/Definition/PropertyEnumToType.h>
#include <Deamer/Language/Convertor/Definition/PropertyTypeToEnum.h>
#include <Deamer/Language/Type/Definition/Property/Type.h>
#include <gtest/gtest.h>

using Type = deamer::language::type::definition::property::Type;
using namespace deamer::language::convertor::definition;
using namespace deamer::language::type::definition::property::main;

class TestPropertyEnumToType : public testing::Test
{
protected:
	TestPropertyEnumToType() = default;
	virtual ~TestPropertyEnumToType() = default;

};

TEST_F(TestPropertyEnumToType, ConvertEnumToType_CorrectTypeIsReturned)
{
	EXPECT_EQ(Type::Associativity,		PropertyTypeToEnum<PropertyEnumToType<Type::Associativity>::type>::value);
	EXPECT_EQ(Type::AstOptimization,	PropertyTypeToEnum<PropertyEnumToType<Type::AstOptimization>::type>::value);
	EXPECT_EQ(Type::AstTranslation,		PropertyTypeToEnum<PropertyEnumToType<Type::AstTranslation>::type>::value);
	EXPECT_EQ(Type::Colorization,		PropertyTypeToEnum<PropertyEnumToType<Type::Colorization>::type>::value);
	EXPECT_EQ(Type::Documentation,		PropertyTypeToEnum<PropertyEnumToType<Type::Documentation>::type>::value);
	EXPECT_EQ(Type::Formatting,			PropertyTypeToEnum<PropertyEnumToType<Type::Formatting>::type>::value);
	EXPECT_EQ(Type::Precendence,		PropertyTypeToEnum<PropertyEnumToType<Type::Precendence>::type>::value);
	EXPECT_EQ(Type::Lexicon,			PropertyTypeToEnum<PropertyEnumToType<Type::Lexicon>::type>::value);
	EXPECT_EQ(Type::Grammar,			PropertyTypeToEnum<PropertyEnumToType<Type::Grammar>::type>::value);
	EXPECT_EQ(Type::Semantic,			PropertyTypeToEnum<PropertyEnumToType<Type::Semantic>::type>::value);
}

TEST_F(TestPropertyEnumToType, ConvertUnknownEnumToType_ShouldReturnUnknown)
{
	EXPECT_EQ(Type::Unknown, PropertyTypeToEnum<PropertyEnumToType<Type::Unknown>::type>::value);
}