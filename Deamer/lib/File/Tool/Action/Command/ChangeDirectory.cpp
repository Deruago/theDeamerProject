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

#include "Deamer/File/Tool/Action/Command/ChangeDirectory.h"

deamer::file::tool::action::ChangeDirectory::ChangeDirectory(const std::string& lhsPath_)
	: Command(CommandType::change_directory),
	  lhsPath(lhsPath_)
{
}

std::string
deamer::file::tool::action::ChangeDirectory::CompileArgument(CommandTarget commandTarget)
{
	switch (commandTarget)
	{
	case CommandTarget::unknown: {
		return "";
	}
	case CommandTarget::os_linux: {
		return "cd \"" + lhsPath + "\"";
	}
	case CommandTarget::python: {
		return PythonCommand("any CD \"" + lhsPath + "\"");
	}
	case CommandTarget::os_windows: {
		return "cd \"" + lhsPath + "\"";
	}
	case CommandTarget::os_mac: {
		return "cd \"" + lhsPath + "\"";
	}
	}

	return "";
}

std::unique_ptr<deamer::file::tool::action::Command>
deamer::file::tool::action::ChangeDirectory::Copy()
{
	auto newCommand = std::make_unique<ChangeDirectory>(lhsPath);
	return std::move(newCommand);
}
