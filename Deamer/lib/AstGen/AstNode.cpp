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

deamer::AstNode::AstNode(std::vector<deamer::AstNode*> AstNodes, bool isNode, std::string AstNodeName)
{
    deamer::AstNode::AstNodes = AstNodes;
    deamer::AstNode::AstNodeName = AstNodeName;
    deamer::AstNode::IsNode = isNode;
}

deamer::AstNode::AstNode(AstInformation* astInformation, bool isNode, std::string AstNodeName)
{
    deamer::AstNode::AstInfo = astInformation;
    deamer::AstNode::IsNode = isNode;
    deamer::AstNode::AstNodeName = AstNodeName;
}

void deamer::AstNode::PrintDirectChildren(int indent)
{
    deamer::AstNode::PrintNode(indent++);
    if (deamer::AstNode::AstNodes.size() > 0)
    {
        for(int i = 0; i < deamer::AstNode::AstNodes.size(); i++)
        {
            if (GetAstId() == deamer::AstNode::AstNodes[i]->GetAstId())
            {
                deamer::AstNode::AstNodes[i]->PrintDirectChildren(indent - 1);
            }
            else
            {
                deamer::AstNode::AstNodes[i]->PrintDirectChildren(indent);
            }
        }
    }
}

void deamer::AstNode::PrintAllChildren()
{
    deamer::AstNode::PrintNode(0);
    if (deamer::AstNode::AstNodes.size() > 0)
    {
        for(int i = 0; i < deamer::AstNode::AstNodes.size(); i++)
        {
            deamer::AstNode::AstNodes[i]->PrintDirectChildren(1);
        }
    }
}

void deamer::AstNode::PrintNode(int indent)
{
    std::cout << deamer::AstNode::CreateIndent(indent);
    if (deamer::AstNode::IsNode)
    {
        std::cout << deamer::AstNode::AstInfo->LineNumber << ' ' << deamer::AstNode::AstInfo->CharNumber << ' ' << deamer::AstNode::AstInfo->ValueName << '\n';
    }
    else
    {
        std::cout << deamer::AstNode::AstNodeName << '\n';
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