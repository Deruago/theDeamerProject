#ifndef DEAMER_ASTGEN_ASTBUILDER_H
#define DEAMER_ASTGEN_ASTBUILDER_H

#include <string>
#include <fstream>
#include <vector>

class AstBuilder
{
    private:
        std::string Output;
        std::string directory;
        std::ofstream* File;

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
        void FinishGlobalHeaderFile();
        void SetDirTarget(std::string dirName);
        std::string GetOutput(); // Returns the output
};

#endif //DEAMER_ASTGEN_ASTBUILDER_H