/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_ASTGEN_ASTBUILDER_H
#define DEAMER_ASTGEN_ASTBUILDER_H

#include "Deamer/Types/Builder.h"
#include <string>
#include <fstream>
#include <vector>

#include "Deamer/FileBuilder/Types/FileClassSection.h"

namespace deamer
{
    class AstBuilder : public Builder
    {
        private:
            std::string languageName;
            FileClassSection* _AstNode;
            FileClassSection* type_int;
            FileClassSection* type_void;
            void FillAstSourceFile(std::ofstream* astSourceFile, std::string tokenName, std::string* defaultTokenName, bool isNode) const;
            deamer::FileClassSection* GetAstNodeFileBuilderClass() const;
            void FillAstHeaderFile(std::ofstream* astHeaderFile, std::string tokenName, std::string* defaultTokenName) const;
            void FillAstTreeSourceFile(std::ofstream* astSourceFile, std::string tokenName, std::string* defaultTokenName, bool isNode) const;
            void FillAstTreeHeaderFile(std::ofstream* astHeaderFile, std::string tokenName, std::string* defaultTokenName) const;
        public:
            AstBuilder();
            void CreateAstNode(std::string TokenName, bool isNode); // Creates an AST Node and writes it to file.
            void CreateAstTree(std::string TokenName, bool isNode) const;
            
            void CreateAstNodeEnumFile() const;
            void AppendAstNodeEnumFile(std::string TokenName) const;
            void FinishAstNodeEnumFile() const;

            void CreateGlobalHeaderFile() const;
            void AppendAstNodeHeaderFile(std::string TokenName) const;
            void AppendAstTreeHeaderFile(std::string TokenName) const;
            void FinishGlobalHeaderFile() const;

            void SetLanguageName(std::string languageName);
    };
}

#endif //DEAMER_ASTGEN_ASTBUILDER_H