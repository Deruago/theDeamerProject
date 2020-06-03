#ifndef DEAMER_LEXERGEN_LEXERBUILDER_H
#define DEAMER_LEXERGEN_LEXERBUILDER_H

#include <string>
#include <fstream>
#include <vector>
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/LanguageGen/Node.h"

class LexerBuilder
{
    protected:
        LexerType_t LexerType;
        std::string Output;
        bool WriteToFile; // If the Builder needs to write to file
        std::string FileName;
        std::ofstream File;
        LexerBuilder();
        LexerBuilder(std::string fileName);
    public:
        virtual void AddNode(Node* node) = 0; // Writes the node to the file
        virtual bool FinishBuild() = 0;
        bool SetFileTarget(std::string fileName);
        std::string* GetOutput(); // Returns the output
        LexerType_t GetLexerTarget();
};

#endif //DEAMER_LEXERGEN_LEXERBUILDER_H