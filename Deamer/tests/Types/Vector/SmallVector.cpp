#include <Deamer/Types/Vector/SmallVector.h>
#include <gtest/gtest.h>

class TestSmallVector : public testing::Test
{
protected:
	TestSmallVector() = default;
	virtual ~TestSmallVector() = default;

};

TEST_F(TestSmallVector, Add5Integers_ShouldHaveCorrectVectorOfIntegers)
{
	SmallVector<int, 5> smallVector;

	smallVector.push_back(1);
	smallVector.push_back(4);
	smallVector.push_back(3);
	smallVector.push_back(5);
	smallVector.push_back(2);


	EXPECT_EQ(5, smallVector.capacity());
	EXPECT_EQ(5, smallVector.size());

	EXPECT_EQ(1, smallVector[0]);
	EXPECT_EQ(4, smallVector[1]);
	EXPECT_EQ(3, smallVector[2]);
	EXPECT_EQ(5, smallVector[3]);
	EXPECT_EQ(2, smallVector[4]);

	EXPECT_EQ(5, smallVector.capacity());
	EXPECT_EQ(5, smallVector.size());
}

TEST_F(TestSmallVector, Add5Integers_SmallVectorIsTooSmall_ShouldHaveCorrectVectorOfIntegers)
{
	SmallVector<int, 2> smallVector;
	smallVector.push_back(1);
	smallVector.push_back(4);
	smallVector.push_back(3);
	smallVector.push_back(5);
	smallVector.push_back(2);

	EXPECT_EQ(5, smallVector.size());
	EXPECT_EQ(1, smallVector[0]);
	EXPECT_EQ(4, smallVector[1]);
	EXPECT_EQ(3, smallVector[2]);
	EXPECT_EQ(5, smallVector[3]);
	EXPECT_EQ(2, smallVector[4]);
	EXPECT_EQ(5, smallVector.size());
}

TEST_F(TestSmallVector, Add5IntegersThenPopBack3Integers_SmallVectorShouldHave2Integers)
{
	SmallVector<int, 2> smallVector;
	smallVector.push_back(1);
	smallVector.push_back(4);
	smallVector.push_back(3);
	smallVector.push_back(5);
	smallVector.push_back(2);

	smallVector.pop_back();
	smallVector.pop_back();
	smallVector.pop_back();

	EXPECT_EQ(2, smallVector.size());

	EXPECT_EQ(1, smallVector[0]);
	EXPECT_EQ(4, smallVector[1]);

	EXPECT_EQ(2, smallVector.size());
}

TEST_F(TestSmallVector, ConvertSmallVectorToSmallVectorBase_SmallVectorIsAccessibleThroughSmallVectorBase)
{
	SmallVector<int, 2> smallVector;
	smallVector.push_back(1);
	smallVector.push_back(4);
	smallVector.push_back(3);
	smallVector.push_back(5);
	smallVector.push_back(2);

	SmallVectorBase<int> smallVectorBase = smallVector;


	EXPECT_EQ(5, smallVectorBase.size());

	EXPECT_EQ(1, smallVectorBase[0]);
	EXPECT_EQ(4, smallVectorBase[1]);
	EXPECT_EQ(3, smallVectorBase[2]);
	EXPECT_EQ(5, smallVectorBase[3]);
	EXPECT_EQ(2, smallVectorBase[4]);

	EXPECT_EQ(5, smallVectorBase.size());
}

SmallVector<int, 3> TestSmallVector_ReturnSimpleSmallVectorOfSize3()
{
	SmallVector<int, 3> smallVector;
	smallVector.push_back(1);
	smallVector.push_back(2);
	smallVector.push_back(3);

	return smallVector;
}
TEST_F(TestSmallVector, ReturnSmallVectorAsFunctionReturnValue_GetCorrectSmallVector)
{
	SmallVector<int, 3> smallVector = TestSmallVector_ReturnSimpleSmallVectorOfSize3();

	EXPECT_EQ(3, smallVector.capacity());
	EXPECT_EQ(3, smallVector.size());

	EXPECT_EQ(1, smallVector[0]);
	EXPECT_EQ(2, smallVector[1]);
	EXPECT_EQ(3, smallVector[2]);

	EXPECT_EQ(3, smallVector.capacity());
	EXPECT_EQ(3, smallVector.size());
}

TEST_F(TestSmallVector, ReturnSmallVectorAsFunctionReturnValue_UseSmallVectorBaseToContainReturnValue_GetCorrectSmallVectorBase)
{
	SmallVectorBase<int> smallVector = TestSmallVector_ReturnSimpleSmallVectorOfSize3();

	EXPECT_EQ(3, smallVector.capacity());
	EXPECT_EQ(3, smallVector.size());

	EXPECT_EQ(1, smallVector[0]);
	EXPECT_EQ(2, smallVector[1]);
	EXPECT_EQ(3, smallVector[2]);

	EXPECT_EQ(3, smallVector.capacity());
	EXPECT_EQ(3, smallVector.size());
}

SmallVectorBase<int> TestSmallVector_ReturnSimpleSmallVectorBaseOfSizeN(const int total)
{
	SmallVector<int, 3> smallVector;
	for (auto i = 0; i < total; i++)
	{
		smallVector.push_back(i + 1); // so we get sequence: 1,2,3,4,5...
	}

	return smallVector;
}
TEST_F(TestSmallVector, ReturnSmallVectorBaseAsFunctionReturnValue_GetCorrectSmallVectorBase)
{
	SmallVectorBase<int> smallVector = TestSmallVector_ReturnSimpleSmallVectorBaseOfSizeN(5);

	EXPECT_EQ(5, smallVector.size());

	EXPECT_EQ(1, smallVector[0]);
	EXPECT_EQ(2, smallVector[1]);
	EXPECT_EQ(3, smallVector[2]);
	EXPECT_EQ(4, smallVector[3]);
	EXPECT_EQ(5, smallVector[4]);

	EXPECT_EQ(5, smallVector.size());
}

TEST_F(TestSmallVector, MoveIntegerIntoVector_IntegerIsCorrectlyMoved)
{
	SmallVector<int, 3> smallVector;

	int integer1 = 4;
	smallVector.push_back(std::move(integer1));
	int integer2 = -12;
	smallVector.push_back(std::move(integer2));

	EXPECT_EQ(4, smallVector[0]);
	EXPECT_EQ(-12, smallVector[1]);
}

TEST_F(TestSmallVector, CtorSmallVectorBaseInitialisation)
{
	SmallVectorBase<int> smallvector = SmallVectorBase<int>(5);

	EXPECT_EQ(5, smallvector.capacity());
}