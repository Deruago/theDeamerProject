/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_ASTGEN_ASTGEN_H
#define DEAMER_ASTGEN_ASTGEN_H

#include "Deamer/Types/Generator.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include "Deamer/AstGen/AstBuilder.h"
#include <string>
#include <memory>


namespace deamer
{
    enum class AstBuilderType;
	
    class AstGen : public Generator
    {
        private:
            std::unique_ptr<AstBuilder> astBuilder;
            LanguageDefinition language_definition_;
        public:
            AstGen(const LanguageDefinition& language_definition, AstBuilderType ast_builder_type);
            //AstGen(std::string dirTarget);
            void DirTarget(std::string dirTarget) override;
            void FileTarget(std::string fileTarget) override;
            void CreateAstNodes(); // Creates a full set of AstNode Classes based of langDef and creates an global header file with all astnode includes
    };
}

#endif //DEAMER_ASTGEN_ASTGEN_H