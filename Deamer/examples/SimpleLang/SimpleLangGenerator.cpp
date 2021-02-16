#include "Deamer/LanguageGen/LanguageGen.h"
#include "Deamer/LanguageAnalyzer/LanguageOptimiser.h"
#include "Deamer/LanguageAnalyzer/LanguagePrinter/LanguageDefinitionPrinter.h"
#include "Deamer/LanguageGen/LanguageDefMacros.h"
#include "Deamer/AstGen/AstGen.h"
#include "Deamer/AstGen/AstNodeDataStructures/AstBuilderType.h"
#include "Deamer/ThreatAnalyzer/Printer/ThreatPrinter.h"
#include "Deamer/ThreatAnalyzer/LanguageDefinition/LanguageDefinitionThreatAnalyzer.h"
#include <iostream>
using namespace deamer;

int main()
{
    #ifdef currentLangDef
    #undef currentLangDef
    #endif
    #define currentLangDef language_definition_builder

    LanguageDefinitionBuilder language_definition_builder = LanguageDefinitionBuilder();
    language_definition_builder.SetTypeContinuation(TypeContinuation_t::vector);

    DELETENODE(ESCAPE_CHARACTERS, "[\\n\\r\\t ]+");
    IGNORENODE(LEFT_CURLY_BRACKET, "[(]");
    IGNORENODE(RIGHT_CURLY_BRACKET, "[)]");
    IGNORENODE(LEFT_BRACKET, "[{]");
    IGNORENODE(RIGHT_BRACKET, "[}]");
    IGNORENODE(EQUAL, "[=]");
    IGNORENODE(SEMICOLON, "[;]");
    IGNORENODE(FUNCTION_DECLARATION, "def");
    IGNORENODE(VARIABLE_DECLARATION, "var");
    NODE(VARNAME, "[a-zA-Z_]+[a-zA-Z_0-9]*");
    NODE(NUMBER, "[0-9]+");
    NODE(DECIMAL, "[0-9]+[\\.][0-9]+");
    NODE(STRING, "[\"][.]*[\"]");
    TYPE(prog);
    TYPE(stmts);
    GROUPEDTYPE(stmt);
    TYPE(variable_initialisation);
    TYPE(function_initialisation);
    TYPE(block);

    RULE(prog, stmts);
    RULE(stmts, stmt, stmts);
    RULE(stmts, EMPTY);
    GROUPTOKENS(stmt, variable_initialisation, function_initialisation);
    RULE(variable_initialisation, VARIABLE_DECLARATION, VARNAME, EQUAL, NUMBER, SEMICOLON);
    RULE(variable_initialisation, VARIABLE_DECLARATION, VARNAME, EQUAL, STRING, SEMICOLON);
    RULE(variable_initialisation, VARIABLE_DECLARATION, VARNAME, EQUAL, DECIMAL, SEMICOLON);
    RULE(variable_initialisation, VARIABLE_DECLARATION, VARNAME, EQUAL, VARNAME, SEMICOLON);
    RULE(function_initialisation, FUNCTION_DECLARATION, VARNAME, LEFT_CURLY_BRACKET, RIGHT_CURLY_BRACKET, block);
    RULE(block, LEFT_BRACKET, stmts, RIGHT_BRACKET);

    language_definition_builder.SetLanguageName("SimpleLang");
    auto language_definition = language_definition_builder.GetLanguageDefinition();

    auto languageGen = new LanguageGen(LexerType_t::flex, ParserType_t::bison, *language_definition);
    languageGen->DirTarget("");


    languageGen->Finish();

    auto astGen = new AstGen(*language_definition, AstBuilderType::visitor);
    astGen->CreateAstNodes();
    delete language_definition;
    return 0;
}

