#ifndef DEAMER_LEXERGEN_LEXERBUILDER_H
#define DEAMER_LEXERGEN_LEXERBUILDER_H

#include "Deamer/Types/Builder.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include "Deamer/LanguageGen/Node.h"
#include <string>

class LexerBuilder : public Builder
{
    protected:
        LexerType_t LexerType;
        LexerBuilder();
        LexerBuilder(std::string fileName);
    public:
        LanguageDefinition* langDef;
        virtual void AddNode(Node* node) = 0; // Writes the node to the file
        virtual bool StartBuild() = 0;
        virtual bool FinishBuild() = 0;
        LexerType_t GetLexerTarget();
};

#endif //DEAMER_LEXERGEN_LEXERBUILDER_H