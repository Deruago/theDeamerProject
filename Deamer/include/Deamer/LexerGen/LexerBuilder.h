#ifndef DEAMER_LEXERGEN_LEXERBUILDER_H
#define DEAMER_LEXERGEN_LEXERBUILDER_H

#include <vector>
#include "Deamer/LanguageGen/Node.h"

class LexerBuilder
{
    LexerType_t lexerType;
    std::vector<Node*> Nodes;
    public:
        LexerBuilder();
        LexerBuilder(LexerType_t lexerTarget);
};

#endif //DEAMER_LEXERGEN_LEXERBUILDER_H