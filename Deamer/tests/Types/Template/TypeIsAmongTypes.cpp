#include <Deamer/Type/Template/TypeIsAmongTypes.h>
#include <gtest/gtest.h>

using namespace deamer::type;

class TestTypeIsAmongTypes : public testing::Test
{
protected:
	TestTypeIsAmongTypes() = default;
	virtual ~TestTypeIsAmongTypes() = default;
};

TEST_F(TestTypeIsAmongTypes, CheckForType_ShouldReturnTrue)
{
	static constexpr bool actual = TypeIsAmongTypes<char, int, char>::value;
	EXPECT_TRUE(actual);
}

TEST_F(TestTypeIsAmongTypes, CheckForNonExistingType_ShouldReturnFalse)
{
	static constexpr bool actual = TypeIsAmongTypes<double, int, char>::value;
	EXPECT_FALSE(actual);
}