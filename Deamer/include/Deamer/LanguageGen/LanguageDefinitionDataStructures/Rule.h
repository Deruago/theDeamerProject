/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -June 2020 Thimo B�hmer
 * -July 2020 Thimo B�hmer
 */

#ifndef DEAMER_LANGUAGEGEN_RULE_H
#define DEAMER_LANGUAGEGEN_RULE_H

/*
This header describes the class implementation of Rule. Which is the base class for Rules.
*/

#include "Deamer/Types/Visitable.h"
#include "Deamer/LanguageAnalyzer/LanguageVisitor/LanguageDefinitionVisitor.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
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
    };
}

#endif //DEAMER_LANGUAGEGEN_RULE_H