/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/AstGen/AstNode.h"
#include <sstream>
#include <iostream>

deamer::AstNode::AstNode(bool isNode, std::string astNodeName)
{
    AstNodeName = astNodeName;
    IsNode = isNode;
}

deamer::AstNode::AstNode(std::vector<AstNode*> AstNodes, bool isNode, std::string AstNodeName)
{
    AstNode::AstNodes = AstNodes;
    AstNode::AstNodeName = AstNodeName;
    IsNode = isNode;
}

deamer::AstNode::AstNode(AstInformation* astInformation, bool isNode, std::string AstNodeName)
{
    AstInfo = astInformation;
    IsNode = isNode;
    AstNode::AstNodeName = AstNodeName;
}

void deamer::AstNode::PrintDirectChildren(int indent)
{
    PrintNode(indent++);
    if (!AstNodes.empty())
    {
        for(int i = 0; i < AstNodes.size(); i++)
        {
            if (GetAstId() == AstNodes[i]->GetAstId())
            {
                AstNodes[i]->PrintDirectChildren(indent - 1);
            }
            else
            {
                AstNodes[i]->PrintDirectChildren(indent);
            }
        }
    }
}

void deamer::AstNode::PrintAllChildren()
{
    PrintNode(0);
    if (AstNodes.size() > 0)
    {
        for(int i = 0; i < AstNodes.size(); i++)
        {
            AstNodes[i]->PrintDirectChildren(1);
        }
    }
}

void deamer::AstNode::PrintNode(int indent)
{
    std::cout << CreateIndent(indent);
    if (IsNode)
    {
        std::cout << AstInfo->LineNumber << ' ' << AstInfo->CharNumber << ' ' << AstInfo->ValueName << '\n';
    }
    else
    {
        std::cout << AstNodeName << '\n';
    }
}

std::string deamer::AstNode::CreateIndent(int indent)
{
    std::ostringstream oss;
    for(int i = 0; i < indent; i++)
    {
        oss << "    ";
    }
    return oss.str();
}

std::string deamer::AstNode::GetValue() const
{
    return AstInfo->ValueName;
}
