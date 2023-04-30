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

#ifndef DEAMER_TYPE_FILE_TEMPORARYFILE_H
#define DEAMER_TYPE_FILE_TEMPORARYFILE_H

#include <string>

namespace deamer::type
{
	/*!	\class TemporaryFile
	 *
	 *	\brief Creates a Temporary File upon creation, and deletes it upon destruction.
	 *
	 *	\note The name follows the regular expression: dtemp_[a-z0-9]{1,13}
	 *
	 *	\warning If the user terminates the program while a temporary file is created
	 *	The temporary file may not be properly deleted.
	 *	It is thus advised to make temporary files short lived.
	 *	I.e. construct and immediately use it, then destruct it when you are done.
	 *
	 *	\warning This has various Security Flaws.
	 */
	class [[deprecated]] TemporaryFile
	{
	private:
		std::string temporaryFileName;

	public:
		TemporaryFile();
		~TemporaryFile();

	public:
		TemporaryFile(const TemporaryFile& rhs) = delete;
		TemporaryFile(TemporaryFile&& rhs) = delete;

		TemporaryFile& operator=(const TemporaryFile& rhs) = delete;
		TemporaryFile& operator=(TemporaryFile&& rhs) = delete;

	public:
		TemporaryFile& operator=(const std::string& rhs);
		TemporaryFile& operator+=(const std::string& rhs);

	public:
		void Fill(const std::string& text);
		void Append(const std::string& text);

		std::string GetContent();

		std::string GetRelativePath();

		std::string GetFileName();

	private:
		std::string GenerateTemporaryFileName();
	};
}

#endif // DEAMER_TYPE_FILE_TEMPORARYFILE_H
