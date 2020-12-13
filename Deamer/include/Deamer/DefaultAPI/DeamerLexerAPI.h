/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 * -December 2020 Thimo Bohmer
 */

#ifndef DEAMER_DEFAULTAPI_DEAMERLEXERAPI_H
#define DEAMER_DEFAULTAPI_DEAMERLEXERAPI_H

#include "Deamer/AstGen/AstNode.h"
#include <string>

namespace deamer
{
    class DeamerLexerAPI
    {
    public:
        DeamerLexerAPI() = default;
        virtual ~DeamerLexerAPI() = default;
    	
        virtual AstNode* LexText(std::string inputText) = 0;
        virtual AstNode* LexFile(FILE* inputFile) = 0;
        virtual AstNode* LexFile(std::string fileLocation) = 0;
    };
}

#endif //DEAMER_DEFAULTAPI_DEAMERLEXERAPI_H