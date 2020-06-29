#include "Deamer/AstGen/AstGen.h"
#include <sstream>

AstGen::AstGen()
{

}

AstGen::AstGen(std::string dirTarget)
{
    AstGen::DirTarget(dirTarget);
}

void AstGen::DirTarget(std::string dirTarget)
{
    dirTarget.append("AstNodes/");
    AstGen::CreateDirectoryIfNotExist(&dirTarget);

    AstGen::astBuilder.SetDirTarget(dirTarget);
}

void AstGen::FileTarget(std::string fileTarget)
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
    AstGen::astBuilder.CreateAstNodeEnumFile();
    
    AstGen::astBuilder.CreateAstTree(langDef->Types[langDef->Types.size() - 1]->TokenName, langDef->Types[langDef->Types.size() - 1]->IsNode);
    AstGen::astBuilder.AppendAstTreeHeaderFile(langDef->Types[langDef->Types.size() - 1]->TokenName);
    AstGen::astBuilder.AppendAstNodeEnumFile(langDef->Types[langDef->Types.size() - 1]->TokenName);

    for (int i = langDef->Types.size() - 2; i >= 0; i--)
    {
        if (langDef->Types[i]->CreateAst)
        {
            AstGen::astBuilder.CreateAstNode(langDef->Types[i]->TokenName, langDef->Types[i]->IsNode);
            AstGen::astBuilder.AppendAstNodeHeaderFile(langDef->Types[i]->TokenName);
            AstGen::astBuilder.AppendAstNodeEnumFile(langDef->Types[i]->TokenName);
        }
    }


    for (int i = 0; i < langDef->Nodes.size(); i++)
    {
        if (langDef->Nodes[i]->CreateAst)
        {
            AstGen::astBuilder.CreateAstNode(langDef->Nodes[i]->TokenName, langDef->Nodes[i]->IsNode);
            AstGen::astBuilder.AppendAstNodeHeaderFile(langDef->Nodes[i]->TokenName);
            AstGen::astBuilder.AppendAstNodeEnumFile(langDef->Nodes[i]->TokenName);
        }
    }

    AstGen::astBuilder.FinishGlobalHeaderFile();
    AstGen::astBuilder.FinishAstNodeEnumFile();
}