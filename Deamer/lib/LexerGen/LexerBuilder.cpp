#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/LexerGen/LexerBuilder.h"

LexerBuilder::LexerBuilder()
{

}

LexerBuilder::LexerBuilder(LexerType_t lexerTarget)
{
    LexerBuilder::lexerType = lexerTarget;
}