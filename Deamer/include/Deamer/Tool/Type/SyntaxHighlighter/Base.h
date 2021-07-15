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

#ifndef DEAMER_TOOL_TYPE_SYNTAXHIGHLIGHTER_BASE_H
#define DEAMER_TOOL_TYPE_SYNTAXHIGHLIGHTER_BASE_H

#include "Deamer/Tool/Type/Base.h"

namespace deamer::tool::type::syntaxhighlighter
{
	class Base : ::deamer::tool::type::Base
	{
	public:
		Base(Tool tool_) : type::Base(tool_)
		{
		}
	};
}

#endif // DEAMER_TOOL_TYPE_SYNTAXHIGHLIGHTER_BASE_H