#ifndef DEAMER_LEXERGEN_FLEXBUILDER_H
#define DEAMER_LEXERGEN_FLEXBUILDER_H

#include "Deamer/LexerGen/LexerBuilder.h"

class FlexBuilder : public LexerBuilder
{
    public:
        FlexBuilder();
        void AddNode(Node* node) override;
        bool FinishBuild()  override;
};

#endif //DEAMER_LEXERGEN_FLEXBUILDER_H