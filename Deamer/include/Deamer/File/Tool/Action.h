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

#ifndef DEAMER_FILE_TOOL_ACTION_H
#define DEAMER_FILE_TOOL_ACTION_H

#include "Deamer/File/Tool/OSType.h"
#include <stdexcept>
#include <string>
#include <utility>

namespace deamer::file::tool
{
	class Action
	{
	private:
		std::string action;

	public:
		Action(std::string action_ = "") : action(std::move(action_))
		{
		}

		~Action() = default;

	public:
		const std::string& GetAction() const
		{
			return action;
		}

		std::string GetSubShellAction(const file::tool::OSType os, const std::string& directory = "./") const
		{
			switch (os)
			{
			case file::tool::OSType::unknown:
			case file::tool::OSType::all:
			case file::tool::OSType::os_linux:
				return "( cd " + directory + " ; " + GetAction() + " )";
			case file::tool::OSType::os_windows:
				return "bash -c \"( cd " + directory + " ; " + GetAction() + " )\"";
			case file::tool::OSType::os_mac:
				return "( cd " + directory + " ; " + GetAction() + " )";
			}

			throw std::logic_error("Unknown os given");
		}
	};
}

#endif // DEAMER_FILE_TOOL_ACTION_H