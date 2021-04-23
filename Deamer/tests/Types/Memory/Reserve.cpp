#include <Deamer/Type/Memory/Reserve.h>
#include <gtest/gtest.h>

using namespace deamer::type;

class TestReserve : public testing::Test
{
protected:
	TestReserve() = default;
	virtual ~TestReserve() = default;

};

TEST_F(TestReserve, reserveMemory_MemoryShouldBeReserved)
{
	const Reserve<int> reserved;

	EXPECT_TRUE(nullptr != reserved.Pointer());

	delete reserved.Pointer();
}

TEST_F(TestReserve, reserve2MemorySlots_BothPointersAreReservedAndNotTheSameSpot)
{
	const Reserve<int> reserved1;
	const Reserve<int> reserved2;
	EXPECT_TRUE(nullptr != reserved1.Pointer());
	EXPECT_TRUE(nullptr != reserved2.Pointer());
	
	EXPECT_TRUE(reserved1.Pointer() != reserved2.Pointer());

	delete reserved1.Pointer();
	delete reserved2.Pointer();
}

TEST_F(TestReserve, reserveMemoryAndPutInInteger_IntegerShouldBeAtTheReservedSpot)
{
	const Reserve<int> reserved;
	const int expectedValue = 100;

	reserved.Set(expectedValue);

	EXPECT_EQ(expectedValue, reserved.Get());
	
	delete reserved.Pointer();
}

TEST_F(TestReserve, reserveMemoryAndPutInInteger_IntegerShouldBeAtTheReservedSpotWhichPointerPointsAt)
{
	const Reserve<int> reserved;
	const int expectedValue = 100;

	reserved.Set(expectedValue);

	EXPECT_EQ(expectedValue, *reserved.Pointer());
	
	delete reserved.Pointer();
}

TEST_F(TestReserve, reserveMultipleMemorySpotsAndAssignIntegers_MemoryShouldNotBeOverriden)
{
	const Reserve<int> reserved1;
	const Reserve<int> reserved2;
	const int expected1Value = 100;
	const int expected2Value = 883977212;

	reserved1.Set(expected1Value);
	reserved2.Set(expected2Value);

	EXPECT_EQ(expected1Value, reserved1.Get());
	EXPECT_EQ(expected2Value, reserved2.Get());
	
	delete reserved1.Pointer();
	delete reserved2.Pointer();
}

TEST_F(TestReserve, reserveSizeShouldBeTypeSize)
{
	const Reserve<int> reserveInt;
	const Reserve<char> reserveChar;
	const Reserve<Reserve<int>> reserveReserveInt;
	
	EXPECT_EQ(sizeof(int), reserveInt.size);
	EXPECT_EQ(sizeof(char), reserveChar.size);
	EXPECT_EQ(sizeof(Reserve<int>), reserveReserveInt.size);
	
	delete reserveInt.Pointer();
	delete reserveChar.Pointer();
	delete reserveReserveInt.Pointer();
}