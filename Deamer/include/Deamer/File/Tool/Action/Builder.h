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

#ifndef DEAMER_FILE_TOOL_ACTION_BUILDER_H
#define DEAMER_FILE_TOOL_ACTION_BUILDER_H

#include "Deamer/File/Tool/Action/Action.h"
#include "Deamer/File/Tool/Action/Command/PlatformDependentCommand.h"
#include "Deamer/File/Tool/Action/Setting.h"
#include "Deamer/File/Tool/OSType.h"
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace deamer::file::tool::action
{
	/*! \class Builder
	 *	\brief Used to construct Arguments.
	 *
	 *	\details The Arguments constructed can utilize the cross platform Python console
	 *	Or utilize the Linux Compatibility modes.
	 */
	class Builder
	{
	private:
		std::vector<std::unique_ptr<Command>> commands;
		OSType used_os;

	public:
		std::unique_ptr<deamer::file::tool::action::Action> GetAction();

	public:
		Builder(OSType used_os_ = os_used);
		~Builder() = default;

	public:
		/*!	\fn SetupSetting
		 *	\brief Set ups some setting
		 *	\details Most settings can be changed between arguments.
		 *	There are settings which cannot be setup such as:
		 *		- our_os: Specifies the OS the python script is running from
		 */
		Builder& SetupSetting(Setting setting, const std::string& argument);

	public:
		/*!	\fn RemoveFile
		 *	\brief Removes a file at given "lhsPath"
		 *	\details If there is no file at "lhsPath" nothing is removed
		 */
		Builder& RemoveFile(const std::string& lhsPath);

		/*!	\fn MoveFile
		 *	\brief Moves a file at "lhsPath" to "rhsPath"
		 *	\details This will remove the file at "lhsPath", as it is moved to "rhsPath"
		 */
		Builder& MoveFile(const std::string& lhsPath, const std::string& rhsPath);

		/*!	\fn CopyFile
		 *	\brief Copies a file at "lhsPath" to "rhsPath"
		 *	\details If there is a file at "rhsPath" it will be overwritten with "lhsPath"
		 */
		Builder& CopyFile(const std::string& lhsPath, const std::string& rhsPath);

		/*!	\fn ChangeDirectory
		 *	\brief Changes the directory to "lhsPath"
		 *
		 *	\details
		 *	If the directory does not exists,
		 *	this will throw an Dangerous exception in the Python script.
		 */
		Builder& ChangeDirectory(const std::string& lhsPath);

		/*!	\fn CrossPlatformCommand
		 *	\brief Executes a cross platform command
		 */
		Builder& CrossPlatformCommand(const std::string& command);

		/*!	\fn RemoveDirectory
		 *	\brief Removes the directory at "lhsPath"
		 */
		Builder& RemoveDirectory(const std::string& lhsPath);

		/*!	\fn CreateDirectory
		 *	\brief Creates the directory at "lhsPath"
		 */
		Builder& CreateDirectory(const std::string& lhsPath);

		/*!	\fn PlatformSpecificCommand
		 *	\brief Executes a platform specific command
		 *
		 *	\details The command can only be executed on specific OSes, thus
		 *	if the current OS has not compatibility with the target OS.
		 *	The generator is platform dependent.
		 *
		 *	The List of PlatformDependentCommands are used to provide an dispatcher for
		 *	various OSes. Suppose there is a windows and linux variant of some command
		 *	The choices allow for automatically choosing the right command for some OS.
		 */
		Builder& PlatformSpecificCommand(
			std::vector<PlatformDependentCommand::PlatformDependentCommandMember>
				platformDependentCommands);
	};
}

#endif // DEAMER_FILE_TOOL_ACTION_BUILDER_H
