#include <Deamer/Type/Template/TypesAreAmongTypesTillSpecificTypeIsFound.h>
#include <gtest/gtest.h>

using namespace deamer::type;

class TestTypesAreAmongTypesTillSpecificTypeIsFound : public testing::Test
{
protected:
	TestTypesAreAmongTypesTillSpecificTypeIsFound() = default;
	virtual ~TestTypesAreAmongTypesTillSpecificTypeIsFound() = default;
};

TEST_F(TestTypesAreAmongTypesTillSpecificTypeIsFound, CheckType_ShouldReturnTrue)
{
	static constexpr bool actual = TypesAreAmongTypesTillSpecificTypeIsFound<int, char, long, double, int>::value<char>;
	EXPECT_TRUE(actual);
}

TEST_F(TestTypesAreAmongTypesTillSpecificTypeIsFound, CheckType_ShouldReturnFalse)
{
	static constexpr bool actual = TypesAreAmongTypesTillSpecificTypeIsFound<int, char, long, double, int>::value<std::string>;
	EXPECT_FALSE(actual);
}

TEST_F(TestTypesAreAmongTypesTillSpecificTypeIsFound, CheckTypes_ShouldReturnTrue)
{
	static constexpr bool actual = TypesAreAmongTypesTillSpecificTypeIsFound<int, char, long, double, int>::value<char, double>;
	EXPECT_TRUE(actual);
}

TEST_F(TestTypesAreAmongTypesTillSpecificTypeIsFound, CheckTypes_ShouldReturnFalse)
{
	static constexpr bool actual = TypesAreAmongTypesTillSpecificTypeIsFound<int, char, long, double, int>::value<std::string, char>;
	EXPECT_FALSE(actual);
}

TEST_F(TestTypesAreAmongTypesTillSpecificTypeIsFound, CheckTypesAfterDeadType_ShouldReturnFalse)
{
	static constexpr bool actual = TypesAreAmongTypesTillSpecificTypeIsFound<int, char, int, long, double>::value<long, double>;
	EXPECT_FALSE(actual);
}

TEST_F(TestTypesAreAmongTypesTillSpecificTypeIsFound, CheckTypeAfterDeadType_ShouldReturnFalse)
{
	static constexpr bool actual = TypesAreAmongTypesTillSpecificTypeIsFound<int, char, int, long, double>::value<long>;
	EXPECT_FALSE(actual);
}