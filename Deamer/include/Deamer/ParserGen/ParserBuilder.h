#ifndef DEAMER_PARSERGEN_PARSERBUILDER_H
#define DEAMER_PARSERGEN_PARSERBUILDER_H

#include <string>
#include <fstream>
#include <vector>
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/LanguageGen/Node.h"
#include "Deamer/LanguageGen/Type.h"
#include "Deamer/LanguageGen/Rule.h"

class ParserBuilder
{
    protected:
        ParserType_t parserType;
        std::string Output;
        bool WriteToFile; // If the Builder needs to write to file
        std::string FileName;
        std::ofstream File;
        ParserBuilder();
        ParserBuilder(std::string fileName);
    public:
        virtual void AddNode(Node* node) = 0; // Writes the node to the file
        virtual void AddType(Type* type) = 0; // Writes the type to the file
        virtual void AddRule(Rule* rule) = 0; // Writes the rule to the file, Note: Type already includes rules so this could be unneccessary
        virtual bool StartBuild() = 0;
        virtual bool FinishBuild() = 0;
        bool SetFileTarget(std::string fileName);
        std::string* GetOutput(); // Returns the output
        ParserType_t GetParserTarget();
};

#endif //DEAMER_PARSERGEN_PARSERBUILDER_H