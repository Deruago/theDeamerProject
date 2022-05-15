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

#include "Deamer/File/Tool/Action/Command/SettingCommand.h"

deamer::file::tool::action::SettingCommand::SettingCommand(Setting setting_,
														   const std::string& argument_)
	: Command(CommandType::setup_setting),
	  setting(setting_),
	  argument(argument_)
{
}

std::string deamer::file::tool::action::SettingCommand::CompileArgument(CommandTarget commandTarget)
{
	switch (commandTarget)
	{
	case CommandTarget::unknown: {
		return "";
	}
	case CommandTarget::os_linux: {
		return "";
	}
	case CommandTarget::python: {
		return PythonCommand("SETTING " + GetSettingName() + " \"" + argument + "\"");
	}
	case CommandTarget::os_windows: {
		return "";
	}
	case CommandTarget::os_mac: {
		return "";
	}
	}

	return "";
}

std::unique_ptr<deamer::file::tool::action::Command>
deamer::file::tool::action::SettingCommand::Copy()
{
	auto newCommand = std::make_unique<SettingCommand>(setting, argument);
	return std::move(newCommand);
}

std::string deamer::file::tool::action::SettingCommand::GetSettingName() const
{
	switch (setting)
	{
	case Setting::unknown: {
		return "unknown";
	}
	case Setting::dangerous: {
		return "DANGEROUS";
	}
	case Setting::our_os: {
		return "OUR_OS";
	}
	case Setting::target_os: {
		return "THEIR_OS";
	}
	}

	return "unknown";
}
