#ifndef DEAMER_ASTGEN_ASTNODE_H
#define DEAMER_ASTGEN_ASTNODE_H

/*
Defines an Abstract class for AstNodes. This will be used for creating new AstNodes and making sure
those Nodes has the neccessary details.
Each AstNode has an initialized AstInformation variable.
*/

#include "Deamer/AstGen/AstInformation.h"
#include <string>
#include <vector>

class AstNode
{
    private:
        std::string CreateIndent(int indent);
    protected:
        std::vector<AstNode*> AstNodes;
        AstInformation* AstInfo;
        std::string AstNodeName;
        bool IsNode;

        AstNode(std::vector<AstNode*> astNodes, bool isNode, std::string astNodeName); // Is used to initliase a basic AST node.
        AstNode(AstInformation* astInformation, bool isNode, std::string astNodeName); // Is used to initiliase AstEndPoints. (Only endpoints may use this constructor)
    public:
        virtual void Generate() = 0; // This generates the source code.
        virtual int GetAstId() = 0;
        void SetAstInformation(AstInformation* astInformation); // Used to set the Ast info after it is constructed.
        void PrintNode(int indent);
        void PrintDirectChildren(int indent);
        void PrintAllChildren();
};

#endif //DEAMER_ASTGEN_ASTNODE_H