#include "Deamer/LexerGen/FlexBuilder.h"

FlexBuilder::FlexBuilder()
{
    FlexBuilder::WriteToFile = false;
}

void FlexBuilder::AddNode(Node* node)
{

}

bool FlexBuilder::FinishBuild()
{
    return true;
}

bool FlexBuilder::StartBuild()
{
    return true;
}