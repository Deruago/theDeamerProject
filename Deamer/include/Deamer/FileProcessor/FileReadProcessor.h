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

#ifndef DEAMER_FILEPROCESSOR_FILEREADPROCESSOR_H
#define DEAMER_FILEPROCESSOR_FILEREADPROCESSOR_H
#include "Deamer/Types/BitwiseEnum.h"
#include "Deamer/FileProcessor/FileRead_Passes.h"
#include <string>

/*
 * This class can be used to read in files and
 * process them using "passes". These passes modify partly
 * the input to make it easier to handle.
 *
 * This class focusses on simple changes.
 *
 * For example: converting indentation to curly bracket logic
 */

namespace deamer
{
	class FileReadProcessor
	{
	private:
		BitwiseEnum<FileRead_Passes> file_read_passes_;
	protected:
	public:
		FileReadProcessor() = default;
		FileReadProcessor(FileRead_Passes file_read_passes);
		std::string ReadFile(const std::string& file_location);
	};
}

#endif //DEAMER_FILEPROCESSOR_FILEREADPROCESSOR_H