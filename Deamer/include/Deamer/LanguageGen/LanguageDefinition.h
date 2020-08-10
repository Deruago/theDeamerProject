/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_LANGUAGEGEN_LANGUAGEDEFINION_H
#define DEAMER_LANGUAGEGEN_LANGUAGEDEFINION_H

/*
This class is used to define a language. This definition can be used to generate specific code
or just display certain trees/diagrams about the language.
*/

#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Node.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"
#include <string>
#include <vector>

namespace deamer
{
    class LanguageDefinition
    {
    private:
        void IncreaseReferenceCounterOfTokensUsedInRule(std::vector<Token*> tokens);
    public:
        LanguageDefinition() = default;
        ~LanguageDefinition() = default;

        Type* StartType = nullptr;
        std::string LanguageName;
    	std::vector<Node*> Nodes;
        std::vector<Node*> IgnoreNodes;
        std::vector<Type*> Types;
        std::vector<Rule*> Rules;

    	void RemoveType(Type* type);
        void RemoveRule(Rule* rule);
        void RemoveNode(Node* node);
    };
}

#endif //DEAMER_LANGUAGEGEN_LANGUAGEDEFINION_H
