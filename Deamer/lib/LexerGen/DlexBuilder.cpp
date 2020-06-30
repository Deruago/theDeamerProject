#include "Deamer/LexerGen/DlexBuilder.h"

DlexBuilder::DlexBuilder()
{

}

DlexBuilder::DlexBuilder(LanguageDefinition* langDef) : DlexBuilder::DlexBuilder()
{
    DlexBuilder::langDef = langDef;
}

void DlexBuilder::AddNode(Node* node)
{

}

bool DlexBuilder::FinishBuild()
{
    return true;
}

bool DlexBuilder::StartBuild()
{
    return true;
}