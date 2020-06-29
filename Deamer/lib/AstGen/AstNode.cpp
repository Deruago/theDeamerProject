#include "Deamer/AstGen/AstNode.h"
#include <sstream>
#include <iostream>

AstNode::AstNode(std::vector<AstNode*> astNodes, bool isNode, std::string astNodeName)
{
    AstNode::AstNodes = astNodes;
    AstNode::AstNodeName = astNodeName;
    AstNode::IsNode = isNode;
}

AstNode::AstNode(AstInformation* astInformation, bool isNode, std::string astNodeName)
{
    AstNode::AstInfo = astInformation;
    AstNode::IsNode = isNode;
    AstNode::AstNodeName = astNodeName;
}

void AstNode::PrintDirectChildren(int indent)
{
    AstNode::PrintNode(indent++);
    if (AstNode::AstNodes.size() > 0)
    {
        for(int i = 0; i < AstNode::AstNodes.size(); i++)
        {
            if (GetAstId() == AstNode::AstNodes[i]->GetAstId())
            {
                AstNode::AstNodes[i]->PrintDirectChildren(indent - 1);
            }
            else
            {
                AstNode::AstNodes[i]->PrintDirectChildren(indent);
            }
        }
    }
}

void AstNode::PrintAllChildren()
{
    AstNode::PrintNode(0);
    if (AstNode::AstNodes.size() > 0)
    {
        for(int i = 0; i < AstNode::AstNodes.size(); i++)
        {
            AstNode::AstNodes[i]->PrintDirectChildren(1);
        }
    }
}

void AstNode::PrintNode(int indent)
{
    std::cout << AstNode::CreateIndent(indent);
    if (AstNode::IsNode)
    {
        std::cout << AstNode::AstInfo->LineNumber << ' ' << AstNode::AstInfo->CharNumber << ' ' << AstNode::AstInfo->ValueName << '\n';
    }
    else
    {
        std::cout << AstNode::AstNodeName << '\n';
    }
}

std::string AstNode::CreateIndent(int indent)
{
    std::ostringstream oss;
    for(int i = 0; i < indent; i++)
    {
        oss << "    ";
    }
    return oss.str();
}