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

namespace deamer
{
    class AstBuilder : public Builder
    {
        private:
            std::string languageName;
            void FillAstSourceFile(std::ofstream* astSourceFile, std::string tokenName, std::string* defaultTokenName, bool isNode);
            void FillAstHeaderFile(std::ofstream* astHeaderFile, std::string tokenName, std::string* defaultTokenName);
            void FillAstTreeSourceFile(std::ofstream* astSourceFile, std::string tokenName, std::string* defaultTokenName, bool isNode);
            void FillAstTreeHeaderFile(std::ofstream* astHeaderFile, std::string tokenName, std::string* defaultTokenName);
        public:
            AstBuilder();
            void CreateAstNode(std::string TokenName, bool isNode); // Creates an AST Node and writes it to file.
            void CreateAstTree(std::string TokenName, bool isNode);
            
            void CreateAstNodeEnumFile();
            void AppendAstNodeEnumFile(std::string TokenName);
            void FinishAstNodeEnumFile();

            void CreateGlobalHeaderFile();
            void AppendAstNodeHeaderFile(std::string TokenName);
            void AppendAstTreeHeaderFile(std::string TokenName);
            void FinishGlobalHeaderFile();

            void SetLanguageName(std::string languageName);
    };
}

#endif //DEAMER_ASTGEN_ASTBUILDER_H