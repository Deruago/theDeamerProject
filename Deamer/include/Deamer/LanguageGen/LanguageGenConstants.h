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
    enum class LexerType_t
    {
        dlex, //Deamer lexer. Currently unsupported
        flex
    };

    enum class ParserType_t
    {
        dparse, //Deamer parser. Currently unsupported
        bison
    };

	// This enum should be used to declare what type the rule is.
	// By changing the type parsers may implement different logic.
	// It is recommended to let analysers or dedicated functions handle this.
	enum class RuleType_t
    {
    	empty,
    	standard,
    	grouped,
    	vectorised
    };
}

#endif //DEAMER_LANGUAGEGEN_LANGUAGEGEN_CONSTANTS_H