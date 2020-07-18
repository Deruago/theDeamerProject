/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -June 2020 Thimo Bohmer
 * -July 2020 Thimo Bohmer
 */

#include "Deamer/ParserGen/ParserFactory.h"
#include "Deamer/ParserGen/ParserBuilder.h"
#include "Deamer/ParserGen/BisonBuilder.h"
#include "Deamer/ParserGen/DParseBuilder.h"

deamer::ParserBuilder* deamer::ParserFactory::MakeParserUseVectorBasedDS(deamer::ParserType_t ParserType_t, LanguageDefinition* langDef) const
{
    switch(ParserType_t)
    {
        case deamer::ParserType_t::dparse:
            return new deamer::DParseBuilder(langDef);
        case deamer::ParserType_t::bison:
            return new deamer::BisonBuilder(langDef);
    }
    return nullptr;
}

deamer::ParserBuilder* deamer::ParserFactory::MakeParserUseRecursiveBasedDS(deamer::ParserType_t ParserType_t, LanguageDefinition* langDef) const
{
    switch(ParserType_t)
    {
        case deamer::ParserType_t::dparse:
            return new deamer::DParseBuilder(langDef);
        case deamer::ParserType_t::bison:
            return new deamer::BisonBuilder(langDef);
    }
    return nullptr;
}