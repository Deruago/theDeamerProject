/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -June 2020 Thimo B�hmer
 * -July 2020 Thimo B�hmer
 */

#ifndef DEAMER_LEXERGEN_DLEXBUILDER_DLEXBUILDER_H
#define DEAMER_LEXERGEN_DLEXBUILDER_DLEXBUILDER_H

#include "Deamer/LexerGen/LexerBuilder.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"

namespace deamer
{
    class DlexBuilder : public LexerBuilder
    {
    public:
        DlexBuilder(const LanguageDefinition* langDef);
        void AddNode(Node* node) override;
        void AddIgnoreNode(Node* node) override;
        void AddDeleteNode(Node* node) override;
        bool FinishBuild() override;
        bool StartBuild() override;
    };
}

#endif //DEAMER_LEXERGEN_DLEXBUILDER_DLEXBUILDER_H
