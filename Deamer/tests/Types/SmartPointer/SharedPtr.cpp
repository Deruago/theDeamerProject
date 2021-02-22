#include <Deamer/Type/SmartPointer/SharedPtr.h>
#include <gtest/gtest.h>

using namespace deamer::type;

class TestSharedPtr : public testing::Test
{
protected:
	TestSharedPtr() = default;
	virtual ~TestSharedPtr() = default;

};

class DetectFree
{
public:
	static bool classIsFreed;
	DetectFree()
	{
		classIsFreed = false;
	}
	~DetectFree()
	{
		classIsFreed = true;
	}
};
bool DetectFree::classIsFreed = false;

TEST_F(TestSharedPtr, InitialValueIs0_IsDeletedShouldReturnTrue)
{
	const SharedPtr<unsigned> unsignedPtr;
	EXPECT_TRUE(unsignedPtr.IsDeleted());
}

TEST_F(TestSharedPtr, InitialValueIsValidPtr_IsDeletedShouldReturnFalse)
{
	const SharedPtr<unsigned> unsignedPtr(new unsigned());
	EXPECT_FALSE(unsignedPtr.IsDeleted());
}

TEST_F(TestSharedPtr, GiveValue_ShouldCorrectlyPointToValue)
{
	unsigned* const expectedValue = new unsigned(100);
	const SharedPtr<unsigned> unsignedPtr(expectedValue);

	const unsigned actualValue = unsignedPtr.GetReferenceToItem();

	EXPECT_EQ(*expectedValue, actualValue);
}

TEST_F(TestSharedPtr, GiveValue_DeepCopyShouldCorrectlyMakeADeepCopy)
{
	unsigned* const expectedValue = new unsigned(100);
	const SharedPtr<unsigned> unsignedPtr(expectedValue);

	const auto actualValue = unsignedPtr.DeepCopy();
	actualValue.GetReferenceToItem() = 2222;

	EXPECT_EQ(2222, actualValue.GetReferenceToItem());

	EXPECT_EQ(*expectedValue, unsignedPtr.GetReferenceToItem());
}

TEST_F(TestSharedPtr, GiveValue_DeepCopyValueAndPromotePointerAsSharedPtr)
{
	unsigned* const expectedValue = new unsigned(100);
	const SharedPtr<unsigned> unsignedPtr(expectedValue);

	auto deepCopyPtr = unsignedPtr.DeepCopy();
	const SharedPtr<unsigned> unsignedDeepCopiedPtr(deepCopyPtr);

	unsignedDeepCopiedPtr.GetReferenceToItem() = 222;

	EXPECT_EQ(*expectedValue, unsignedPtr.GetReferenceToItem());
	EXPECT_EQ(222, unsignedDeepCopiedPtr.GetReferenceToItem());
}

TEST_F(TestSharedPtr, GiveValue_ShouldDeletePointerWhenOutOfScope)
{
	
	DetectFree* const expectedValue = new DetectFree();
	EXPECT_FALSE(DetectFree::classIsFreed);

	// create scope
	{
		const SharedPtr<DetectFree> unsignedPtr(expectedValue);
	}

	EXPECT_TRUE(DetectFree::classIsFreed);
}

TEST_F(TestSharedPtr, GiveValueAndShareItWithSharedPtrAtMainScope_ShouldNotDeletePointer)
{
	DetectFree* const expectedValue = new DetectFree();
	EXPECT_FALSE(DetectFree::classIsFreed);
	
	SharedPtr<DetectFree> mainScope(expectedValue);
	
	// create scope
	{
		const SharedPtr<DetectFree> unsignedPtr(mainScope);
	}

	EXPECT_FALSE(DetectFree::classIsFreed);
}