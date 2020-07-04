#include "Deamer/ParserGen/DParseBuilder.h"

deamer::DParseBuilder::DParseBuilder()
{

}

deamer::DParseBuilder::DParseBuilder(LanguageDefinition* langDef) : deamer::DParseBuilder::DParseBuilder()
{
    deamer::DParseBuilder::langDef = langDef;
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