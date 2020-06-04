#ifndef DEAMER_PARSERGEN_BISONBUILDER_H
#define DEAMER_PARSERGEN_BISONBUILDER_H

#include "Deamer/ParserGen/ParserBuilder.h"
#include <string>

class BisonBuilder : public ParserBuilder
{
    std::string includePart;
    std::string tokenDeclarationPart;
    std::string typeDeclarationPart;
    std::string unionDeclarationPart;
    std::string ruleDeclarationPart;
    bool IsFirstType;
    unsigned int curRuleSizeOfType;
    unsigned int currentRulesBuilt;
    void WriteRule(Rule* rule, std::ostringstream* oss);
    void WriteRuleModificationPart(Rule* rule, std::ostringstream* oss);
    public:
        BisonBuilder();
        void AddNode(Node* node) override;
        void AddType(Type* type) override;
        void AddRule(Rule* rule) override;
        bool FinishBuild() override;
        bool StartBuild() override;
};

#endif //DEAMER_PARSERGEN_BISONBUILDER_H