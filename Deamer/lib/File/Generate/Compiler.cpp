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
	: compilerOutput(compilerOutput_),
	  currentOs(compilerOutput_.GetLanguageReference()
					.GetDefinition<language::type::definition::property::Type::Generation>()
					.GetOSTarget())
{
}

deamer::file::generate::Compiler::Compiler(const deamer::file::compiler::Output& compilerOutput_,
										   deamer::file::tool::OSType currentOs_)
	: compilerOutput(compilerOutput_),
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

void deamer::file::generate::Compiler::GenerateProjectCMakeLists(const std::string& compilerPath)
{
	const auto names = GetSubCompilerNames();

	std::string add_subdirectory_sub_compilers;
	for (const auto& name : names)
	{
		add_subdirectory_sub_compilers += "add_subdirectory(" + name + ")\n";
	}

	const std::string cmakelists_content =
		"cmake_minimum_required(VERSION 3.18)\n"
		"\n"
		"project(" +
		languageName +
		")\n"
		"\n"
		"find_package(Deamer_External REQUIRED)\n"
		"\n" +
		"include(deamer.cmake)\n"
		"\n"
		"add_subdirectory(extern)\n"
		"add_subdirectory(lib)\n"
		"\n"
		"option(TESTS \"Enables all the tests\" ON)\n"
		"if(TESTS)\n"
		"	message(STATUS \"Tests are now available.\")\n"
		"	add_subdirectory(tests)\n"
		"endif()\n"
		"\n"
		"option(APPLICATIONS \"Enables all the applications\" ON)\n"
		"if(APPLICATIONS)\n"
		"	message(STATUS \"Applications are now available.\")\n"
		"	add_subdirectory(sources)\n"
		"endif()\n"
		"\n";

	const tool::File file("CMakeLists", "txt", cmakelists_content,
						  tool::GenerationLevel::Dont_generate_if_file_already_exists);

	GenerateFile(file, compilerPath);

	const std::string deamerCMake_content =
		"# This file is auto-generated and auto-maintained.\n"
		"# Please don't change code in this file, as new changes will be "
		"discarded,\n"
		"# when Deamer regenerates the project.\n"
		"#\n"
		"# If you want to contribute to Deamer.\n"
		"# Please visit: https://github.com/Deruago/theDeamerProject \n"
		"\n"
		"find_package(Deamer_External REQUIRED)\n"
		"\n" +
		add_subdirectory_sub_compilers +
		"\n"
		"add_library(" +
		languageName + "_external_libraries STATIC \"${" + languageName + "_SOURCE_DIR}/lib/" +
		languageName +
		".cpp\")\n"
		"target_link_libraries(" +
		languageName +
		"_external_libraries PUBLIC Deamer_External)\n"
		"target_include_directories(" +
		languageName +
		"_external_libraries PUBLIC "
		"\"${" +
		languageName + "_SOURCE_DIR}/extern\" \"${" + languageName +
		"_SOURCE_DIR}/include\")\n"
		"\n"
		"function(" +
		languageName +
		"_add_external_library external_library_name source_files)\n"
		"\tset(external_library_full_name \"" +
		languageName +
		"_${external_library_name}_static_library\")\n"
		"\n"
		"\tadd_library(${external_library_full_name} STATIC ${source_files})\n"
		"\n"
		"\ttarget_link_libraries(${external_library_full_name} PUBLIC Deamer_External)\n"
		"\ttarget_include_directories(${external_library_full_name} PRIVATE \"${" +
		languageName + "_SOURCE_DIR}/extern\" \"${" + languageName +
		"_SOURCE_DIR}/include\")\n"
		"\ttarget_compile_features(${external_library_full_name} PUBLIC cxx_std_17)\n"
		"\tset_target_properties(${external_library_full_name} PROPERTIES LINKED_LANGUAGE CXX)\n"
		"\tset_property(TARGET ${external_library_full_name} PROPERTY POSITION_INDEPENDENT_CODE "
		"ON)\n"
		"\t\n"
		"\ttarget_link_libraries(" +
		languageName +
		"_external_libraries PUBLIC ${external_library_full_name})\n"
		"\t\n"
		"endfunction()\n"
		"\n";

	// This file is always autogenerated, and is safe to be auto generated.
	const tool::File deamerCMake("deamer", "cmake", deamerCMake_content,
								 tool::GenerationLevel::Always_regenerate);

	GenerateFile(deamerCMake, compilerPath);
}

deamer::file::tool::File deamer::file::generate::Compiler::InitialiseExternalCMakeLists()
{
	return tool::CMakeLists(CMakeListsHeader("extern"), "",
							tool::CMakeListsGenerationVariant::user_excluded)
		.GetCMakeLists();
}

deamer::file::tool::File deamer::file::generate::Compiler::InitialiseLibraryCMakeLists()
{
	const std::string library_get_source_files = "file(GLOB_RECURSE SOURCE_LIST \"${" +
												 languageName +
												 "_SOURCE_DIR}/lib/*.cpp\")\n"
												 "\n";
	const std::string library_cmakelists_static_library_content =
		"add_library(" + languageName +
		"_static_library STATIC ${SOURCE_LIST})\n"
		"\n"
		"target_include_directories(" +
		languageName + "_static_library PUBLIC \"${" + languageName + "_SOURCE_DIR}/extern\" \"${" +
		languageName +
		"_SOURCE_DIR}/include\")\n"
		"target_compile_features(" +
		languageName +
		"_static_library PUBLIC cxx_std_17)\n"
		"set_target_properties(" +
		languageName +
		"_static_library PROPERTIES LINKER_LANGUAGE CXX)\n"
		"\n"
		"target_link_libraries(" +
		languageName + "_static_library PUBLIC " + languageName +
		"_external_libraries)\n"
		"\n";

	const std::string library_cmakelists_shared_library_content =
		"add_library(" + languageName +
		"_shared_library SHARED ${SOURCE_LIST})\n"
		"\n"
		"target_include_directories(" +
		languageName + "_shared_library PUBLIC \"${" + languageName + "_SOURCE_DIR}/extern\" \"${" +
		languageName +
		"_SOURCE_DIR}/include\")\n"
		"target_compile_features(" +
		languageName +
		"_shared_library PUBLIC cxx_std_17)\n"
		"set_target_properties(" +
		languageName +
		"_shared_library PROPERTIES LINKER_LANGUAGE CXX)\n"
		"\n"
		"target_link_libraries(" +
		languageName + "_shared_library PUBLIC " + languageName +
		"_external_libraries)\n"
		"\n";

	return tool::CMakeLists(CMakeListsHeader("lib") + library_get_source_files +
								library_cmakelists_static_library_content +
								library_cmakelists_shared_library_content,
							"", tool::CMakeListsGenerationVariant::user_excluded)
		.GetCMakeLists();
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
	const std::string source_code = "#include \"" + languageName + "/" + languageName +
									".h\"\n"
									"\n"
									"// This is a generated file for the language: " +
									languageName + "\n";

	return tool::File(languageName, "cpp", source_code);
}

deamer::file::tool::File deamer::file::generate::Compiler::language_default_header_file()
{
	const std::string source_code = "#ifndef " + languageName + "_" + languageName +
									"_H\n"
									"#define " +
									languageName + "_" + languageName +
									"_H\n"
									"\n"
									"// This is a generated file for the language: " +
									languageName +
									"\n"
									"\n"
									"namespace " +
									languageName +
									"\n"
									"{\n"
									"}\n"
									"\n"
									"#endif // " +
									languageName + "_" + languageName + "_H\n";

	return tool::File(languageName, "h", source_code);
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
