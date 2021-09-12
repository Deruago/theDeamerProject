#include "Deamer/Language/Type/Definition/Object/Main/Threat/Check/Multi/Deamer/Lexicon/UnusedTerminal.h"
#include "FaultyLanguageDefinition.h"
#include <gtest/gtest.h>

using namespace ::deamer::language::type::definition::object::main::threat::deamer::lexicon;
using namespace ::deamer::language::type::definition::object::main::threat;
using namespace ::deamer::test::language::threat::standard::generator;

class TestThreatStandardGeneratorLPD : public testing::Test
{
protected:
	TestThreatStandardGeneratorLPD() = default;
	virtual ~TestThreatStandardGeneratorLPD() = default;

protected:
};

TEST_F(TestThreatStandardGeneratorLPD,
	   LanguageWithThreatsShouldThrowThreats_CheckIfThreatsAreThrown)
{
	FaultyLanguageDefinition language;
	auto* generatedLanguage = language.GenerateLanguage();

	const ::deamer::language::reference::PropertyDefinition<
		::deamer::language::type::definition::property::Type::Threat>
		threatReference(generatedLanguage);
	const auto& threatLPD =
		threatReference
			.GetDefinition<::deamer::language::type::definition::property::Type::Threat>();

	auto* threat_VARNAME = new UnusedTerminal(language.VARNAME.Pointer());
	auto* threat_STRING = new UnusedTerminal(language.STRING.Pointer());
	auto* threat_ESCAPE_CHARS = new UnusedTerminal(language.ESCAPE_CHARS.Pointer());

	ASSERT_GE(threatLPD.Threats.size(), 3);

	const auto unusedTerminals = threatLPD.GetAllThreatsOfTypeAndAnalyzer(
		analyzer::Type::Deamer_Lexicon, Type::UnusedTerminal);

	EXPECT_EQ(unusedTerminals.size(), 3);
	EXPECT_TRUE(threatLPD.IsThreatRan(analyzer::Type::Deamer_Lexicon, Type::UnusedTerminal));

	for (const auto* unusedTerminalThreat : unusedTerminals)
	{
		if (*dynamic_cast<const UnusedTerminal*>(unusedTerminalThreat) == *threat_VARNAME)
		{
		}
		else if (*dynamic_cast<const UnusedTerminal*>(unusedTerminalThreat) == *threat_STRING)
		{
		}
		else if (*dynamic_cast<const UnusedTerminal*>(unusedTerminalThreat) == *threat_ESCAPE_CHARS)
		{
		}
		else
		{
			EXPECT_TRUE(false);
		}
	}

	auto* deletedTerminalThreat = new DeletedTerminalReferencedInGrammar(language.SPACES.Pointer());

	const auto deletedTerminalsReferenced = threatLPD.GetAllThreatsOfTypeAndAnalyzer(
		analyzer::Type::Deamer_Lexicon, Type::DeletedTerminalReferencedInGrammar);

	EXPECT_EQ(deletedTerminalsReferenced.size(), 1);
	EXPECT_TRUE(threatLPD.IsThreatRan(analyzer::Type::Deamer_Lexicon,
									  Type::DeletedTerminalReferencedInGrammar));

	for (const auto* deletedTerminal : deletedTerminalsReferenced)
	{
		if (*dynamic_cast<const DeletedTerminalReferencedInGrammar*>(deletedTerminal) ==
			*deletedTerminalThreat)
		{
		}
		else
		{
			EXPECT_TRUE(false);
		}
	}

	delete generatedLanguage;

	delete threat_VARNAME;
	delete threat_STRING;
	delete threat_ESCAPE_CHARS;

	delete deletedTerminalThreat;
}
