#include "./AstNodeX.h"
#include "Deamer/AstGen/AstNode.h"
#include <iostream>
#include <fstream>

AstNodeX::AstNodeX(std::vector<AstNode*> astNodes) : AstNode::AstNode(astNodes)
{

}

AstNodeX::AstNodeX(AstInformation* astInformation) : AstNode::AstNode(astInformation)
{

}

void AstNodeX::Generate()
{
    
}