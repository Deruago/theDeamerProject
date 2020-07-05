/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/AstGen/AstGen.h"
#include <sstream>

deamer::AstGen::AstGen()
{

}

deamer::AstGen::AstGen(std::string dirTarget)
{
    deamer::AstGen::DirTarget(dirTarget);
}

void deamer::AstGen::DirTarget(std::string dirTarget)
{
    dirTarget.append("AstNodes/");
    deamer::AstGen::CreateDirectoryIfNotExist(&dirTarget);

    deamer::AstGen::astBuilder.SetDirTarget(dirTarget);
}

void deamer::AstGen::FileTarget(std::string fileTarget)
{
}

std::string deamer::AstGen::GetAstNodeClassName(std::string TokenName)
{
    std::ostringstream oss;
    oss << "AstNode_" << TokenName;
    return oss.str();
}

void deamer::AstGen::CreateAstNodes(LanguageDefinition* langDef)
{
    deamer::AstGen::astBuilder.SetLanguageName(langDef->GetLanguageName());
    
    deamer::AstGen::astBuilder.CreateGlobalHeaderFile();
    deamer::AstGen::astBuilder.CreateAstNodeEnumFile();
    
    deamer::AstGen::astBuilder.CreateAstTree(langDef->Types[langDef->Types.size() - 1]->TokenName, langDef->Types[langDef->Types.size() - 1]->IsNode);
    deamer::AstGen::astBuilder.AppendAstTreeHeaderFile(langDef->Types[langDef->Types.size() - 1]->TokenName);
    deamer::AstGen::astBuilder.AppendAstNodeEnumFile(langDef->Types[langDef->Types.size() - 1]->TokenName);

    for (int i = langDef->Types.size() - 2; i >= 0; i--)
    {
        if (langDef->Types[i]->CreateAst)
        {
            deamer::AstGen::astBuilder.CreateAstNode(langDef->Types[i]->TokenName, langDef->Types[i]->IsNode);
            deamer::AstGen::astBuilder.AppendAstNodeHeaderFile(langDef->Types[i]->TokenName);
            deamer::AstGen::astBuilder.AppendAstNodeEnumFile(langDef->Types[i]->TokenName);
        }
    }


    for (int i = 0; i < langDef->Nodes.size(); i++)
    {
        if (langDef->Nodes[i]->CreateAst)
        {
            deamer::AstGen::astBuilder.CreateAstNode(langDef->Nodes[i]->TokenName, langDef->Nodes[i]->IsNode);
            deamer::AstGen::astBuilder.AppendAstNodeHeaderFile(langDef->Nodes[i]->TokenName);
            deamer::AstGen::astBuilder.AppendAstNodeEnumFile(langDef->Nodes[i]->TokenName);
        }
    }

    deamer::AstGen::astBuilder.FinishGlobalHeaderFile();
    deamer::AstGen::astBuilder.FinishAstNodeEnumFile();
}