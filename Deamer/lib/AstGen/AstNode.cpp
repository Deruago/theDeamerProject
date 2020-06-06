#include "Deamer/AstGen/AstNode.h"

AstNode::AstNode(std::vector<AstNode*> astNodes)
{
    AstNode::AstNodes = astNodes;
}