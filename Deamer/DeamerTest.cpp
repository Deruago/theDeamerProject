#include "Deamer/Deamer.h"
#include "Deamer/LanguageGen/LanguageGen.h"
#include "Deamer/LanguageGen/LanguageDefMacros.h"
#include "Deamer/AstGen/AstGen.h"
#include <iostream>
//using namespace Deamer;

int main()
{
    #ifdef currentLangDef
    #undef currentLangDef
    #endif
    #define currentLangDef languageDef

    LanguageDefinition languageDef = LanguageDefinition();
    LanguageGen* languageGen = new LanguageGen(flex, bison, &languageDef);

    newNode(SEMICOLON, "[;]");
    newNode(PLUS, "[+]");
    newNode(MULT, "[*]");
    newNode(DIV, "[/]");
    newNode(MIN, "[-]");
    newNode(NUMBER, "[0-9]+");
    newNode(DECIMAL, "[0-9]+[\\.][0-9]+")
    newNode(COMPARE, "[=][=]");
    newNode(NOTCOMP, "[!][=]");
    newNode(EQUAL, "[=]");
    newNode(STRING_TYPE, "[\"][^\"]*[\"]")
    newNode(STRING, "[s][t][r][i][n][g]");
    newNode(CHAR, "[c][h][a][r]");
    newNode(INT, "[i][n][t]");
    newNode(DOUBLE, "[d][o][u][b][l][e]");
    newNode(FLOAT, "[f][l][o][a][t]");
    newNode(VARNAME, "[a-zA-Z]+[a-zA-Z_0-9]*")

    newType(DATATYPE);
    newRule(DATATYPE, STRING);
    newRule(DATATYPE, CHAR);
    newRule(DATATYPE, INT);
    newRule(DATATYPE, DOUBLE);
    newRule(DATATYPE, FLOAT);

    newType(COND);
    newRule(COND, PLUS);
    newRule(COND, MIN);
    newRule(COND, MULT);
    newRule(COND, DIV);



    newType(EXPR);
    newRule(EXPR, NUMBER);
    newRule(EXPR, DECIMAL);
    newRule(EXPR, STRING_TYPE);

    newType(EXPRS);
    newRule(EXPRS, EXPR, COND, EXPRS);
    newRule(EXPRS, EXPR);

    newType(VAR_INIT);
    newRule(VAR_INIT, DATATYPE, VARNAME, EQUAL, EXPRS);

    newType(VAR_EXPR);
    newRule(VAR_EXPR, VAR_INIT);
    // newRule(VAR_EXPR, VAR_DECL);
    // newRule(VAR_EXPR, VAR_ASSI);

    newRule(EXPR, VAR_EXPR);

    newType(STMT);
    newRule(STMT, EXPR);

    newType(STMTS);
    newRule(STMTS, EMPTY_RULE);
    newRule(STMTS, STMT, SEMICOLON, STMTS);
    
    newType(PROG);
    newRule(PROG, STMTS);

    languageGen->GenerateLexer();
    
    languageGen->GenerateParser();

    AstGen* astGen = new AstGen();
    astGen->CreateAstNodes(&languageDef);
    
    return 0;
}