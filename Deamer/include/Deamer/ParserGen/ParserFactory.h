/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -June 2020 Thimo Bohmer
 * -July 2020 Thimo Bohmer
 */

#ifndef DEAMER_PARSERGEN_PARSERFACTORY_H
#define DEAMER_PARSERGEN_PARSERFACTORY_H
#include "Deamer/LanguageGen/LanguageGenConstants.h"

namespace deamer
{
    class LanguageDefinition;
    class ParserBuilder;

    class ParserFactory
    {
        public:
            ParserFactory() = default;
            ~ParserFactory() = default;
            //e.g:
            //STMTS:
            //    STMT STMTS
            // New STMTS recursively define new STMTS.
            ParserBuilder* MakeParser(deamer::ParserType_t ParserType_t, LanguageDefinition* langDef) const;
    };
}

#endif //DEAMER_PARSERGEN_PARSERFACTORY_H