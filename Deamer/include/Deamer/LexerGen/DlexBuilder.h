#ifndef DEAMER_LEXERGEN_DLEXBUILDER_H
#define DEAMER_LEXERGEN_DLEXBUILDER_H

#include "Deamer/LexerGen/LexerBuilder.h"

class DlexBuilder : public LexerBuilder
{
    public:
        DlexBuilder();
        void AddNode(Node* node) override;
        bool FinishBuild() override;
        bool StartBuild() override;
};

#endif //DEAMER_LEXERGEN_DLEXBUILDER_H