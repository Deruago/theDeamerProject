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
    
    	void  DeleteAllNodes();
        void  DeleteAllTypes();
        void  DeleteAllRules();
    	
        void  PrintLanguageConfig();
        void  PrintNodes();
        void  PrintTypes();
        void  PrintRules();

        bool TypeIsStartType(Type* type);
    };
}

#endif //DEAMER_LANGUAGEGEN_LANGUAGEDEFINION_H
