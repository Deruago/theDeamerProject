#include "../../Integration/Language/DefineSimpleLanguage.h"
#include <Deamer/Language/Reference/PropertyDefinition.h>
#include <gtest/gtest.h>

using Type = deamer::language::type::definition::property::Type;
using namespace deamer::language::reference;

class TestPropertyDefinition : public testing::Test
{
public:
	using ReferenceType = PropertyDefinition<Type::Lexicon, Type::Grammar>;

protected:
	LanguageDefinition languageDefinition;
	deamer::language::type::definition::Language* language;

	TestPropertyDefinition()
	{
		language = languageDefinition.GenerateLanguage();
	}

	virtual ~TestPropertyDefinition()
	{
		delete language;
	}
};

TEST_F(TestPropertyDefinition, CheckIfEverythingIsCorrectlySet)
{
	{
		using ReferenceType = PropertyDefinition<Type::Lexicon, Type::Grammar>;
		auto reference = ReferenceType(language);

		EXPECT_EQ(2, reference.totalRequestedTypes);
	}
	{
		using ReferenceType = PropertyDefinition<Type::Lexicon, Type::Lexicon, Type::Grammar>;
		auto reference = ReferenceType(language);

		EXPECT_EQ(3, reference.totalRequestedTypes);
	}
	{
		using ReferenceType = PropertyDefinition<>;
		auto reference = ReferenceType(language);

		EXPECT_EQ(0, reference.totalRequestedTypes);
	}
}
