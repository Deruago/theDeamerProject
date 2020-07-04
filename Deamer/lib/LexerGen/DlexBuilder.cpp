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

bool deamer::DlexBuilder::FinishBuild()
{
    return true;
}

bool deamer::DlexBuilder::StartBuild()
{
    return true;
}