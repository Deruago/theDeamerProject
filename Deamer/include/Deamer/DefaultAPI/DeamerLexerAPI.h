#ifndef DEAMER_DEFAULTAPI_DEAMERLEXERAPI_H
#define DEAMER_DEFAULTAPI_DEAMERLEXERAPI_H

#include "Deamer/AstGen/AstNode.h"
#include "Deamer/AstGen/AstTree.h"
#include <string>

namespace deamer
{
    class DeamerLexerAPI
    {
        public:
            DeamerLexerAPI();
            ~DeamerLexerAPI();
            virtual AstNode* LexText(std::string inputText) = 0;
            virtual AstNode* LexFile(FILE* inputFile) = 0;
            virtual AstNode* LexFile(std::string fileLocation) = 0;
    };
}

#endif //DEAMER_DEFAULTAPI_DEAMERLEXERAPI_H