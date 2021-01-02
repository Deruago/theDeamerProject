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

#ifndef DEAMER_FILEPROCESSOR_FILEREAD_PASSES_H
#define DEAMER_FILEPROCESSOR_FILEREAD_PASSES_H

namespace deamer
{
	/*
	 * This enum is used to define which passes you want
	 * to use in file processing.
	 */
	enum class FileRead_Passes
	{
		replace_indent_by_curly_brackets = 1,
		add_curly_brackets_to_lines_followed_by_lines_on_same_level = 2,
		add_newline_to_end_file = 4,
		all = 0b11111111,
	};
}

#endif //DEAMER_FILEPROCESSOR_FILEREAD_PASSES_H