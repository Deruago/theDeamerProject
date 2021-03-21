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

#ifndef DEAMER_EXTERNAL_LEXER_TERMINALOBJECT_H
#define DEAMER_EXTERNAL_LEXER_TERMINALOBJECT_H

#include <string>
#include <utility>

namespace deamer::external::lexer
{
	/*!	\class TerminalObject
	 *
	 *	\brief This class is used to contain data about parsed Terminals, in the lexer stage.
	 */
	class TerminalObject
	{
	public:
		const std::string Value;
		const int LineNumber;
		const int ColumnNumber;

	public:
		TerminalObject(std::string value_, const int lineNumber_ = -1, const int columnNumber_ = -1)
			: Value(std::move(value_)),
			  LineNumber(lineNumber_),
			  ColumnNumber(columnNumber_)
		{
		}
		~TerminalObject() = default;
	};
}

#endif // DEAMER_EXTERNAL_LEXER_TERMINALOBJECT_H
