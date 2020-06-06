#include "Deamer/AstGen/AstGen.h"
#include <sstream>

AstGen::AstGen()
{

}

std::string AstGen::GetAstNodeClassName(std::string TokenName)
{
    std::ostringstream oss;
    oss << "AstNode_" << TokenName;
    return oss.str();
}

void AstGen::CreateAstNodes(LanguageDefinition* langDef)
{
    AstGen::astBuilder.CreateGlobalHeaderFile();
    
    AstGen::astBuilder.CreateAstTree(langDef->Types[0]->TokenName);
    AstGen::astBuilder.AppendAstNodeHeaderFile(langDef->Types[0]->TokenName);

    for (int i = 1; i < langDef->Types.size(); i++)
    {
        AstGen::astBuilder.AppendAstNodeHeaderFile(langDef->Types[i]->TokenName);
        AstGen::astBuilder.CreateAstNode(langDef->Types[i]->TokenName);
    }


    for (int i = 0; i < langDef->Nodes.size(); i++)
    {
        AstGen::astBuilder.AppendAstNodeHeaderFile(langDef->Nodes[i]->TokenName);
        AstGen::astBuilder.CreateAstNode(langDef->Nodes[i]->TokenName);
    }

    AstGen::astBuilder.FinishGlobalHeaderFile();
}