/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -June 2020 Thimo B�hmer
 * -July 2020 Thimo B�hmer
 */

#ifndef DEAMER_LANGUAGEGEN_LANGUAGEGEN_CONSTANTS_H
#define DEAMER_LANGUAGEGEN_LANGUAGEGEN_CONSTANTS_H

namespace deamer
{
    typedef enum class LexerType_s
    {
        dlex, //Deamer lexer. Currently unsupported
        flex
    } LexerType_t;

    typedef enum class ParserType_s
    {
        dparse, //Deamer parser. Currently unsupported
        bison
    } ParserType_t;
}

#endif //DEAMER_LANGUAGEGEN_LANGUAGEGEN_CONSTANTS_H