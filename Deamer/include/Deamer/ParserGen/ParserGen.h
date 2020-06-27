#ifndef DEAMER_PARSERGEN_PARSERGEN_H
#define DEAMER_PARSERGEN_PARSERGEN_H

#include "Deamer/Types/Generator.h"
#include "Deamer/ParserGen/ParserBuilder.h"
#include "Deamer/ParserGen/DParseBuilder.h"
#include "Deamer/ParserGen/BisonBuilder.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"

class ParserGen : public Generator
{
    ParserBuilder* parserBuilder;
    ParserType_t ParserTarget;
    LanguageDefinition* langDef;
    void SetParserBuilder();
    void BuildNodes();
    void BuildRulesOfType(Type* type);
    public:
        ParserGen(ParserType_t parserTarget, LanguageDefinition* langDef);
        void DirTarget(std::string dirTarget) override;
        void SetTarget(ParserType_t parserTarget);
        bool Build() override;
        bool Write() override;
        void SetLangDef(LanguageDefinition* langDef);
};


#endif //DEAMER_PARSERGEN_PARSERGEN_H