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

#ifndef DEAMER_TOOL_TYPE_TOOL_H
#define DEAMER_TOOL_TYPE_TOOL_H

namespace deamer::tool::type
{
	/*!	\enum Tool
	 *
	 *	\brief Used to enumerate all available tools.
	 */
	enum class Tool
	{
		// Unknown
		Unknown,

		// Lexer
		Flex,
		Antlr_Lexer,
		Dleg,

		// Parser
		Bison,
		Antlr_Parser,
		Dparse,

		// AST generators
		DeamerAST,

		// External

		// Syntax Highlighter
		SyntaxHighlighter_UDL,		// used by notepad++
		SyntaxHighlighter_TextMate, // used by visual code, textmate

		// Documentation generators
		DeamerDocumentation,

		// Default application generators
		DeamerDefaultApplication,

		// Fuzzing Tools
		DeamerFuzzer,

		// DLDL Converter, generates DLDL definitions
		DLDLConverter,

		// OopSyntaxRecognizer, Used to recognize Oop Concepts via syntax
		OopSyntaxRecognizer,
	};
}

#endif // DEAMER_TOOL_TYPE_TOOL_H
