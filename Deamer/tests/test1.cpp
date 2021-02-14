#include <gtest/gtest.h> 

#include "Deamer/LanguageGen/LanguageGen.h"
#include "Deamer/LanguageAnalyzer/LanguageOptimiser.h"
#include "Deamer/LanguageAnalyzer/LanguagePrinter/LanguageDefinitionPrinter.h"
#include "Deamer/LanguageGen/LanguageDefMacros.h"
#include "Deamer/AstGen/AstGen.h"
#include "Deamer/AstGen/AstNodeDataStructures/AstBuilderType.h"

using namespace deamer;

TEST(test1, test1_true_is_true)
{
	#ifdef currentLangDef
    #undef currentLangDef
    #endif
    #define currentLangDef language_definition_builder

    LanguageDefinitionBuilder language_definition_builder = LanguageDefinitionBuilder();
    language_definition_builder.SetTypeContinuation(TypeContinuation_t::vector);
    DELETENODE(NEWLINE, "[\\n]");
	
	EXPECT_TRUE(true);
}