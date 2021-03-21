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

#ifndef DEAMER_FILE_TOOL_DATA_H
#define DEAMER_FILE_TOOL_DATA_H

#include <string>

namespace deamer::file::tool
{
	class Data
	{
	protected:
		std::string braces(const std::string& str) const
		{
			return '{' + str + '}';
		}

		std::string parenthesis(const std::string& str) const
		{
			return '(' + str + ')';
		}

	public:
		Data() = default;
		virtual ~Data() = default;

	public:
		virtual std::string Generate() const;
		virtual Data Parse(const std::string& data_) const;
	};
}

#endif // DEAMER_FILE_TOOL_DATA_H
