/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -June 2020 Thimo B�hmer
 * -July 2020 Thimo B�hmer
 */

#ifndef DEAMER_LEXERGEN_LEXERBUILDER_H
#define DEAMER_LEXERGEN_LEXERBUILDER_H

#include "Deamer/Types/Builder.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include "Deamer/LanguageGen/Node.h"
#include <string>

namespace deamer
{
    class LexerBuilder : public Builder
    {
        protected:
            LexerType_t LexerType;
            LexerBuilder();
            LexerBuilder(std::string fileName);
        public:
            LanguageDefinition* langDef;
            virtual void AddNode(Node* node) = 0; // Writes the node to the file
            virtual void AddIgnoreNode(Node* node) = 0;
            virtual bool StartBuild() = 0;
            virtual bool FinishBuild() = 0;
            LexerType_t GetLexerTarget();
    };
}

#endif //DEAMER_LEXERGEN_LEXERBUILDER_H
