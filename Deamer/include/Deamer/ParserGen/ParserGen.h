#ifndef DEAMER_PARSERGEN_PARSERGEN_H
#define DEAMER_PARSERGEN_PARSERGEN_H

#include "Deamer/Types/Generator.h"
#include "Deamer/ParserGen/ParserBuilder.h"
#include "Deamer/ParserGen/DParseBuilder.h"
#include "Deamer/ParserGen/BisonBuilder.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include <string>

namespace deamer
{
    class ParserGen : public Generator
    {
        private:
            ParserBuilder* GetBuilder(ParserType_t parserType_t);
            ParserBuilder* parserBuilder;
            LanguageDefinition* langDef;
            std::string Directory;
            std::string Filename = "parser.y";
            void SetParserBuilder();
            void BuildNodes();
            void BuildRulesOfType(Type* type);
        public:
            ParserType_t ParserTarget;
            std::string GetFileLocation();
            std::string GetDirectoryLocation();
            ParserGen(ParserType_t parserTarget, LanguageDefinition* langDef);
            void DirTarget(std::string dirTarget) override;
            void FileTarget(std::string fileTarget) override;
            void SetTarget(ParserType_t parserTarget);
            bool Build() override;
            bool Write() override;
            void SetLangDef(LanguageDefinition* langDef);
    };
}

#endif //DEAMER_PARSERGEN_PARSERGEN_H