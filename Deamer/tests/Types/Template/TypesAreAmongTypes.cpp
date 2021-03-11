#include <Deamer/Type/Template/TypesAreAmongTypes.h>
#include <gtest/gtest.h>

using namespace deamer::type;

class TestTypesAreAmongTypes : public testing::Test
{
protected:
	TestTypesAreAmongTypes() = default;
	virtual ~TestTypesAreAmongTypes() = default;
};

TEST_F(TestTypesAreAmongTypes, CheckForType_ShouldReturnTrue)
{
	static constexpr bool actual = TypesAreAmongTypes<int, char>::value<int>;
	EXPECT_TRUE(actual);
}

TEST_F(TestTypesAreAmongTypes, CheckForTypes_ShouldReturnTrue)
{
	static constexpr bool actual = TypesAreAmongTypes<int, char, double>::value<int, char>;
	EXPECT_TRUE(actual);
}

TEST_F(TestTypesAreAmongTypes, CheckForNonExistingType_ShouldReturnFalse)
{
	static constexpr bool actual = TypesAreAmongTypes<int, char, double>::value<long>;
	EXPECT_FALSE(actual);
}

TEST_F(TestTypesAreAmongTypes, CheckForNonExistingTypes_ShouldReturnFalse)
{
	static constexpr bool actual = TypesAreAmongTypes<int, char, double>::value<long, std::string>;
	EXPECT_FALSE(actual);
}

TEST_F(TestTypesAreAmongTypes, CheckForSomeExistingAndSomeNonExistingTypes_ShouldReturnFalse)
{
	static constexpr bool actual = TypesAreAmongTypes<int, char, double>::value<int, long, std::string>;
	EXPECT_FALSE(actual);
}