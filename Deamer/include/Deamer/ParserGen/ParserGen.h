/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_PARSERGEN_PARSERGEN_H
#define DEAMER_PARSERGEN_PARSERGEN_H

#include "Deamer/Types/Generator.h"
#include "Deamer/ParserGen/ParserBuilder.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include "Deamer/Types/SmartPointer/BaseAutoPtr.h"
#include <string>


namespace deamer
{
    class ParserGen : public Generator
    {
    private:
        std::string Directory;
        std::string Filename = "parser.y";
    	
    	ParserType_t ParserTarget;
        LanguageDefinition* langDef;
        BaseAutoPtr<ParserBuilder> parserBuilder;

    	void BuildNodes() const;
    public:
        ParserGen(ParserType_t parserTarget, LanguageDefinition* langDef);
        virtual ~ParserGen() = default;
    	
        std::string GetFileLocation() const;
        std::string GetDirectoryLocation() const;

    	void DirTarget(std::string dirTarget) override;
        void FileTarget(std::string fileTarget) override;
        void SetTarget(ParserType_t parserTarget);
        void Build() override;
        void Write() override;
    };
}

#endif //DEAMER_PARSERGEN_PARSERGEN_H