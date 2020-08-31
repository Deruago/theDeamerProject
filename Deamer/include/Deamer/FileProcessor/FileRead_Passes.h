/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
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