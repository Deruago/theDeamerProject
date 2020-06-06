#ifndef DEAMER_ASTGEN_ASTGEN_H
#define DEAMER_ASTGEN_ASTGEN_H

#include "Deamer/AstGen/AstNode.h"
#include "Deamer/AstGen/AstTree.h"
#include "Deamer/AstGen/AstBuilder.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include <string>

class AstGen
{
    private:
        AstBuilder astBuilder;
    public:
        AstGen();
        AstGen(std::string dirTarget);
        void DirTarget(std::string dirTarget);
        std::string GetAstNodeClassName(std::string TokenName); // Returns the AST Node class name
        void CreateAstNodes(LanguageDefinition* langDef); // Creates a full set of AstNode Classes based of langDef and creates an global header file with all astnode includes
};

#endif //DEAMER_ASTGEN_ASTGEN_H