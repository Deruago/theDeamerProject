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

#include "Deamer/LanguageGen/Node.h"
#include "Deamer/LanguageGen/Type.h"
#include "Deamer/LanguageGen/Token.h"
#include "Deamer/LanguageGen/Rule.h"
#include <string>
#include <vector>

namespace deamer
{
    class LanguageDefinition
    {
    private:
        void IncreaseReferenceCounterOfTokensUsedInRule(std::vector<Token*> tokens);
    protected:
        std::string LanguageName;
    public:
        LanguageDefinition(std::string languageName);
        ~LanguageDefinition() = default;

    	std::vector<Node*> Nodes;
        std::vector<Node*> IgnoreNodes;
        std::vector<Type*> Types;
        std::vector<Rule*> Rules;

    	Node* CreateNode(const std::string& nodeName, const std::string& regex, const bool createAst = true); // Used to create a Node Class
        Node* IgnoreNode(const std::string& nodeName, const std::string& regex);
        Type* CreateType(const std::string& typeName, const bool createAst = true); // Used to create a Type Class
        Type* CreateGroupedType(const std::string& typeName, const bool createAst = true); // Used to create a Type Class
        Rule* CreateRule(Type* type, std::vector<Token*> tokens); // Used to create a Rule Class
        deamer::Rule* CreateRuleWithOneToken(Type* type, Token* token);
        Type* GroupTokens(const std::string& typeName, std::vector<Token*>& tokens); // Used to manually subtype a group of tokens under a single type

    	void RemoveType(Type* type);
        void RemoveRule(Rule* rule);
        void RemoveNode(Node* node);
    
    	void  DeleteAllNodes();
        void  DeleteAllTypes();
        void  DeleteAllRules();
        void  PrintLanguageConfig();
        void  PrintNodes();
        void  PrintTypes();
        void  PrintRules();
        std::string GetLanguageName();
    };
}

#endif //DEAMER_LANGUAGEGEN_LANGUAGEDEFINION_H
