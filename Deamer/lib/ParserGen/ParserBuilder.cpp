#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/ParserGen/ParserBuilder.h"

ParserBuilder::ParserBuilder()
{

}

ParserBuilder::ParserBuilder(ParserType_t parserTarget)
{
    ParserBuilder::parserType = parserTarget;
}