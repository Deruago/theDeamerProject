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
#include "Deamer/Template/File/CPP/CMake/Miscel/Default/HeaderFile/HeaderFileTemplate.h"
#include "Deamer/Template/File/CPP/CMake/Miscel/Default/SourceFile/SourceFileTemplate.h"
#include "Deamer/Template/File/CPP/CMake/Multi/Lib/Deamer/DefaultDeamerTemplate.h"
#include "Deamer/Template/File/CPP/CMake/Multi/Main/Deamer/DefaultDeamerTemplate.h"
#include "Deamer/Template/File/CPP/CMake/Multi/Main/Default/DefaultUserTemplate.h"
#include "Deamer/Template/File/CPP/CMake/Single/Lib/Deamer/DefaultDeamerTemplate.h"
#include "Deamer/Template/File/CPP/CMake/Single/Main/Deamer/DefaultDeamerTemplate.h"
#include <filesystem>
#include <fstream>

deamer::file::generate::Compiler::Compiler(const deamer::file::compiler::Output& compilerOutput_)
	: compilerOutput(std::move(compilerOutput_)),
	  currentOs(compilerOutput.GetLanguageReference()
					.GetDefinition<language::type::definition::property::Type::Generation>()
					.GetOSTarget())
{
}

deamer::file::generate::Compiler::Compiler(const deamer::file::compiler::Output& compilerOutput_,
										   deamer::file::tool::OSType currentOs_)
	: compilerOutput(std::move(compilerOutput_)),
	  currentOs(currentOs_)
{
}

void deamer::file::generate::Compiler::Generate(const std::string& pathFromRoot)
{
	const auto& identity =
		compilerOutput.GetLanguageReference()
			.GetDefinition<language::type::definition::property::Type::Identity>();

	languageName = compilerOutput.GetLanguageReference()
					   .GetDefinition<language::type::definition::property::Type::Identity>()
					   .name->value;

	const auto compilerPath = pathFromRoot + identity.name->value + '/';
	std::filesystem::create_directory(compilerPath);

	auto cmakelists_external = InitialiseExternalCMakeLists();
	auto cmakelists_library = InitialiseLibraryCMakeLists();
	auto cmakelists_include = InitialiseIncludeCMakeLists();
	auto cmakelists_tests = InitialiseTestsCMakeLists();
	auto cmakelists_sources = InitialiseSourcesCMakeLists();

	auto standardDirectory = tool::Directory();
	standardDirectory.SetCMakeLists(tool::CMakeLists(
		"include(deamer.cmake)\n\n", "", tool::CMakeListsGenerationVariant::user_maintained,
		tool::GenerationLevel::Dont_generate_if_file_already_exists));
	// Generate standard directories.
	// These directories are always default generated.
	GenerateExternalDirectory(compilerPath, standardDirectory);
	GenerateLibraryDirectory(compilerPath, standardDirectory);
	GenerateIncludeDirectory(compilerPath);
	GenerateDocsDirectory(compilerPath);
	GenerateTestsDirectory(compilerPath, standardDirectory);
	GenerateSourcesDirectory(compilerPath, standardDirectory);

	for (const auto& languageOutput : compilerOutput.GetLanguageOutputs())
	{
		const auto externalDirectory = languageOutput.GetExternalDirectory();
		const auto libDirectory = languageOutput.GetLibraryDirectory();
		const auto includeDirectory = languageOutput.GetIncludeDirectory();
		const auto docsDirectory = languageOutput.GetDocsDirectory();
		const auto testsDirectory = languageOutput.GetTestsDirectory();
		const auto sourcesDirectory = languageOutput.GetSourcesDirectory();

		GenerateIfDirectoryIsNotUseless(&Compiler::GenerateExternalDirectory, compilerPath,
										externalDirectory);
		GenerateIfDirectoryIsNotUseless(&Compiler::GenerateLibraryDirectory, compilerPath,
										libDirectory);
		GenerateIfDirectoryIsNotUseless(&Compiler::GenerateIncludeDirectory, compilerPath,
										includeDirectory);
		GenerateIfDirectoryIsNotUseless(&Compiler::GenerateDocsDirectory, compilerPath,
										docsDirectory);
		GenerateIfDirectoryIsNotUseless(&Compiler::GenerateTestsDirectory, compilerPath,
										testsDirectory);
		GenerateIfDirectoryIsNotUseless(&Compiler::GenerateSourcesDirectory, compilerPath,
										sourcesDirectory);

		AddIfDirectoryIsNotUseless(cmakelists_external, externalDirectory,
								   "add_subdirectory(" + externalDirectory.GetThisDirectory() +
									   ")\n");
		AddIfDirectoryIsNotUseless(cmakelists_library, libDirectory,
								   "add_subdirectory(" + libDirectory.GetThisDirectory() + ")\n");
		AddIfDirectoryIsNotUseless(cmakelists_tests, testsDirectory,
								   "add_subdirectory(" + testsDirectory.GetThisDirectory() + ")\n");
		AddIfDirectoryIsNotUseless(cmakelists_sources, sourcesDirectory,
								   "add_subdirectory(" + sourcesDirectory.GetThisDirectory() +
									   ")\n");
	}

	GenerateProjectCMakeLists(compilerPath);
	GenerateFile(cmakelists_external, compilerPath + "extern/");
	GenerateFile(cmakelists_library, compilerPath + "lib/");
	GenerateFile(cmakelists_include, compilerPath + "include/");
	GenerateFile(cmakelists_tests, compilerPath + "tests/");
	GenerateFile(cmakelists_sources, compilerPath + "sources/");

	GenerateFile(language_default_source_file(), compilerPath + "lib/");
	GenerateFile(language_default_header_file(), compilerPath + "include/" + languageName + "/");

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

void deamer::file::generate::Compiler::GenerateExternalDirectory(const std::string& pathFromRoot,
																 const tool::Directory& directory)
{
	const auto externalDirectory = pathFromRoot + "extern/";
	const auto directoryPath = externalDirectory + directory.GetThisDirectory() + '/';

	FillDirectory(directory, externalDirectory, directoryPath);
}

void deamer::file::generate::Compiler::GenerateLibraryDirectory(const std::string& pathFromRoot,
																const tool::Directory& directory)
{
	const auto libraryDirectory = pathFromRoot + "lib/";
	const auto directoryPath = libraryDirectory + directory.GetThisDirectory() + '/';

	FillDirectory(directory, libraryDirectory, directoryPath);
}

void deamer::file::generate::Compiler::GenerateIncludeDirectory(const std::string& pathFromRoot,
																const tool::Directory& directory)
{
	const auto includeDirectory =
		pathFromRoot + "include/" +
		compilerOutput.GetLanguageReference()
			.GetDefinition<language::type::definition::property::Type::Identity>()
			.name->value +
		"/";
	const auto directoryPath = includeDirectory + directory.GetThisDirectory() + '/';

	FillDirectory(directory, includeDirectory, directoryPath);
}

void deamer::file::generate::Compiler::GenerateDocsDirectory(const std::string& pathFromRoot,
															 const tool::Directory& directory)
{
	const auto libraryDirectory = pathFromRoot + "docs/";
	const auto directoryPath = libraryDirectory + directory.GetThisDirectory() + '/';

	FillDirectory(directory, libraryDirectory, directoryPath);
}

void deamer::file::generate::Compiler::GenerateTestsDirectory(const std::string& pathFromRoot,
															  const tool::Directory& directory)
{
	const auto libraryDirectory = pathFromRoot + "tests/";
	const auto directoryPath = libraryDirectory + directory.GetThisDirectory() + '/';

	FillDirectory(directory, libraryDirectory, directoryPath);
}

void deamer::file::generate::Compiler::GenerateSourcesDirectory(const std::string& pathFromRoot,
																const tool::Directory& directory)
{
	const auto libraryDirectory = pathFromRoot + "sources/";
	const auto directoryPath = libraryDirectory + directory.GetThisDirectory() + '/';

	FillDirectory(directory, libraryDirectory, directoryPath);
}

void deamer::file::generate::Compiler::GenerateFile(const tool::File& file,
													const std::string& pathFromRoot)
{
	const auto filePath = pathFromRoot + file.GetCompleteFileName();

	if (file.GetGenerationLevel() == tool::GenerationLevel::Dont_generate_if_file_already_exists &&
		std::filesystem::exists(filePath) && !std::filesystem::is_empty(filePath))
	{
		return;
	}

	std::ofstream outputFile;
	outputFile.open(filePath);

	outputFile << file.FileContent();

	outputFile.close();
}

std::string
deamer::file::generate::Compiler::CMakeListsHeader(const deamer::file::tool::Directory& directory)
{
	return CMakeListsHeader(directory.GetThisDirectory());
}

std::string deamer::file::generate::Compiler::CMakeListsHeader(const std::string& directory)
{
	return "# This file is auto-generated and auto-maintained.\n"
		   "# Please don't change code in this file, as new changes will be "
		   "discarded,\n"
		   "# when Deamer regenerates the project.\n"
		   "#\n"
		   "# If you want to contribute to Deamer.\n"
		   "# Please visit: https://github.com/Deruago/theDeamerProject \n"
		   "#\n"
		   "# This file is part of the directory: " +
		   directory +
		   "\n"
		   "\n";
}

void deamer::file::generate::Compiler::FillDirectory(const deamer::file::tool::Directory& directory,
													 const std::string& libraryDirectory,
													 const std::string& directoryPath)
{
	std::filesystem::create_directories(libraryDirectory);
	std::filesystem::create_directory(directoryPath);

	for (const auto& file : directory.GetFiles())
	{
		GenerateFile(file, directoryPath);
	}

	const auto cmakelists = directory.GetCMakeLists();
	auto cmakelists_file = cmakelists.GetCMakeLists();

	if (cmakelists.IsDefault())
	{
		cmakelists_file += CMakeListsHeader(directory);
	}
	else if (cmakelists.IsUserMaintained())
	{
	}
	else
	{
		cmakelists_file =
			tool::CMakeLists(CMakeListsHeader(directory) + cmakelists_file.FileContent())
				.GetCMakeLists();
	}

	for (const auto& subDirectory : directory.GetDirectories())
	{
		cmakelists_file += "add_subdirectory(" + subDirectory.GetThisDirectory() + ")\n";
		FillDirectory(subDirectory, libraryDirectory,
					  directoryPath + subDirectory.GetThisDirectory() + '/');
	}

	GenerateFile(cmakelists_file, directoryPath);
	ExecuteDirectoryAction(directory, directoryPath);
}

void deamer::file::generate::Compiler::ExecuteDirectoryAction(
	const tool::Directory& directory, const std::string& directoryPath) const
{
	// as this is run on the platform installed, we require to use the global
	// deamer::file::tool::os_used variable.
	const deamer::file::tool::Action action = directory.GetAction(deamer::file::tool::os_used);
	const std::string console_action =
		action.GetSubShellAction(deamer::file::tool::os_used, directoryPath);
	const char* console_action_char_ptr = console_action.c_str();

	std::system(console_action_char_ptr);
}
#include <iostream>
std::string deamer::file::generate::Compiler::GetRootLanguageName() const
{
	const auto* currentCompilerOutput = &compilerOutput;
	while (currentCompilerOutput->GetParent().has_value() &&
		   currentCompilerOutput->GetParent().value() != nullptr)
	{
		currentCompilerOutput = currentCompilerOutput->GetParent().value();
	}

	return currentCompilerOutput->GetLanguageReference()
		.GetDefinition<language::type::definition::property::Type::Identity>()
		.name->value;
}

bool deamer::file::generate::Compiler::RootProject() const
{
	return !compilerOutput.GetParent().has_value();
}

void deamer::file::generate::Compiler::GenerateProjectCMakeLists(const std::string& compilerPath)
{
	if (SingleProject())
	{
		auto deamerProjectFileTemplate =
			deamer::templates::cmake::single::main::DefaultDeamerTemplate();
		deamerProjectFileTemplate.languageName_->Set(languageName);
		deamerProjectFileTemplate.root_language_name_->Set(GetRootLanguageName());
		if (!RootProject())
		{
			deamerProjectFileTemplate.optional_root_external_library_->Set("");
		}

		const auto names = GetSubCompilerNames();

		for (const auto& name : names)
		{
			deamerProjectFileTemplate.subproject_name_->Set(name);
			deamerProjectFileTemplate.add_subdirectory_sub_compiler_->ExpandVariableField();
		}

		// This file is always autogenerated, and is safe to be auto generated.
		const tool::File deamerCMake("deamer", "cmake", deamerProjectFileTemplate.GetOutput(),
									 tool::GenerationLevel::Always_regenerate);

		GenerateFile(deamerCMake, compilerPath);
	}
	else
	{
		auto deamerProjectFileTemplate =
			deamer::templates::cmake::multi::main::DefaultDeamerTemplate();
		deamerProjectFileTemplate.languageName_->Set(languageName);

		const auto names = GetSubCompilerNames();

		for (const auto& name : names)
		{
			deamerProjectFileTemplate.subproject_name_->Set(name);
			deamerProjectFileTemplate.add_subdirectory_sub_compiler_->ExpandVariableField();
		}

		// This file is always autogenerated, and is safe to be auto generated.
		const tool::File deamerCMake("deamer", "cmake", deamerProjectFileTemplate.GetOutput(),
									 tool::GenerationLevel::Always_regenerate);

		GenerateFile(deamerCMake, compilerPath);
	}

	auto userProjectFileTemplate = deamer::templates::cmake::multi::main::DefaultUserTemplate();
	userProjectFileTemplate.languageName_->Set(languageName);
	const tool::File file("CMakeLists", "txt", userProjectFileTemplate.GetOutput(),
						  tool::GenerationLevel::Dont_generate_if_file_already_exists);

	GenerateFile(file, compilerPath);
}

deamer::file::tool::File deamer::file::generate::Compiler::InitialiseExternalCMakeLists()
{
	return tool::CMakeLists(CMakeListsHeader("extern"), "",
							tool::CMakeListsGenerationVariant::user_excluded)
		.GetCMakeLists();
}

deamer::file::tool::File deamer::file::generate::Compiler::InitialiseLibraryCMakeLists()
{
	if (SingleProject())
	{
		auto deamerProjectFileTemplate =
			deamer::templates::cmake::single::lib::DefaultDeamerTemplate();
		deamerProjectFileTemplate.languageName_->Set(languageName);
		deamerProjectFileTemplate.root_language_name_->Set(GetRootLanguageName());
		if (RootProject())
		{
			deamerProjectFileTemplate.optional_if_not_root_alias_target_->Set("");
		}

		return tool::File("deamer", "cmake", deamerProjectFileTemplate.GetOutput(),
						  tool::GenerationLevel::Always_regenerate);
	}
	else
	{
		auto deamerProjectFileTemplate =
			deamer::templates::cmake::multi::lib::DefaultDeamerTemplate();
		deamerProjectFileTemplate.languageName_->Set(languageName);

		return tool::File("deamer", "cmake", deamerProjectFileTemplate.GetOutput(),
						  tool::GenerationLevel::Always_regenerate);
	}
}

deamer::file::tool::File deamer::file::generate::Compiler::InitialiseIncludeCMakeLists()
{
	return tool::CMakeLists(CMakeListsHeader("include"), "",
							tool::CMakeListsGenerationVariant::user_excluded)
		.GetCMakeLists();
}

deamer::file::tool::File deamer::file::generate::Compiler::InitialiseTestsCMakeLists()
{
	return tool::CMakeLists(CMakeListsHeader("tests"), "",
							tool::CMakeListsGenerationVariant::user_excluded)
		.GetCMakeLists();
}

deamer::file::tool::File deamer::file::generate::Compiler::InitialiseSourcesCMakeLists()
{
	return tool::CMakeLists(CMakeListsHeader("sources"), "",
							tool::CMakeListsGenerationVariant::user_excluded)
		.GetCMakeLists();
}

deamer::file::tool::File deamer::file::generate::Compiler::language_default_source_file()
{
	auto standardSourceFileTemplate =
		deamer::templates::cmake::miscel::standard::SourceFileTemplate();
	standardSourceFileTemplate.languageName_->Set(languageName);

	return tool::File(languageName, "cpp", standardSourceFileTemplate.GetOutput());
}

deamer::file::tool::File deamer::file::generate::Compiler::language_default_header_file()
{
	auto standardHeaderFileTemplate =
		deamer::templates::cmake::miscel::standard::HeaderFileTemplate();
	standardHeaderFileTemplate.languageName_->Set(languageName);

	return tool::File(languageName, "h", standardHeaderFileTemplate.GetOutput());
}

std::vector<std::string> deamer::file::generate::Compiler::GetSubCompilerNames() const
{
	std::vector<std::string> names;
	for (auto& compiler : compilerOutput.GetCompilerOutputs())
	{
		names.push_back(compiler.GetLanguageReference()
							.GetDefinition<language::type::definition::property::Type::Identity>()
							.name->value);
	}

	return names;
}

void deamer::file::generate::Compiler::SetProjectType(ProjectType projectType_)
{
	projectType = projectType_;
}

bool deamer::file::generate::Compiler::SingleProject() const
{
	return projectType == ProjectType::single;
}

void deamer::file::generate::Compiler::GenerateIfDirectoryIsNotUseless(
	void (Compiler::*generateDirectory)(const std::string&, const tool::Directory&),
	const std::string& path, const tool::Directory& directory)
{
	if (!directory.Useless())
	{
		(this->*generateDirectory)(path, directory);
	}
}

void deamer::file::generate::Compiler::AddIfDirectoryIsNotUseless(tool::File& file,
																  const tool::Directory& directory,
																  const std::string& text)
{
	if (!directory.Useless())
	{
		file += text;
	}
}
