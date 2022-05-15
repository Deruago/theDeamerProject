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

#include "Deamer/File/Tool/Action/Command.h"

deamer::file::tool::action::Command::Command(CommandType commandType_) : commandType(commandType_)
{
}

deamer::file::tool::action::CommandType deamer::file::tool::action::Command::GetCommandType() const
{
	return commandType;
}

std::string deamer::file::tool::action::Command::PythonCommand(const std::string& command) const
{
	std::string formatted = "\"";
	for (auto character : command)
	{
		if (character == '"')
		{
			formatted += "\\\"";
		}
		else if (character == '\\')
		{
			formatted += "\\";
		}
		else
		{
			formatted += character;
		}
	}
	formatted += "\"";
	return formatted;
}
