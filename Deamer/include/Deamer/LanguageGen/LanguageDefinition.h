/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
 /*
  * Part of the DeamerProject.
  * For more information go to: https://github.com/Deruago/theDeamerProject
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
