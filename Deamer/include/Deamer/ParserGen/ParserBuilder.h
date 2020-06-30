#ifndef DEAMER_PARSERGEN_PARSERBUILDER_H
#define DEAMER_PARSERGEN_PARSERBUILDER_H

#include "Deamer/Types/Builder.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include "Deamer/LanguageGen/Node.h"
#include "Deamer/LanguageGen/Type.h"
#include "Deamer/LanguageGen/Rule.h"
#include <string>

class ParserBuilder : public Builder
{
    protected:
        ParserType_t parserType;
        ParserBuilder();
        ParserBuilder(std::string fileName);
    public:
        LanguageDefinition* langDef;
        virtual void AddNode(Node* node) = 0; // Writes the node to the file
        virtual void AddType(Type* type) = 0; // Writes the type to the file
        virtual void AddRule(Rule* rule) = 0; // Writes the rule to the file, Note: Type already includes rules so this could be unneccessary
        virtual bool StartBuild() = 0;
        virtual bool FinishBuild() = 0;
        ParserType_t GetParserTarget();
};

#endif //DEAMER_PARSERGEN_PARSERBUILDER_H