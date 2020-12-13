/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -June 2020 Thimo B�hmer
 * -July 2020 Thimo B�hmer
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
        void IncreaseReferenceCounterOfTokensUsedInRule(const std::vector<Token*>& tokens);

    	std::vector<Node*> Nodes;
        std::vector<Node*> IgnoreNodes;
        std::vector<Type*> Types;
        std::vector<Rule*> Rules;

        bool IsNodeInVector(const Node* node) const;
        bool IsIgnoredNodeInVector(const Node* node) const;
        bool IsTypeInVector(const Type* type) const;
    	bool IsRuleInVector(const Rule* rule) const;
    public:
        LanguageDefinition() = default;
        ~LanguageDefinition();

        Type* StartType = nullptr;
        std::string LanguageName;

        void AddNode(Node* newNode);
        void AddIgnoredNode(Node* newNode);
        void AddType(Type* newType);
        void AddRule(Rule* newRule);
    	
    	void RemoveType(Type* type);
        void RemoveRule(Rule* rule);
        void RemoveNode(Node* node);

        const std::vector<Node*>& GetNodes() const;
        const std::vector<Node*>& GetIgnoreNodes() const;
        const std::vector<Type*>& GetTypes() const;
        const std::vector<Rule*>& GetRules() const;
    };
}

#endif //DEAMER_LANGUAGEGEN_LANGUAGEDEFINION_H
