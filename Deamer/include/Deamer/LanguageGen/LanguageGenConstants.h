/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
 /*
  * Part of the DeamerProject.
  * For more information go to: https://github.com/Deruago/theDeamerProject
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
		none = 0,
    	empty = 1,
    	standard = 2,
    	grouped = 4,
    	vectorised = 8,
		recursive = 16,
		all = 32,
    };

	// This enum is used to define what kind of type a certain type is.
	// e.g we have types that are used for grouping types, start types and standard types
	enum class TokenType_t
	{
		none = 0,
		standard = 1,
		vector = 2,
		start = 4,
		grouped = 8,
		all = 16,
	};

	enum class TokenPermission_t
	{
		none = 0,
		node = 1,
		delete_ = 2,
		ignore = 4,
		all = 8,
	};

	enum class TypeContinuation_t
	{
		recursive,
		vector,
	};
}

#endif //DEAMER_LANGUAGEGEN_LANGUAGEGEN_CONSTANTS_H