/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_LANGUAGEGEN_RULE_H
#define DEAMER_LANGUAGEGEN_RULE_H

/*
This header describes the class implementation of Rule. Which is the base class for Rules.
*/

#include "Deamer/Types/Visitable.h"
#include "Deamer/LanguageAnalyzer/LanguageVisitor/LanguageDefinitionVisitor.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/ParserGen/BisonBuilder/BisonBuilder.h"
#include <vector>


namespace deamer
{
    class Rule : public Visitable<Rule, LanguageDefinitionVisitor>
    {
        public:
            Rule() = default;
            Rule(const std::vector<Token*>& tokens);

    		std::vector<Token*> Tokens;
            BitwiseEnum<RuleType_t> RuleType;
            //RuleType_t RuleType = RuleType_t::standard;
    		

            bool IsEmpty() const;
    		void PrintRule();
            std::string MakeConstructorArguments(Token* token_subject);
            std::string MakeConstructorPrototype(Token* token_subject);
            std::string MakeConstructors(Token* token_subject);
            std::string MakeConstructor(Token* token);
    };
}

#endif //DEAMER_LANGUAGEGEN_RULE_H