/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -June 2020 Thimo B�hmer
 * -July 2020 Thimo B�hmer
 */

#include "Deamer/AstGen/AstGen.h"
#include "Deamer/AstGen/AstBuilderFactory.h"
#include <sstream>

deamer::AstGen::AstGen(const LanguageDefinition& language_definition, AstBuilderType ast_builder_type)
{
    language_definition_ = language_definition;
    astBuilder = AstBuilderFactory().MakeAstBuilder(ast_builder_type, "AstNodes/", language_definition_.LanguageName);
    CreateDirectoryIfNotExist("AstNodes/");
}

//deamer::AstGen::AstGen(std::string dirTarget)
//{
//    AstGen::DirTarget(dirTarget);
//}

void deamer::AstGen::DirTarget(std::string dirTarget)
{
    dirTarget.append("AstNodes/");
}

void deamer::AstGen::FileTarget(std::string fileTarget)
{
}

void deamer::AstGen::CreateAstNodes()
{
    astBuilder->StartBuild();
    for (auto& Type : language_definition_.Types)
    {
        if (!Type->TokenPermission.has_flag(TokenPermission_t::ignore))
            astBuilder->Build(*Type);
    }
	
    for (auto& Node : language_definition_.Nodes)
    {
        if (!Node->TokenPermission.has_flag(TokenPermission_t::ignore))
            astBuilder->Build(*Node);
    }
    astBuilder->FinishBuild();
}