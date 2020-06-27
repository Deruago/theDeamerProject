#ifndef DEAMER_ASTGEN_ASTGEN_H
#define DEAMER_ASTGEN_ASTGEN_H

#include "Deamer/Types/Generator.h"
#include "Deamer/AstGen/AstNode.h"
#include "Deamer/AstGen/AstTree.h"
#include "Deamer/AstGen/AstBuilder.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include <string>

class AstGen : public Generator
{
    private:
        AstBuilder astBuilder;
    public:
        AstGen();
        AstGen(std::string dirTarget);
        void DirTarget(std::string dirTarget) override;
        void FileTarget(std::string fileTarget) override;
        std::string GetAstNodeClassName(std::string TokenName); // Returns the AST Node class name
        void CreateAstNodes(LanguageDefinition* langDef); // Creates a full set of AstNode Classes based of langDef and creates an global header file with all astnode includes
};

#endif //DEAMER_ASTGEN_ASTGEN_H