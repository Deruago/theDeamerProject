#ifndef DEAMER_LEXERGEN_DLEXBUILDER_H
#define DEAMER_LEXERGEN_DLEXBUILDER_H

#include "Deamer/LexerGen/LexerBuilder.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"

namespace deamer
{
    class DlexBuilder : public LexerBuilder
    {
        public:
            DlexBuilder();
            DlexBuilder(LanguageDefinition* langDef);
            void AddNode(Node* node) override;
            bool FinishBuild() override;
            bool StartBuild() override;
    };
}

#endif //DEAMER_LEXERGEN_DLEXBUILDER_H