#ifndef DEAMER_ASTGEN_ASTNODE_H
#define DEAMER_ASTGEN_ASTNODE_H

/*
Defines an Abstract class for AstNodes. This will be used for creating new AstNodes and making sure
those Nodes has the neccessary details.
Each AstNode has an initialized AstInformation variable.
*/

#include "Deamer/AstGen/AstInformation.h"
#include <vector>

class AstNode
{
    protected:
        std::vector<AstNode*> AstNodes;
        AstInformation* AstInfo;

        AstNode(std::vector<AstNode*> astNodes); // Is used to initliase a basic AST node.
        AstNode(AstInformation* astInformation); // Is used to initiliase AstEndPoints. (Only endpoints may use this constructor)
    public:
        virtual void Generate() = 0; // This generates the source code.
        void SetAstInformation(AstInformation* astInformation); // Used to set the Ast info after it is constructed.
        void PrintNode();
        void PrintDirectChildren();
        void PrintAllChildren();
};

#endif //DEAMER_ASTGEN_ASTNODE_H