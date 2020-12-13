/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -June 2020 Thimo B�hmer
 * -July 2020 Thimo B�hmer
 */

#include "Deamer/ParserGen/DParseBuilder/DParseBuilder.h"

deamer::DParseBuilder::DParseBuilder(const LanguageDefinition* langDef) : ParserBuilder(langDef)
{
}

void deamer::DParseBuilder::AddNode(Node* node)
{

}

void deamer::DParseBuilder::AddType(Type* type)
{

}

void deamer::DParseBuilder::AddRule(Rule* rule)
{

}

bool deamer::DParseBuilder::FinishBuild()
{
    return true;
}

bool deamer::DParseBuilder::StartBuild()
{
    return true;
}