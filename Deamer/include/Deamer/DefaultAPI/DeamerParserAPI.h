/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 * -December 2020 Thimo Bohmer
 */

#ifndef DEAMER_DEFAULTAPI_DEAMERPARSERAPI_H
#define DEAMER_DEFAULTAPI_DEAMERPARSERAPI_H

#include "Deamer/AstGen/AstNode.h"
#include <string>

namespace deamer
{
    class DeamerParserAPI
    {
    public:
        DeamerParserAPI() = default;
        virtual ~DeamerParserAPI() = default;
    	
        virtual AstNode* ParseText(std::string inputText) = 0;
        virtual AstNode* ParseFile(FILE* inputFile) = 0;
        virtual AstNode* ParseFile(std::string fileLocation) = 0;
    };
}

#endif //DEAMER_DEFAULTAPI_DEAMERPARSERAPI_H