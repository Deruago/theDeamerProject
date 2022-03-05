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

#ifndef DEAMER_FILE_TOOL_ACTION_COMMAND_H
#define DEAMER_FILE_TOOL_ACTION_COMMAND_H

#include "Deamer/File/Tool/Action/CommandTarget.h"
#include "Deamer/File/Tool/Action/CommandType.h"
#include "Deamer/File/Tool/OSType.h"
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace deamer::file::tool::action
{
	/*! \class Command
	 *	\brief Defines a base command
	 */
	class Command
	{
	private:
		CommandType commandType;

	public:
		Command(CommandType commandType_);
		virtual ~Command() = default;

	public:
		virtual std::string CompileArgument(CommandTarget commandTarget) = 0;
		virtual std::unique_ptr<Command> Copy() = 0;

	public:
		CommandType GetCommandType() const;

	public:
		/*!	\fn PythonCommand
		 *	\brief Converts command to proper Python command
		 */
		std::string PythonCommand(const std::string& command) const;
	};
}

#endif // DEAMER_FILE_TOOL_ACTION_COMMAND_H
