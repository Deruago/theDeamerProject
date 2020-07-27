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
    AstGen::DirTarget(dirTarget);
}

void deamer::AstGen::DirTarget(std::string dirTarget)
{
    dirTarget.append("AstNodes/");
    CreateDirectoryIfNotExist(&dirTarget);

    astBuilder.SetDirTarget(dirTarget);
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
    astBuilder.SetLanguageName(langDef->GetLanguageName());
    
    astBuilder.CreateGlobalHeaderFile();
    astBuilder.CreateAstNodeEnumFile();
    
    astBuilder.CreateAstTree(langDef->Types[langDef->Types.size() - 1], langDef->Types[langDef->Types.size() - 1]->IsNode);
    astBuilder.AppendAstTreeHeaderFile(langDef->Types[langDef->Types.size() - 1]->TokenName);
    astBuilder.AppendAstNodeEnumFile(langDef->Types[langDef->Types.size() - 1]->TokenName);

    for (int i = langDef->Types.size() - 2; i >= 0; i--)
    {
        if (langDef->Types[i]->CreateAst)
        {
            astBuilder.CreateAstNode(langDef->Types[i], langDef->Types[i]->IsNode);
            astBuilder.AppendAstNodeHeaderFile(langDef->Types[i]->TokenName);
            astBuilder.AppendAstNodeEnumFile(langDef->Types[i]->TokenName);
        }
    }


    for (int i = 0; i < langDef->Nodes.size(); i++)
    {
        if (langDef->Nodes[i]->CreateAst)
        {
            astBuilder.CreateAstNode(langDef->Nodes[i], langDef->Nodes[i]->IsNode);
            astBuilder.AppendAstNodeHeaderFile(langDef->Nodes[i]->TokenName);
            astBuilder.AppendAstNodeEnumFile(langDef->Nodes[i]->TokenName);
        }
    }

    astBuilder.FinishGlobalHeaderFile();
    astBuilder.FinishAstNodeEnumFile();
}