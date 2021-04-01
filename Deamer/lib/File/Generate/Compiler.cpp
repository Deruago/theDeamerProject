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

#include "Deamer/File/Generate/Compiler.h"
#include <filesystem>
#include <fstream>

deamer::file::generate::Compiler::Compiler(const deamer::file::compiler::Output& compilerOutput_)
	: compilerOutput(compilerOutput_)
{
}

void deamer::file::generate::Compiler::Generate(const std::string& pathFromRoot)
{
	const auto& identity =
		compilerOutput.GetLanguageReference()
			.GetDefinition<language::type::definition::property::Type::Identity>();

	const auto compilerPath = pathFromRoot + identity.name->value + '/';
	std::filesystem::create_directory(compilerPath);

	for (const auto& languageOutput : compilerOutput.GetLanguageOutputs())
	{
		const auto externalDirectory = languageOutput.GetExternalDirectory();
		const auto libDirectory = languageOutput.GetLibraryDirectory();
		const auto includeDirectory = languageOutput.GetIncludeDirectory();

		GenerateExternalDirectory(externalDirectory, compilerPath);
		GenerateLibraryDirectory(libDirectory, compilerPath);
		GenerateIncludeDirectory(includeDirectory, compilerPath);
	}

	for (const auto& compiler : compilerOutput.GetCompilerOutputs())
	{
		Compiler newCompiler(compiler);
		newCompiler.Generate(compilerPath);
	}
}

void deamer::file::generate::Compiler::GenerateDirectory(const tool::Directory& directory,
														 const std::string& pathFromRoot)
{
	const auto directoryPath = pathFromRoot + directory.GetThisDirectory() + '/';
	std::filesystem::create_directory(directoryPath);

	for (const auto& file : directory.GetFiles())
	{
		GenerateFile(file, directoryPath);
	}

	for (const auto& subDirectory : directory.GetDirectories())
	{
		GenerateDirectory(subDirectory, directoryPath);
	}
}

void deamer::file::generate::Compiler::GenerateExternalDirectory(const tool::Directory& directory,
																 const std::string& pathFromRoot)
{
	const auto externalDirectory = pathFromRoot + "extern/";
	const auto directoryPath = externalDirectory + directory.GetThisDirectory() + '/';

	FillDirectory(directory, externalDirectory, directoryPath);
}

void deamer::file::generate::Compiler::GenerateLibraryDirectory(const tool::Directory& directory,
																const std::string& pathFromRoot)
{
	const auto libraryDirectory = pathFromRoot + "lib/";
	const auto directoryPath = libraryDirectory + directory.GetThisDirectory() + '/';

	FillDirectory(directory, libraryDirectory, directoryPath);
}

void deamer::file::generate::Compiler::GenerateIncludeDirectory(const tool::Directory& directory,
																const std::string& pathFromRoot)
{
	const auto includeDirectory = pathFromRoot + "include/";
	const auto directoryPath = includeDirectory + directory.GetThisDirectory() + '/';

	FillDirectory(directory, includeDirectory, directoryPath);
}

void deamer::file::generate::Compiler::GenerateFile(const tool::File& file,
													const std::string& pathFromRoot)
{
	const auto filePath = pathFromRoot + file.GetCompleteFileName();

	std::ofstream outputFile;
	outputFile.open(filePath);

	outputFile << file.FileContent();

	outputFile.close();
}

void deamer::file::generate::Compiler::FillDirectory(const deamer::file::tool::Directory& directory,
													 const std::string& libraryDirectory,
													 const std::string& directoryPath)
{
	std::filesystem::create_directory(libraryDirectory);
	std::filesystem::create_directory(directoryPath);

	for (const auto& file : directory.GetFiles())
	{
		GenerateFile(file, directoryPath);
	}

	for (const auto& subDirectory : directory.GetDirectories())
	{
		GenerateDirectory(subDirectory, directoryPath);
	}
}
