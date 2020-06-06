#ifndef DEAMER_ASTGEN_ASTBUILDER_H
#define DEAMER_ASTGEN_ASTBUILDER_H

#include <string>
#include <fstream>
#include <vector>

class AstBuilder
{
    private:
        std::string Output;
        bool WriteToFile; // If the Builder needs to write to file
        std::string FileName;
        std::ofstream File;
    public:
        AstBuilder();
        void CreatAstNode(std::string TokenName); // Creates an AST Node and writes it to file.
        bool SetFileTarget(std::string fileName);
        std::string GetOutput(); // Returns the output
};

#endif //DEAMER_ASTGEN_ASTBUILDER_H