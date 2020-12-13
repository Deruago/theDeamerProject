/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -June 2020 Thimo B�hmer
 * -July 2020 Thimo B�hmer
 */

#ifndef DEAMER_PARSERGEN_PARSERBUILDER_H
#define DEAMER_PARSERGEN_PARSERBUILDER_H

#include "Deamer/Types/Builder.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include <string>

namespace deamer
{
    class Node;
    class Type;
    class Rule;
    class LanguageDefinition;
	
    class ParserBuilder : public Builder
    {
    protected:
        ParserType_t parserType;
        const LanguageDefinition* langDef;

    	ParserBuilder(const LanguageDefinition* languageDefinition);
    public:
        virtual ~ParserBuilder() = default;


    	virtual void AddNode(Node* node) = 0; // Writes the node to the file
        virtual void AddType(Type* type) = 0; // Writes the type to the file
        virtual void AddRule(Rule* rule) = 0; // Writes the rule to the file, Note: Type already includes rules so this could be unneccessary
        virtual bool StartBuild() = 0;
        virtual bool FinishBuild() = 0;
    };
}

#endif //DEAMER_PARSERGEN_PARSERBUILDER_H