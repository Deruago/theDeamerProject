/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -June 2020 Thimo B�hmer
 * -July 2020 Thimo B�hmer
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
            // STMTS is a vector of new STMT.
            ParserBuilder* MakeParserUseVectorBasedDS(deamer::ParserType_t ParserType_t, LanguageDefinition* langDef) const;
            //e.g:
            //STMTS:
            //    STMT STMTS
            // New STMTS recursively define new STMTS.
            ParserBuilder* MakeParserUseRecursiveBasedDS(deamer::ParserType_t ParserType_t, LanguageDefinition* langDef) const;
    };
}

#endif //DEAMER_PARSERGEN_PARSERFACTORY_H