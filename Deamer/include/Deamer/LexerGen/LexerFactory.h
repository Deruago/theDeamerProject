/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -June 2020 Thimo B�hmer
 * -July 2020 Thimo B�hmer
 */

#ifndef DEAMER_LEXERGEN_LEXERFACTORY_H
#define DEAMER_LEXERGEN_LEXERFACTORY_H
#include "Deamer/LanguageGen/LanguageGenConstants.h"

namespace deamer
{
    class LanguageDefinition;
    class LexerBuilder;

    class LexerFactory
    {
        public:
            LexerFactory() = default;
            ~LexerFactory() = default;
            //e.g:
            //STMTS:
            //    STMT STMTS
            // STMTS is a vector of new STMT.
            LexerBuilder* MakeLexerUseVectorBasedDS(LexerType_t lexerType_t, LanguageDefinition* langDef) const;
            //e.g:
            //STMTS:
            //    STMT STMTS
            // New STMTS recursively define new STMTS.
            LexerBuilder* MakeLexerUseRecursiveBasedDS(LexerType_t lexerType_t, LanguageDefinition* langDef) const;
    };
}

#endif //DEAMER_LEXERGEN_LEXERFACTORY_H