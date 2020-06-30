#ifndef DEAMER_PARSERGEN_DPARSEBUILDER_H
#define DEAMER_PARSERGEN_DPARSEBUILDER_H

#include "Deamer/ParserGen/ParserBuilder.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"

class DParseBuilder : public ParserBuilder
{
    public:
        DParseBuilder();
        DParseBuilder(LanguageDefinition* langDef);
        void AddNode(Node* node) override;
        void AddType(Type* type) override;
        void AddRule(Rule* rule) override;
        bool FinishBuild() override;
        bool StartBuild() override;
        
};

#endif //DEAMER_PARSERGEN_DPARSEBUILDER_H