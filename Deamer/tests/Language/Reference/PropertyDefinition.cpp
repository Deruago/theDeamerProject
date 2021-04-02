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

	void Test_ConstantReference(const ReferenceType reference)
	{
		const auto* varname = reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME");
		const auto* string = reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING");
		const auto* escape_chars =
			reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS");
		const auto* spaces = reference.GetDefinition<Type::Lexicon>().GetTerminal("SPACES");

		EXPECT_TRUE(varname != nullptr);
		EXPECT_TRUE(string != nullptr);
		EXPECT_TRUE(escape_chars != nullptr);
		EXPECT_TRUE(spaces != nullptr);

		EXPECT_EQ("VARNAME", varname->Name);
		EXPECT_EQ("STRING", string->Name);
		EXPECT_EQ("ESCAPE_CHARS", escape_chars->Name);
		EXPECT_EQ("SPACES", spaces->Name);
	}

	void Test_StandardReference(ReferenceType reference)
	{
		const auto* varname = reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME");
		const auto* string = reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING");
		const auto* escape_chars =
			reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS");
		const auto* spaces = reference.GetDefinition<Type::Lexicon>().GetTerminal("SPACES");

		EXPECT_TRUE(varname != nullptr);
		EXPECT_TRUE(string != nullptr);
		EXPECT_TRUE(escape_chars != nullptr);
		EXPECT_TRUE(spaces != nullptr);

		EXPECT_EQ("VARNAME", varname->Name);
		EXPECT_EQ("STRING", string->Name);
		EXPECT_EQ("ESCAPE_CHARS", escape_chars->Name);
		EXPECT_EQ("SPACES", spaces->Name);
	}

	// This gives compiler error, and cannot be used.
	// Using this is thus always wrong.
	/*void Test_CppReference(ReferenceType& reference)
	{
	}*/

	void Test_CppConstantReference(const ReferenceType& reference)
	{
		const auto* varname = reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME");
		const auto* string = reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING");
		const auto* escape_chars =
			reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS");
		const auto* spaces = reference.GetDefinition<Type::Lexicon>().GetTerminal("SPACES");

		EXPECT_TRUE(varname != nullptr);
		EXPECT_TRUE(string != nullptr);
		EXPECT_TRUE(escape_chars != nullptr);
		EXPECT_TRUE(spaces != nullptr);

		EXPECT_EQ("VARNAME", varname->Name);
		EXPECT_EQ("STRING", string->Name);
		EXPECT_EQ("ESCAPE_CHARS", escape_chars->Name);
		EXPECT_EQ("SPACES", spaces->Name);
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

TEST_F(TestPropertyDefinition, Test_ConstantReference)
{
	Test_ConstantReference(language);
}

TEST_F(TestPropertyDefinition, Test_StandardReference)
{
	Test_StandardReference(language);
}

TEST_F(TestPropertyDefinition, Test_CppConstantReference)
{
	Test_CppConstantReference(language);
}
