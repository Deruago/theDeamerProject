#ifndef DEAMER_PARSERGEN_BISONBUILDER_H
#define DEAMER_PARSERGEN_BISONBUILDER_H

#include "Deamer/ParserGen/ParserBuilder.h"

class BisonBuilder : public ParserBuilder
{
    public:
        BisonBuilder();
        void AddNode(Node* node) override;
        void AddType(Type* type) override;
        void AddRule(Rule* rule) override;
        bool FinishBuild() override;
        bool StartBuild() override;
};

#endif //DEAMER_PARSERGEN_BISONBUILDER_H