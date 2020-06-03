#ifndef DEAMER_LANGUAGEGEN_LANGUAGEDEFINION_H
#define DEAMER_LANGUAGEGEN_LANGUAGEDEFINION_H

/*
This class is used to define a language. This definition can be used to generate specific code
or just display certain trees/diagrams about the language.
*/

#include <vector>
#include "Deamer/LanguageGen/Node.h"
#include "Deamer/LanguageGen/Type.h"
#include "Deamer/LanguageGen/Token.h"
#include "Deamer/LanguageGen/Rule.h"

class LanguageDefinition
{
    public:
        std::vector<Node*> Nodes;
        std::vector<Type*> Types;
        std::vector<Rule*> Rules;
        Node* CreateNode(const std::string nodeName, const std::string regex); // Used to create a Node Class
        Type* CreateType(const std::string typeName); // Used to create a Type Class
        Rule* CreateRule(Type* type, const std::vector<Token*> tokens); // Used to create a Rule Class
        void  DeleteAllNodes();
        void  DeleteAllTypes();
        void  DeleteAllRules();
        void  PrintLanguageConfig();
        void  PrintNodes();
        void  PrintTypes();
        void  PrintRules();
};
#endif //DEAMER_LANGUAGEGEN_LANGUAGEDEFINION_H