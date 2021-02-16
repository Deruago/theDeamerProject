#include <Deamer/Types/BitwiseEnum.h>
#include <gtest/gtest.h>

class TestBitwiseEnum : public testing::Test
{
protected:
	TestBitwiseEnum() = default;
	virtual ~TestBitwiseEnum() = default;

};

enum class TestableEnum
{
	one		= 0b0000'0001, // 1
	two		= 0b0000'0010, // 2
	three	= 0b0000'0100, // 4
	four	= 0b0000'1000, // 8
};

TEST_F(TestBitwiseEnum, InitialValueIs0)
{
	const BitwiseEnum<TestableEnum> bitwiseEnum;
	EXPECT_EQ(0, bitwiseEnum.value());
}

TEST_F(TestBitwiseEnum, Initial_AllFlagsAreNotChecked)
{
	const BitwiseEnum<TestableEnum> bitwiseEnum;

	EXPECT_FALSE(bitwiseEnum.is_flag_set(TestableEnum::one));
	EXPECT_FALSE(bitwiseEnum.is_flag_set(TestableEnum::two));
	EXPECT_FALSE(bitwiseEnum.is_flag_set(TestableEnum::three));
	EXPECT_FALSE(bitwiseEnum.is_flag_set(TestableEnum::four));
}

TEST_F(TestBitwiseEnum, SetFlag_ShouldReturnCorrectValue)
{
	BitwiseEnum<TestableEnum> bitwiseEnum;

	bitwiseEnum.set_flag(TestableEnum::one);
	EXPECT_EQ(1, bitwiseEnum.value());
}

TEST_F(TestBitwiseEnum, SetFlag_ShouldReturnCorrectEnumValue)
{
	BitwiseEnum<TestableEnum> bitwiseEnum;

	bitwiseEnum.set_flag(TestableEnum::one);
	EXPECT_EQ(TestableEnum::one, bitwiseEnum.enum_value());
}

TEST_F(TestBitwiseEnum, SetMultipleFlagsValueShouldIncrease)
{
	BitwiseEnum<TestableEnum> bitwiseEnum;

	bitwiseEnum.set_flag(TestableEnum::one);
	EXPECT_EQ(0b0000'0001, bitwiseEnum.value());

	bitwiseEnum.set_flag(TestableEnum::two);
	EXPECT_EQ(0b0000'0011, bitwiseEnum.value());

	bitwiseEnum.set_flag(TestableEnum::three);
	EXPECT_EQ(0b0000'0111, bitwiseEnum.value());

	bitwiseEnum.set_flag(TestableEnum::four);
	EXPECT_EQ(0b0000'1111, bitwiseEnum.value());
}

TEST_F(TestBitwiseEnum, SetFlagThenClearFlag_ValueShouldBe0)
{
	BitwiseEnum<TestableEnum> bitwiseEnum;

	bitwiseEnum.set_flag(TestableEnum::one);
	bitwiseEnum.clear_flag(TestableEnum::one);
	EXPECT_EQ(0b0000'0000, bitwiseEnum.value());

	bitwiseEnum.set_flag(TestableEnum::two);
	bitwiseEnum.clear_flag(TestableEnum::two);
	EXPECT_EQ(0b0000'0000, bitwiseEnum.value());

	bitwiseEnum.set_flag(TestableEnum::three);
	bitwiseEnum.clear_flag(TestableEnum::three);
	EXPECT_EQ(0b0000'0000, bitwiseEnum.value());

	bitwiseEnum.set_flag(TestableEnum::four);
	bitwiseEnum.clear_flag(TestableEnum::four);
	EXPECT_EQ(0b0000'0000, bitwiseEnum.value());
}

TEST_F(TestBitwiseEnum, SetFlags_ShouldCorrectlyCheckIfFlagIsChecked)
{
	BitwiseEnum<TestableEnum> bitwiseEnum;
	
	bitwiseEnum.set_flag(TestableEnum::one);
	EXPECT_TRUE(bitwiseEnum.is_flag_set(TestableEnum::one));
	EXPECT_FALSE(bitwiseEnum.is_flag_set(TestableEnum::two));
	EXPECT_FALSE(bitwiseEnum.is_flag_set(TestableEnum::three));
	EXPECT_FALSE(bitwiseEnum.is_flag_set(TestableEnum::four));

	bitwiseEnum.set_flag(TestableEnum::two);
	EXPECT_TRUE(bitwiseEnum.is_flag_set(TestableEnum::one));
	EXPECT_TRUE(bitwiseEnum.is_flag_set(TestableEnum::two));
	EXPECT_FALSE(bitwiseEnum.is_flag_set(TestableEnum::three));
	EXPECT_FALSE(bitwiseEnum.is_flag_set(TestableEnum::four));

	bitwiseEnum.set_flag(TestableEnum::three);
	EXPECT_TRUE(bitwiseEnum.is_flag_set(TestableEnum::one));
	EXPECT_TRUE(bitwiseEnum.is_flag_set(TestableEnum::two));
	EXPECT_TRUE(bitwiseEnum.is_flag_set(TestableEnum::three));
	EXPECT_FALSE(bitwiseEnum.is_flag_set(TestableEnum::four));

	bitwiseEnum.set_flag(TestableEnum::four);
	EXPECT_TRUE(bitwiseEnum.is_flag_set(TestableEnum::one));
	EXPECT_TRUE(bitwiseEnum.is_flag_set(TestableEnum::two));
	EXPECT_TRUE(bitwiseEnum.is_flag_set(TestableEnum::three));
	EXPECT_TRUE(bitwiseEnum.is_flag_set(TestableEnum::four));
}

TEST_F(TestBitwiseEnum, SetFlags_ShouldCorrectlyCheckIfSeveralFlagsAreChecked)
{
	BitwiseEnum<TestableEnum> bitwiseEnum;

	EXPECT_TRUE(bitwiseEnum.are_flags_set({ }));

	bitwiseEnum.set_flag(TestableEnum::one);
	EXPECT_TRUE(bitwiseEnum.are_flags_set({ TestableEnum::one }));

	bitwiseEnum.set_flag(TestableEnum::two);
	EXPECT_TRUE(bitwiseEnum.are_flags_set({ TestableEnum::one, TestableEnum::two }));

	bitwiseEnum.set_flag(TestableEnum::three);
	EXPECT_TRUE(bitwiseEnum.are_flags_set({ TestableEnum::one, TestableEnum::two, TestableEnum::three }));

	bitwiseEnum.set_flag(TestableEnum::four);
	EXPECT_TRUE(bitwiseEnum.are_flags_set({ TestableEnum::one, TestableEnum::two, TestableEnum::three, TestableEnum::four }));
}

TEST_F(TestBitwiseEnum, SetFlags_ShouldCorrectlyCheckIfSeveralFlagsAreNotChecked)
{
	BitwiseEnum<TestableEnum> bitwiseEnum;

	EXPECT_TRUE(bitwiseEnum.are_flags_not_set({ TestableEnum::one, TestableEnum::two, TestableEnum::three, TestableEnum::four }));

	bitwiseEnum.set_flag(TestableEnum::one);
	EXPECT_TRUE(bitwiseEnum.are_flags_not_set({ TestableEnum::two, TestableEnum::three, TestableEnum::four }));

	bitwiseEnum.set_flag(TestableEnum::two);
	EXPECT_TRUE(bitwiseEnum.are_flags_not_set({ TestableEnum::three, TestableEnum::four }));

	bitwiseEnum.set_flag(TestableEnum::three);
	EXPECT_TRUE(bitwiseEnum.are_flags_not_set({ TestableEnum::four }));

	bitwiseEnum.set_flag(TestableEnum::four);
	EXPECT_TRUE(bitwiseEnum.are_flags_not_set({ }));
}

TEST_F(TestBitwiseEnum, BitwiseOperationsWithEnumValues_ShouldCorrectlyApplyBitwiseOperations)
{
	BitwiseEnum<TestableEnum> bitwiseEnum;
	unsigned expectedValue = 0;

	expectedValue	|= 0b0000'0011;
	bitwiseEnum		|= TestableEnum::one;
	bitwiseEnum		|= TestableEnum::two;
	EXPECT_EQ(expectedValue, bitwiseEnum.value());

	expectedValue	&= 0b0000'0010;
	bitwiseEnum		&= TestableEnum::two;
	EXPECT_EQ(expectedValue, bitwiseEnum.value());

	expectedValue	^= 0b0000'1000;
	bitwiseEnum		^= TestableEnum::four;
	EXPECT_EQ(expectedValue, bitwiseEnum.value());

	expectedValue	&= ~0b0000'1010; // reset to 0
	bitwiseEnum		&= static_cast<TestableEnum>(~static_cast<unsigned>(TestableEnum::two));
	bitwiseEnum		&= static_cast<TestableEnum>(~static_cast<unsigned>(TestableEnum::four));
	EXPECT_EQ(expectedValue, bitwiseEnum.value());
}

TEST_F(TestBitwiseEnum, BitwiseOperationsWithUnsignedValues_ShouldCorrectlyApplyBitwiseOperations)
{
	BitwiseEnum<TestableEnum> bitwiseEnum;
	unsigned expectedValue = 0;

	expectedValue	|= 0b0000'0011;
	bitwiseEnum		|= 0b0000'0011;
	EXPECT_EQ(expectedValue, bitwiseEnum.value());

	expectedValue	&= 0b0000'0010;
	bitwiseEnum		&= 0b0000'0010;
	EXPECT_EQ(expectedValue, bitwiseEnum.value());

	expectedValue	^= 0b0000'1000;
	bitwiseEnum		^= 0b0000'1000;
	EXPECT_EQ(expectedValue, bitwiseEnum.value());

	expectedValue	&= ~0b0000'1010; // reset to 0
	bitwiseEnum		&= ~0b0000'1010;
	EXPECT_EQ(expectedValue, bitwiseEnum.value());
}

TEST_F(TestBitwiseEnum, SetSeveralFlags_ShouldReturnTotalFlagsSet)
{
	BitwiseEnum<TestableEnum> bitwiseEnum;

	bitwiseEnum.set_flag(TestableEnum::one);
	EXPECT_EQ(1, bitwiseEnum.active_flags());
	
	bitwiseEnum.set_flag(TestableEnum::two);
	EXPECT_EQ(2, bitwiseEnum.active_flags());
	
	bitwiseEnum.set_flag(TestableEnum::three);
	EXPECT_EQ(3, bitwiseEnum.active_flags());
	
	bitwiseEnum.set_flag(TestableEnum::four);
	EXPECT_EQ(4, bitwiseEnum.active_flags());
}