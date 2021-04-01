#include <Deamer/Language/Reference/PropertyDefinition.h>
#include <gtest/gtest.h>

using Type = deamer::language::type::definition::property::Type;
using namespace deamer::language::reference;

class TestPropertyDefinition : public testing::Test
{
protected:
	TestPropertyDefinition() = default;
	virtual ~TestPropertyDefinition() = default;
};

TEST_F(TestPropertyDefinition, CheckIfEverythingIsCorrectlySet)
{
	using ReferenceType = PropertyDefinition<Type::Lexicon, Type::Grammar>;
	const auto language = deamer::language::type::definition::Language({}, {});
	auto reference = ReferenceType(&language);

	EXPECT_EQ(2, reference.totalRequestedTypes);
}
