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

#ifndef DEAMER_FILE_GENERATE_COMPILER_H
#define DEAMER_FILE_GENERATE_COMPILER_H

#include "Deamer/File/Compiler/Output.h"
#include "Deamer/Language/Reference/PropertyDefinition.h"

namespace deamer::file::generate
{
	/*!	\class Compiler
	 *
	 *	\brief This class is used to generate multi compilers, given a multi compiler output object.
	 *
	 *	\details This generates the multi compiler to disk.
	 *	Its code is virtual, meaning that users can override the generation process completely.
	 */
	class Compiler
	{
	private:
		const deamer::file::compiler::Output compilerOutput;

		virtual void GenerateDirectory(const tool::Directory& directory,
									   const std::string& pathFromRoot);
		virtual void GenerateExternalDirectory(const tool::Directory& directory,
											   const std::string& pathFromRoot);
		virtual void GenerateLibraryDirectory(const tool::Directory& directory,
											  const std::string& pathFromRoot);
		virtual void GenerateIncludeDirectory(const tool::Directory& directory,
											  const std::string& pathFromRoot);
		virtual void GenerateFile(const tool::File& file, const std::string& pathFromRoot);

	public:
		Compiler(const deamer::file::compiler::Output& compilerOutput_);
		virtual ~Compiler() = default;

	public:
		virtual void Generate(const std::string& pathFromRoot = "./");
	};
}
#endif // DEAMER_FILE_GENERATE_COMPILER_H
