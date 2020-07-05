/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

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