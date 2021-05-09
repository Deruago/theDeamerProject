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
		deamer::file::tool::OSType currentOs;
		std::string languageName;

		virtual void GenerateDirectory(const tool::Directory& directory,
									   const std::string& pathFromRoot);
		virtual void
		GenerateExternalDirectory(const std::string& pathFromRoot,
								  const tool::Directory& directory = tool::Directory());
		virtual void GenerateLibraryDirectory(const std::string& pathFromRoot,
											  const tool::Directory& directory = tool::Directory());
		virtual void GenerateIncludeDirectory(const std::string& pathFromRoot,
											  const tool::Directory& directory = tool::Directory());
		virtual void GenerateFile(const tool::File& file, const std::string& pathFromRoot);
		std::string CMakeListsHeader(const deamer::file::tool::Directory& directory);
		std::string CMakeListsHeader(const std::string& directory);

		virtual void FillDirectory(const tool::Directory& directory,
								   const std::string& libraryDirectory,
								   const std::string& directoryPath);

		void ExecuteDirectoryAction(const tool::Directory& directory,
									const std::string& directoryPath) const;
		tool::File InitialiseExternalCMakeLists();
		tool::File InitialiseLibraryCMakeLists();
		tool::File InitialiseIncludeCMakeLists();

		tool::File language_default_source_file();
		tool::File language_default_header_file();

	public:
		Compiler(const deamer::file::compiler::Output& compilerOutput_,
				 deamer::file::tool::OSType currentOs_ = tool::os_used);
		virtual ~Compiler() = default;

	public:
		void GenerateProjectCMakeLists(const std::string& compilerPath);
		virtual void Generate(const std::string& pathFromRoot = "./");

		std::vector<std::string> GetSubCompilerNames() const;
	};
}
#endif // DEAMER_FILE_GENERATE_COMPILER_H
