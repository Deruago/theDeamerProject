#include "ColorfulLanguageDefinition.h"
#include <gtest/gtest.h>

using namespace ::deamer::test::language::threat::standard::generator;

class TestColorizationStandardGeneratorLPD : public testing::Test
{
protected:
	TestColorizationStandardGeneratorLPD() = default;
	virtual ~TestColorizationStandardGeneratorLPD() = default;

protected:
};

TEST_F(TestColorizationStandardGeneratorLPD,
	   LanguageWithSymbols_EqualizeSymbols_AllSymbolsShouldBeInReservedColorGroupOfSymbols)
{
	ColorfulLanguageDefinition language(true);
	auto* generatedLanguage = language.GenerateLanguage();
	
	const ::deamer::language::reference::PropertyDefinition<
		::deamer::language::type::definition::property::Type::Colorization,
		::deamer::language::type::definition::property::Type::Lexicon,
		::deamer::language::type::definition::property::Type::Grammar>
		colorizationReference(generatedLanguage);

	deamer::language::reference::ReverseLookup<
		::deamer::language::type::definition::object::main::TerminalColor>
		lookupTerminalColor(&colorizationReference);

	auto lexicon =
		colorizationReference
			.GetDefinition<::deamer::language::type::definition::property::Type::Lexicon>();

	auto result_varname = lookupTerminalColor.Get(lexicon.GetTerminal("VARNAME"));
	ASSERT_TRUE(result_varname.GetObjects().size() > 0);
	EXPECT_TRUE(result_varname.GetObjects().size() == 1);
	
	auto result_eq = lookupTerminalColor.Get(lexicon.GetTerminal("EQ"));
	ASSERT_TRUE(result_eq.GetObjects().size() > 0);
	EXPECT_TRUE(result_eq.GetObjects().size() == 1);
	
	auto result_semicolon = lookupTerminalColor.Get(lexicon.GetTerminal("SEMICOLON"));
	ASSERT_TRUE(result_semicolon.GetObjects().size() > 0);
	EXPECT_TRUE(result_semicolon.GetObjects().size() == 1);
	
	EXPECT_TRUE(result_varname.GetObject()->colorGroup->ColorId !=
				result_eq.GetObject()->colorGroup->ColorId);
	EXPECT_TRUE(result_varname.GetObject()->colorGroup->ColorId !=
				result_semicolon.GetObject()->colorGroup->ColorId);
	EXPECT_TRUE(result_eq.GetObject()->colorGroup->ColorId ==
				result_semicolon.GetObject()->colorGroup->ColorId);

	EXPECT_TRUE(result_eq.GetObject()->colorGroup->ColorId == 1025);
	EXPECT_TRUE(result_semicolon.GetObject()->colorGroup->ColorId == 1025);

	delete generatedLanguage;
}

TEST_F(TestColorizationStandardGeneratorLPD,
	   LanguageWithSymbols_DontEqualizeSymbols_AllSymbolsShouldNotBeInTheReservedGroupOfSymbols)
{
	ColorfulLanguageDefinition language;
	auto* generatedLanguage = language.GenerateLanguage();

	const ::deamer::language::reference::PropertyDefinition<
		::deamer::language::type::definition::property::Type::Colorization,
		::deamer::language::type::definition::property::Type::Lexicon,
		::deamer::language::type::definition::property::Type::Grammar>
		colorizationReference(generatedLanguage);

	deamer::language::reference::ReverseLookup<
		::deamer::language::type::definition::object::main::TerminalColor>
		lookupTerminalColor(&colorizationReference);

	auto lexicon =
		colorizationReference
			.GetDefinition<::deamer::language::type::definition::property::Type::Lexicon>();

	auto result_varname = lookupTerminalColor.Get(lexicon.GetTerminal("VARNAME"));
	ASSERT_TRUE(result_varname.GetObjects().size() > 0);
	EXPECT_TRUE(result_varname.GetObjects().size() == 1);

	auto result_eq = lookupTerminalColor.Get(lexicon.GetTerminal("EQ"));
	ASSERT_TRUE(result_eq.GetObjects().size() > 0);
	EXPECT_TRUE(result_eq.GetObjects().size() == 1);

	auto result_semicolon = lookupTerminalColor.Get(lexicon.GetTerminal("SEMICOLON"));
	ASSERT_TRUE(result_semicolon.GetObjects().size() > 0);
	EXPECT_TRUE(result_semicolon.GetObjects().size() == 1);

	EXPECT_TRUE(result_varname.GetObject()->colorGroup->ColorId !=
				result_eq.GetObject()->colorGroup->ColorId);
	EXPECT_TRUE(result_varname.GetObject()->colorGroup->ColorId !=
				result_semicolon.GetObject()->colorGroup->ColorId);
	EXPECT_TRUE(result_eq.GetObject()->colorGroup->ColorId != 1025);
	EXPECT_TRUE(result_semicolon.GetObject()->colorGroup->ColorId != 1025);

	delete generatedLanguage;
}
