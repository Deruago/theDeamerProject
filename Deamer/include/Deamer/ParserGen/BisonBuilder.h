#ifndef DEAMER_PARSERGEN_BISONBUILDER_H
#define DEAMER_PARSERGEN_BISONBUILDER_H

#include "Deamer/ParserGen/ParserBuilder.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include <string>

namespace deamer
{
    class BisonBuilder : public ParserBuilder
    {
        std::string includePart;
        std::string tokenDeclarationPart;
        std::string typeDeclarationPart;
        std::string unionDeclarationPart;
        std::string ruleDeclarationPart;
        Type* curType;
        Type* firstType;
        bool IsFirstType;
        unsigned int curRuleSizeOfType;
        unsigned int currentRulesBuilt;
        void WriteRule(Rule* rule, std::ostringstream* oss);
        void WriteRuleModificationPart(Rule* rule, std::ostringstream* oss);
        public:
            BisonBuilder();
            BisonBuilder(LanguageDefinition* langDef);
            void AddNode(Node* node) override;
            void AddType(Type* type) override;
            void AddRule(Rule* rule) override;
            bool FinishBuild() override;
            bool StartBuild() override;
    };
}

#endif //DEAMER_PARSERGEN_BISONBUILDER_H