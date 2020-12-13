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
#include "Deamer/ParserGen/BisonBuilder/BisonBuilder.h"
#include "Deamer/ParserGen/DParseBuilder/DParseBuilder.h"

deamer::ParserBuilder* deamer::ParserFactory::MakeParser(ParserType_t ParserType_t, const LanguageDefinition* langDef) const
{
    switch(ParserType_t)
    {
        case ParserType_t::dparse:
            return new DParseBuilder(langDef);
        case ParserType_t::bison:
            return new BisonBuilder(langDef);
    }
    return nullptr;
}