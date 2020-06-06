#ifndef DEAMER_ASTGEN_ASTNODE_H
#define DEAMER_ASTGEN_ASTNODE_H

/*
Defines an Abstract class for AstNodes. This will be used for creating new AstNodes and making sure
those Nodes has the neccessary details
*/

#include "Deamer/AstGen/AstInformation.h"
#include <vector>

class AstNode
{
    protected:
        std::vector<AstNode*> AstNodes;
        AstInformation AstInfo;

        AstNode(std::vector<AstNode*> astNodes); // Is used to initliase a basic AST node.
        AstNode(AstInformation astInformation); // Is used to initiliase AstEndPoints. (Only endpoints may use this constructor)
        void PrintNode();
        void PrintDirectChildren();
        void PrintAllChildren();
    public:
        virtual void Generate() = 0; // This generates the source code.
};

#endif //DEAMER_ASTGEN_ASTNODE_H