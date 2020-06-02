#include "Deamer/Deamer.h"
#include "Deamer/LanguageGen/LanguageGen.h"
#include "Deamer/LanguageGen/LanguageDefMacros.h"
#include <iostream>
//using namespace Deamer;

int main()
{
    #ifdef currentLangGen
    #undef currentLangGen
    #endif
    #define currentLangGen languageGen

    LanguageGen languageGen = LanguageGen(flex, bison);

    newNode(SEMICOLON, "[;]");
    newNode(PLUS, "[+]");
    newNode(MULT, "[*]");
    newNode(DIV, "[/]");
    newNode(MIN, "[-]");
    newType(PROG);
    newRule(PROG, SEMICOLON, PROG);

    languageGen.DeleteAllNodes();

    return 0;
}