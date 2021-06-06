#include "Deamer/Language/Type/Definition/Object/Main/Threat/Check/Multi/Deamer/Lexicon/UnusedTerminal.h"
#include "LanguageDefinitionUnusedTerminals.h"
#include "LanguageDefinitionUsedTerminals.h"
#include <gtest/gtest.h>

using namespace ::deamer::language::type::definition::object::main::threat::deamer::lexicon;
using namespace ::deamer::language::type::definition::object::main::threat;
using namespace ::deamer::test::language::threat::deamer::unusedterminal;

class TestUnusedTerminal : public testing::Test
{
protected:
	TestUnusedTerminal() = default;
	virtual ~TestUnusedTerminal() = default;

protected:
	check::deamer::lexicon::UnusedTerminal unusedTerminalCheck =
		check::deamer::lexicon::UnusedTerminal();
};

TEST_F(TestUnusedTerminal, LanguageWithUnusedTerminals_ShouldReturnCorrectThreats)
{
	LanguageDefinitionUnusedTerminals language;
	auto* generatedLanguage = language.GenerateLanguage();

	auto threats = unusedTerminalCheck.Analyze(generatedLanguage);

	auto* threat_VARNAME = new UnusedTerminal(language.VARNAME.Pointer());
	auto* threat_STRING = new UnusedTerminal(language.STRING.Pointer());
	auto* threat_ESCAPE_CHARS = new UnusedTerminal(language.ESCAPE_CHARS.Pointer());

	ASSERT_EQ(threats.size(), 3);

	ASSERT_NO_THROW(dynamic_cast<UnusedTerminal*>(threats[0]));
	ASSERT_NO_THROW(dynamic_cast<UnusedTerminal*>(threats[1]));
	ASSERT_NO_THROW(dynamic_cast<UnusedTerminal*>(threats[2]));

	EXPECT_EQ(*dynamic_cast<UnusedTerminal*>(threats[0]), *threat_VARNAME);
	EXPECT_EQ(*dynamic_cast<UnusedTerminal*>(threats[1]), *threat_STRING);
	EXPECT_EQ(*dynamic_cast<UnusedTerminal*>(threats[2]), *threat_ESCAPE_CHARS);

	delete generatedLanguage;

	delete threat_VARNAME;
	delete threat_STRING;
	delete threat_ESCAPE_CHARS;

	for (auto* const threat : threats)
	{
		delete threat;
	}
}

TEST_F(TestUnusedTerminal, LanguageWithoutUnusedTerminals_ShouldReturnNoThreats)
{
	LanguageDefinitionUsedTerminals language;
	auto* generatedLanguage = language.GenerateLanguage();

	const auto threats = unusedTerminalCheck.Analyze(generatedLanguage);

	EXPECT_EQ(threats.size(), 0);

	delete generatedLanguage;
}
