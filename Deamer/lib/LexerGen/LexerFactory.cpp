/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -June 2020 Thimo Bohmer
 * -July 2020 Thimo Bohmer
 */

#include "Deamer/LexerGen/LexerFactory.h"
#include "Deamer/LexerGen/LexerBuilder.h"
#include "Deamer/LexerGen/FlexBuilder.h"
#include "Deamer/LexerGen/DlexBuilder.h"

deamer::LexerBuilder* deamer::LexerFactory::MakeLexerUseVectorBasedDS(LexerType_t lexerType_t, LanguageDefinition* langDef) const
{
    switch(lexerType_t)
    {
        case LexerType_s::dlex:
            return new DlexBuilder(langDef);
        case LexerType_s::flex:
            return new FlexBuilder(langDef);
    }
    return nullptr;
}

deamer::LexerBuilder* deamer::LexerFactory::MakeLexerUseRecursiveBasedDS(LexerType_t lexerType_t, LanguageDefinition* langDef) const
{
    switch(lexerType_t)
    {
        case LexerType_s::dlex:
            return new DlexBuilder(langDef);
        case LexerType_s::flex:
            return new FlexBuilder(langDef);
    }
    return nullptr;
}