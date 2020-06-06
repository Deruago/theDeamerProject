#include "Deamer/AstGen/AstNode.h"
#include <iostream>

AstNode::AstNode(std::vector<AstNode*> astNodes)
{
    AstNode::AstNodes = astNodes;
}

AstNode::AstNode(AstInformation* astInformation)
{
    AstNode::AstInfo = astInformation;
}

void AstNode::PrintDirectChildren()
{
    AstNode::PrintNode();
    if (AstNode::AstNodes.size() > 0)
    {
        for(int i = 0; i < AstNode::AstNodes.size(); i++)
        {
            AstNode::AstNodes[i]->PrintNode();
        }
    }
}

void AstNode::PrintAllChildren()
{
    AstNode::PrintNode();
    if (AstNode::AstNodes.size() > 0)
    {
        for(int i = 0; i < AstNode::AstNodes.size(); i++)
        {
            AstNode::AstNodes[i]->PrintDirectChildren();
        }
    }
}

void AstNode::PrintNode()
{
    std::cout << AstNode::AstInfo->LineNumber << ' ' << AstNode::AstInfo->CharNumber << ' ' << AstNode::AstInfo->ValueName << '\n';
}
