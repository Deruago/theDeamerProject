#include "../../../../Integration/Language/DefineSimpleLanguage.h"
#include "Deamer/Language/Analyzer/Analyzer.h"
#include "Deamer/Language/Analyzer/Main/Grammar/NonTerminal.h"
#include "Deamer/Language/Reference/ReverseLookup.h"
#include "Language/TerminalNeighbors.h"
#include <Deamer/Language/Reference/PropertyDefinition.h>
#include <gtest/gtest.h>

using Type = deamer::language::type::definition::property::Type;
using namespace deamer::language::reference;
using namespace deamer::test::language::analyzer::grammar::language::terminal;

class TestTerminal : public testing::Test
{
public:
	using ReferenceType = PropertyDefinition<Type::Lexicon, Type::Grammar>;

protected:
	LanguageDefinition languageDefinition;
	TerminalNeighbors terminalNeighborsLanguageDefinition;

	deamer::language::type::definition::Language* language;
	deamer::language::type::definition::Language* terminalNeighbors;

	TestTerminal()
	{
		language = languageDefinition.GenerateLanguage();
		terminalNeighbors = terminalNeighborsLanguageDefinition.GenerateLanguage();
	}

	virtual ~TestTerminal()
	{
		delete language;
		delete terminalNeighbors;
	}
};

// clang-format off
#define EXPECT_TERMINAL_IN_SET(expectedBase, bases) { const bool found = bases.find(const_cast<::deamer::language::type::definition::object::Base*>( static_cast<const ::deamer::language::type::definition::object::Base*>(expectedBase))) != bases.end(); EXPECT_TRUE(found); }

#define EXPECT_TERMINAL_NOT_IN_SET(expectedBase, bases) { const bool found = bases.find(const_cast<::deamer::language::type::definition::object::Base*>( static_cast<const ::deamer::language::type::definition::object::Base*>(expectedBase))) != bases.end(); EXPECT_FALSE(found); }

#define EXPECT_TOKEN_IN_SET(expectedBase, bases) { const bool found = bases.find(const_cast<::deamer::language::type::definition::object::Base*>( static_cast<const ::deamer::language::type::definition::object::Base*>(expectedBase))) != bases.end(); EXPECT_TRUE(found); }

#define EXPECT_TOKEN_NOT_IN_SET(expectedBase, bases) { const bool found = bases.find(const_cast<::deamer::language::type::definition::object::Base*>( static_cast<const ::deamer::language::type::definition::object::Base*>(expectedBase))) != bases.end(); EXPECT_FALSE(found); }
// clang-format on

TEST_F(TestTerminal, GetNeighborsOfSingleTerminal_ShouldCorrectlyGiveNeighbors)
{
	const ReferenceType reference(terminalNeighbors);

	const auto* terminal = reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::Terminal>
		analyzer(&reference, terminal);

	std::set<LDO<::deamer::language::type::definition::object::main::Terminal>> neighborTerminals;
	analyzer->GetAllPossibleNeighbouringTerminals(neighborTerminals);

	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("EQUAL"),
						   neighborTerminals)
	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("INTEGER_TYPE"),
						   neighborTerminals)
	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("DOUBLE_TYPE"),
						   neighborTerminals)
	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("FLOAT_TYPE"),
						   neighborTerminals)

	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
							   neighborTerminals)
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("NUMBER"),
							   neighborTerminals)
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME"),
							   neighborTerminals)
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS"),
							   neighborTerminals)
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("SPACE"),
							   neighborTerminals)
}

TEST_F(TestTerminal, GetNeighborsOfDeletedTerminals_ShouldGiveNoNeighborsAsTheTerminalIsDeleted)
{
	{
		const ReferenceType reference(terminalNeighbors);

		const auto* terminal = reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS");

		const deamer::language::analyzer::Analyzer<
			deamer::language::type::definition::object::main::Terminal>
			analyzer(&reference, terminal);

		std::set<LDO<::deamer::language::type::definition::object::main::Terminal>>
			neighborTerminals;
		analyzer->GetAllPossibleNeighbouringTerminals(neighborTerminals);

		EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME"),
								   neighborTerminals)
		EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("EQUAL"),
								   neighborTerminals)
		EXPECT_TERMINAL_NOT_IN_SET(
			reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS"), neighborTerminals)
		EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("SPACE"),
								   neighborTerminals)
		EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
								   neighborTerminals)
		EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("NUMBER"),
								   neighborTerminals)
		EXPECT_TERMINAL_NOT_IN_SET(
			reference.GetDefinition<Type::Lexicon>().GetTerminal("INTEGER_TYPE"), neighborTerminals)
		EXPECT_TERMINAL_NOT_IN_SET(
			reference.GetDefinition<Type::Lexicon>().GetTerminal("DOUBLE_TYPE"), neighborTerminals)
		EXPECT_TERMINAL_NOT_IN_SET(
			reference.GetDefinition<Type::Lexicon>().GetTerminal("FLOAT_TYPE"), neighborTerminals)
	}

	{
		const ReferenceType reference(terminalNeighbors);

		const auto* terminal = reference.GetDefinition<Type::Lexicon>().GetTerminal("SPACES");

		const deamer::language::analyzer::Analyzer<
			deamer::language::type::definition::object::main::Terminal>
			analyzer(&reference, terminal);

		std::set<LDO<::deamer::language::type::definition::object::main::Terminal>>
			neighborTerminals;
		analyzer->GetAllPossibleNeighbouringTerminals(neighborTerminals);

		EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME"),
								   neighborTerminals)
		EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("EQUAL"),
								   neighborTerminals)
		EXPECT_TERMINAL_NOT_IN_SET(
			reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS"), neighborTerminals)
		EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("SPACE"),
								   neighborTerminals)
		EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
								   neighborTerminals)
		EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("NUMBER"),
								   neighborTerminals)
		EXPECT_TERMINAL_NOT_IN_SET(
			reference.GetDefinition<Type::Lexicon>().GetTerminal("INTEGER_TYPE"), neighborTerminals)
		EXPECT_TERMINAL_NOT_IN_SET(
			reference.GetDefinition<Type::Lexicon>().GetTerminal("DOUBLE_TYPE"), neighborTerminals)
		EXPECT_TERMINAL_NOT_IN_SET(
			reference.GetDefinition<Type::Lexicon>().GetTerminal("FLOAT_TYPE"), neighborTerminals)
	}
}

TEST_F(TestTerminal,
	   GetNeigborsOfTerminal_TerminalIsntConnectedWithValueTerminals_ShouldCorrectlyGiveNeighbors)
{
	const ReferenceType reference(terminalNeighbors);

	const auto* terminal = reference.GetDefinition<Type::Lexicon>().GetTerminal("NUMBER");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::Terminal>
		analyzer(&reference, terminal);

	std::set<LDO<::deamer::language::type::definition::object::main::Terminal>> neighborTerminals;
	analyzer->GetAllPossibleNeighbouringTerminals(neighborTerminals);

	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("EQUAL"),
						   neighborTerminals)
	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("INTEGER_TYPE"),
						   neighborTerminals)
	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("DOUBLE_TYPE"),
						   neighborTerminals)
	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("FLOAT_TYPE"),
						   neighborTerminals)

	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME"),
							   neighborTerminals)
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
							   neighborTerminals)
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("NUMBER"),
							   neighborTerminals)
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS"),
							   neighborTerminals)
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("SPACE"),
							   neighborTerminals)
}

TEST_F(TestTerminal,
	   GetNeigborsOfTerminal_TerminalIsntConnectedWithTypeTerminals_ShouldCorrectlyGiveNeighbors)
{
	const ReferenceType reference(terminalNeighbors);

	const auto* terminal = reference.GetDefinition<Type::Lexicon>().GetTerminal("INTEGER_TYPE");

	const deamer::language::analyzer::Analyzer<
		deamer::language::type::definition::object::main::Terminal>
		analyzer(&reference, terminal);

	std::set<LDO<::deamer::language::type::definition::object::main::Terminal>> neighborTerminals;
	analyzer->GetAllPossibleNeighbouringTerminals(neighborTerminals);

	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME"),
						   neighborTerminals)
	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("STRING"),
						   neighborTerminals)
	EXPECT_TERMINAL_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("NUMBER"),
						   neighborTerminals)

	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("EQUAL"),
							   neighborTerminals)
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("INTEGER_TYPE"),
							   neighborTerminals)
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("DOUBLE_TYPE"),
							   neighborTerminals)
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("FLOAT_TYPE"),
							   neighborTerminals)
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("ESCAPE_CHARS"),
							   neighborTerminals)
	EXPECT_TERMINAL_NOT_IN_SET(reference.GetDefinition<Type::Lexicon>().GetTerminal("SPACE"),
							   neighborTerminals)
}
