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
        protected:
            std::string LanguageName;
        public:
            LanguageDefinition(std::string languageName);
            ~LanguageDefinition() = default;
            std::vector<Node*> Nodes;
            std::vector<Type*> Types;
            std::vector<Rule*> Rules;
            Node* CreateNode(const std::string nodeName, const std::string regex, const bool createAst = true); // Used to create a Node Class
            Type* CreateType(const std::string typeName, const bool createAst = true); // Used to create a Type Class
            Rule* CreateRule(Type* type, const std::vector<Token*> tokens); // Used to create a Rule Class
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