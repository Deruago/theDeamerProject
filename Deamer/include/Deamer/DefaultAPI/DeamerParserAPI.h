#ifndef DEAMER_DEFAULTAPI_DEAMERPARSERAPI_H
#define DEAMER_DEFAULTAPI_DEAMERPARSERAPI_H

#include "Deamer/AstGen/AstNode.h"
#include "Deamer/AstGen/AstTree.h"
#include <string>
#include <stdio.h>

class DeamerParserAPI
{
    public:
        virtual AstNode* ParseText(std::string inputText) = 0;
        virtual AstNode* ParseFile(FILE* inputFile) = 0;
        virtual AstNode* ParseFile(std::string fileLocation) = 0;
};

#endif //DEAMER_DEFAULTAPI_DEAMERPARSERAPI_H