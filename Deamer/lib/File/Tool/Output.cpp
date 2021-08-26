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

#include "Deamer/File/Tool/Output.h"

deamer::file::tool::Output::Output(const std::string& toolDirectory_)
	: toolDirectory(toolDirectory_),
	  external(Directory(toolDirectory_)),
	  include(Directory(toolDirectory_)),
	  library(Directory(toolDirectory_)),
	  docs(Directory(toolDirectory_)),
	  tests(Directory(toolDirectory_)),
	  sources(Directory(toolDirectory_))
{
}

void deamer::file::tool::Output::AddDirectoryToExternal(const Directory& newDirectory)
{
	external.AddDirectory(newDirectory);
}

void deamer::file::tool::Output::AddDirectoryToInclude(const Directory& newDirectory)
{
	include.AddDirectory(newDirectory);
}

void deamer::file::tool::Output::AddDirectoryToLibrary(const Directory& newDirectory)
{
	library.AddDirectory(newDirectory);
}

void deamer::file::tool::Output::AddDirectoryToDocs(const Directory& newDirectory)
{
	docs.AddDirectory(newDirectory);
}

void deamer::file::tool::Output::AddDirectoryToTests(const Directory& newDirectory)
{
	tests.AddDirectory(newDirectory);
}

void deamer::file::tool::Output::AddDirectoryToSources(const Directory& newDirectory)
{
	sources.AddDirectory(newDirectory);
}

void deamer::file::tool::Output::AddFileToExternal(const File& newFile)
{
	external.AddFile(newFile);
}

void deamer::file::tool::Output::AddFileToInclude(const File& newFile)
{
	include.AddFile(newFile);
}

void deamer::file::tool::Output::AddFileToLibrary(const File& newFile)
{
	library.AddFile(newFile);
}

void deamer::file::tool::Output::AddFileToDocs(const File& newFile)
{
	docs.AddFile(newFile);
}

void deamer::file::tool::Output::AddFileToTests(const File& newFile)
{
	tests.AddFile(newFile);
}

void deamer::file::tool::Output::AddFileToSources(const File& newFile)
{
	sources.AddFile(newFile);
}

void deamer::file::tool::Output::AddCMakeListsToExternal(const CMakeLists& newFile)
{
	external.SetCMakeLists(newFile.GetCMakeLists().FileContent());
}

void deamer::file::tool::Output::AddCMakeListsToInclude(const CMakeLists& newFile)
{
	include.SetCMakeLists(newFile.GetCMakeLists().FileContent());
}

void deamer::file::tool::Output::AddCMakeListsToLibrary(const CMakeLists& newFile)
{
	library.SetCMakeLists(newFile.GetCMakeLists().FileContent());
}

void deamer::file::tool::Output::AddActionToExternal(const deamer::file::tool::Action& action,
													 const deamer::file::tool::OSType os)
{
	external.AddAction(action, os);
}

void deamer::file::tool::Output::AddActionToInclude(const deamer::file::tool::Action& action,
													const deamer::file::tool::OSType os)
{
	include.AddAction(action, os);
}

void deamer::file::tool::Output::AddActionToLibrary(const deamer::file::tool::Action& action,
													const deamer::file::tool::OSType os)
{
	library.AddAction(action, os);
}

std::string deamer::file::tool::Output::GetToolDirectory() const
{
	return toolDirectory;
}

deamer::file::tool::Directory deamer::file::tool::Output::GetExternalDirectory() const
{
	return external;
}

deamer::file::tool::Directory deamer::file::tool::Output::GetIncludeDirectory() const
{
	return include;
}

deamer::file::tool::Directory deamer::file::tool::Output::GetLibraryDirectory() const
{
	return library;
}

deamer::file::tool::Directory deamer::file::tool::Output::GetDocsDirectory() const
{
	return docs;
}

deamer::file::tool::Directory deamer::file::tool::Output::GetTestsDirectory() const
{
	return tests;
}

deamer::file::tool::Directory deamer::file::tool::Output::GetSourcesDirectory() const
{
	return sources;
}

deamer::file::tool::Output deamer::file::tool::Output::Merge(const std::vector<Output>& outputs)
{
	if (outputs.empty())
	{
		throw std::logic_error("Outputs is empty.");
	}

	Output baseOutput = Output(outputs[0].toolDirectory);

	for (const auto& currentOutput : outputs)
	{
		baseOutput += currentOutput;
	}

	return baseOutput;
}

deamer::file::tool::Output& deamer::file::tool::Output::operator+=(const Output& output)
{
	if (&output == this)
	{
		return *this;
	}

	external += output.external;
	include += output.include;
	library += output.library;

	docs += output.docs;
	tests += output.tests;
	sources += output.sources;

	return *this;
}
