#include "../../Integration/Language/DefineSimpleLanguage.h"
#include <Deamer/Language/Reference/LDO.h>
#include <gtest/gtest.h>

using Type = deamer::language::type::definition::property::Type;
using namespace deamer::language::reference;

class TestLDO : public testing::Test
{
public:
	using ReferenceType = PropertyDefinition<Type::Lexicon, Type::Grammar>;

protected:
	LanguageDefinition languageDefinition;
	deamer::language::type::definition::Language* language;

	TestLDO()
	{
		language = languageDefinition.GenerateLanguage();
	}

	virtual ~TestLDO()
	{
		delete language;
	}
};

TEST_F(TestLDO, CorrectlyInitialisesReference)
{
	ReferenceType reference(language);
	const auto* expected_varname = reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME");

	LDO<deamer::language::type::definition::object::main::Terminal> terminalReference(
		expected_varname);
	const auto* actual_varname = terminalReference.Get();

	EXPECT_EQ(expected_varname, actual_varname);
}

TEST_F(TestLDO, CorrectlyInitialisesConstantReference)
{
	ReferenceType reference(language);
	const auto* expected_varname = reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME");

	const LDO<deamer::language::type::definition::object::main::Terminal> terminalReference(
		expected_varname);
	const auto* actual_varname = terminalReference.Get();

	EXPECT_EQ(expected_varname, actual_varname);
}

TEST_F(TestLDO, CorrectlyCopiesLdoReference)
{
	ReferenceType reference(language);
	const auto* expected_varname = reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME");

	const LDO<deamer::language::type::definition::object::main::Terminal>
		terminalReference_original(expected_varname);

	const LDO<deamer::language::type::definition::object::main::Terminal> terminalReference_clone(
		terminalReference_original);

	const auto* actual_varname = terminalReference_clone.Get();

	EXPECT_EQ(expected_varname, actual_varname);
}

TEST_F(TestLDO, CorrectlyMovesLdoReference)
{
	ReferenceType reference(language);
	const auto* expected_varname = reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME");

	LDO<deamer::language::type::definition::object::main::Terminal> terminalReference_original(
		expected_varname);

	const LDO<deamer::language::type::definition::object::main::Terminal> terminalReference_clone(
		std::move(terminalReference_original));

	const auto* actual_varname = terminalReference_clone.Get();

	EXPECT_EQ(expected_varname, actual_varname);
}

TEST_F(TestLDO, CorrectlyAllocateOnHeap)
{
	ReferenceType reference(language);
	const auto* expected_varname = reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME");

	const auto* terminalReference_original =
		new LDO<deamer::language::type::definition::object::main::Terminal>(expected_varname);

	const auto* actual_varname = terminalReference_original->Get();

	EXPECT_EQ(expected_varname, actual_varname);

	delete terminalReference_original;
}

TEST_F(TestLDO, GiveNullptrTerminal_ShouldNotThrow)
{
	const deamer::language::type::definition::object::main::Terminal* const nullptr_terminal =
		nullptr;

	LDO<deamer::language::type::definition::object::main::Terminal> actual(nullptr_terminal);
}

TEST_F(TestLDO, GiveNullptrTerminal_ButEnableCheckOnCtor_ShouldThrow)
{
	using LDO_reference = LDO<deamer::language::type::definition::object::main::Terminal, true>;

	const deamer::language::type::definition::object::main::Terminal* const nullptr_terminal =
		nullptr;
	EXPECT_ANY_THROW(LDO_reference actual(nullptr_terminal));
}

TEST_F(TestLDO, VerifyIfUnknownPointerIsInLanguage_ShouldReturnFalse)
{
	ReferenceType reference(language);
	const auto* expected_varname = reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME");

	const auto terminalReference_original =
		LDO<deamer::language::type::definition::object::main::Terminal>(expected_varname);

	EXPECT_TRUE(terminalReference_original.Verify(language));
}

TEST_F(TestLDO, VerifyIfKnownPointerIsInLanguage_ShouldReturnTrue)
{
	ReferenceType reference(language);
	const auto* unknown_pointer =
		static_cast<LDO<deamer::language::type::definition::object::main::Terminal>::type>(
			nullptr) +
		1;

	const auto terminalReference_original =
		LDO<deamer::language::type::definition::object::main::Terminal>(unknown_pointer);

	EXPECT_FALSE(terminalReference_original.Verify(language));
}

TEST_F(TestLDO, VerifyViaReferenceIfUnknownPointerIsInLanguage_ShouldReturnFalse)
{
	ReferenceType reference(language);
	const auto* expected_varname = reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME");

	const auto terminalReference_original =
		LDO<deamer::language::type::definition::object::main::Terminal>(expected_varname);

	EXPECT_TRUE(terminalReference_original.Verify(&reference));
}

TEST_F(TestLDO, VerifyViaReferenceIfKnownPointerIsInLanguage_ShouldReturnTrue)
{
	ReferenceType reference(language);
	const auto* unknown_pointer =
		static_cast<LDO<deamer::language::type::definition::object::main::Terminal>::type>(
			nullptr) +
		1;

	const auto terminalReference_original =
		LDO<deamer::language::type::definition::object::main::Terminal>(unknown_pointer);

	EXPECT_FALSE(terminalReference_original.Verify(&reference));
}

TEST_F(TestLDO, VerifyViaBaseReferenceIfUnknownPointerIsInLanguage_ShouldReturnFalse)
{
	const PropertyDefinitionBase* const reference_base = new ReferenceType(language);
	ReferenceType reference(language);
	const auto* expected_varname = reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME");

	const auto terminalReference_original =
		LDO<deamer::language::type::definition::object::main::Terminal>(expected_varname);

	EXPECT_TRUE(terminalReference_original.Verify(reference_base));

	delete reference_base;
}

TEST_F(TestLDO, VerifyViaBaseReferenceIfKnownPointerIsInLanguage_ShouldReturnTrue)
{
	const PropertyDefinitionBase* const reference_base = new ReferenceType(language);
	const auto* unknown_pointer =
		static_cast<LDO<deamer::language::type::definition::object::main::Terminal>::type>(
			nullptr) +
		1;

	const auto terminalReference_original =
		LDO<deamer::language::type::definition::object::main::Terminal>(unknown_pointer);

	EXPECT_FALSE(terminalReference_original.Verify(reference_base));

	delete reference_base;
}

TEST_F(TestLDO, CheckIfBaseIsCorrespondsWithGivenType_CorrespondingType_ShouldReturnTrue)
{
	ReferenceType reference(language);
	const auto* expected_varname = reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME");

	const auto terminalReference_original =
		LDO<deamer::language::type::definition::object::main::Terminal>(expected_varname);

	EXPECT_TRUE(terminalReference_original.IsBaseTypeValid());
}

TEST_F(TestLDO, CheckIfBaseIsCorrespondsWithGivenType_NonCorrespondingType_ShouldReturnFalse)
{
	ReferenceType reference(language);
	const auto* noncorresponding_type =
		reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");

	const auto terminalReference_original =
		LDO<deamer::language::type::definition::object::main::Terminal>(noncorresponding_type);

	EXPECT_FALSE(terminalReference_original.IsBaseTypeValid());
}

TEST_F(TestLDO, CheckInCtorWithGivenType_CorrespondingType_ShouldnotThrow)
{
	ReferenceType reference(language);
	const auto* expected_varname = reference.GetDefinition<Type::Lexicon>().GetTerminal("VARNAME");

	const auto terminalReference_original =
		LDO<deamer::language::type::definition::object::main::Terminal, true>(expected_varname);
}

TEST_F(TestLDO, CheckInCtorCorrespondsWithGivenType_NonCorrespondingType_ShouldThrow)
{
	using LDO_reference = LDO<deamer::language::type::definition::object::main::Terminal, true>;
	ReferenceType reference(language);
	const auto* noncorresponding_type =
		reference.GetDefinition<Type::Grammar>().GetNonTerminal("stmts");

	EXPECT_ANY_THROW(const auto terminalReference_original = LDO_reference(noncorresponding_type););
}
