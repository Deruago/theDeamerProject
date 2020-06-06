#ifndef DEAMER_ASTGEN_ASTBUILDER_H
#define DEAMER_ASTGEN_ASTBUILDER_H

#include "Deamer/Types/Builder.h"
#include <string>
#include <fstream>
#include <vector>

class AstBuilder : public Builder
{
    private:
        void FillAstSourceFile(std::ofstream* astSourceFile, std::string tokenName);
        void FillAstHeaderFile(std::ofstream* astHeaderFile, std::string tokenName);
        void FillAstTreeSourceFile(std::ofstream* astSourceFile, std::string tokenName);
        void FillAstTreeHeaderFile(std::ofstream* astHeaderFile, std::string tokenName);
    public:
        AstBuilder();
        void CreateAstNode(std::string TokenName); // Creates an AST Node and writes it to file.
        void CreateAstTree(std::string TokenName);
        void CreateGlobalHeaderFile();
        void AppendAstNodeHeaderFile(std::string TokenName);
        void AppendAstTreeHeaderFile(std::string TokenName);
        void FinishGlobalHeaderFile();
};

#endif //DEAMER_ASTGEN_ASTBUILDER_H