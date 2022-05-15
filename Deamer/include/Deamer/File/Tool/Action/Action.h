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

#ifndef DEAMER_FILE_TOOL_ACTION_ACTION_H
#define DEAMER_FILE_TOOL_ACTION_ACTION_H

#include "Deamer/File/Tool/Action/Command.h"
#include "Deamer/File/Tool/OSType.h"
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace deamer::file::tool::action
{
	/*! \class Action
	 *	\brief Defines an Action
	 *	\details An Action contains various commands.
	 */
	class Action
	{
	private:
		std::vector<std::unique_ptr<Command>> commands;
		bool empty = true;
		OSType used_os;

	public:
		Action(OSType used_os_ = os_used);
		~Action() = default;

		Action(const Action& action);
		Action(Action&& action) noexcept;

	public:
		::deamer::file::tool::action::Action& operator+=(const Action& action);
		::deamer::file::tool::action::Action& operator+=(Action&& action) noexcept;

	public:
		std::string ConstructArgument(CommandTarget commandTarget,
									  const std::string& directoryPath = "./", bool force = false,
									  const std::string forceConsolePath = "") const;
		bool IsEmpty() const;

	public:
		void SetCommands(std::vector<std::unique_ptr<Command>> commands_);
		std::unique_ptr<Action> Copy() const;

	private:
		std::string ConstructPythonConsoleSpecialSettings(CommandTarget commandTarget) const;

		std::string ConstructForLinux(CommandTarget commandTarget, const std::string& commands,
									  const std::string forceConsolePath) const;
		std::string ConstructForWindows(CommandTarget commandTarget, const std::string& commands,
										const std::string forceConsolePath) const;
		std::string ConstructForMac(CommandTarget commandTarget, const std::string& commands,
									const std::string forceConsolePath) const;
	};
}

#endif // DEAMER_FILE_TOOL_ACTION_ACTION_H
