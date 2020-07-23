/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
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

	// This enum should be used to declare what type the rule is.
	// By changing the type parsers may implement different logic.
	// It is recommended to let analysers or dedicated functions handle this.
	typedef enum class RuleType_s
    {
    	empty,
    	standard,
    	grouped,
    	vectorised
    } RuleType_t;
}

#endif //DEAMER_LANGUAGEGEN_LANGUAGEGEN_CONSTANTS_H