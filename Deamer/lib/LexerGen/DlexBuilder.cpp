/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -June 2020 Thimo B�hmer
 * -July 2020 Thimo B�hmer
 */

#include "Deamer/LexerGen/DlexBuilder.h"

deamer::DlexBuilder::DlexBuilder()
{

}

deamer::DlexBuilder::DlexBuilder(deamer::LanguageDefinition* langDef) : deamer::DlexBuilder::DlexBuilder()
{
    deamer::DlexBuilder::langDef = langDef;
}

void deamer::DlexBuilder::AddNode(Node* node)
{

}

void deamer::DlexBuilder::AddIgnoreNode(Node* node)
{

}

bool deamer::DlexBuilder::FinishBuild()
{
    return true;
}

bool deamer::DlexBuilder::StartBuild()
{
    return true;
}
