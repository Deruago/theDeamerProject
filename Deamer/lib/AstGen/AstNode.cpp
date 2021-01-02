/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
 /*
  * Part of the DeamerProject.
  * For more information go to: https://github.com/Deruago/theDeamerProject
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
