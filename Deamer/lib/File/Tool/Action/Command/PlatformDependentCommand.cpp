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

#include "Deamer/File/Tool/Action/Command/PlatformDependentCommand.h"
#include <utility>

deamer::file::tool::action::PlatformDependentCommand::PlatformDependentCommandMember::
	PlatformDependentCommandMember(::deamer::file::tool::OSType targetOS_, std::string command_)
	: targetOS(targetOS_),
	  command(command_)
{
}

deamer::file::tool::action::PlatformDependentCommand::PlatformDependentCommand(
	std::vector<PlatformDependentCommandMember> platformDependentCommands_)
	: Command(CommandType::platformdependentcommand),
	  platformDependentCommands(std::move(platformDependentCommands_))
{
}

std::string
deamer::file::tool::action::PlatformDependentCommand::CompileArgument(CommandTarget commandTarget)
{
	if constexpr (os_used == OSType::unknown)
	{
		throw std::logic_error("Unknown OS");
	}
	else if constexpr (os_used == OSType::os_linux)
	{
		return CompileLinuxArgument(commandTarget);
	}
	else if constexpr (os_used == OSType::os_windows)
	{
		return CompileWindowsArgument(commandTarget);
	}
	else if constexpr (os_used == OSType::os_mac)
	{
		return CompileMacArgument(commandTarget);
	}
	else
	{
		throw std::logic_error("Unknown OS");
	}
}

std::unique_ptr<deamer::file::tool::action::Command>
deamer::file::tool::action::PlatformDependentCommand::Copy()
{
	auto newCommand = std::make_unique<PlatformDependentCommand>(platformDependentCommands);
	return std::move(newCommand);
}

std::string deamer::file::tool::action::PlatformDependentCommand::CompileWindowsArgument(
	CommandTarget commandTarget) const
{
	if (commandTarget == CommandTarget::os_linux)
	{
		auto linuxCommand = GetLinuxCommand();
		if (!linuxCommand.has_value())
		{
			throw std::logic_error("No Conversion Possible");
		}

		return linuxCommand.value().command;
	}
	if (commandTarget == CommandTarget::os_mac)
	{
		throw std::logic_error("No Conversion Possible");
	}
	if (commandTarget == CommandTarget::os_windows)
	{
		auto windowsCommand = GetWindowsCommand();
		if (!windowsCommand.has_value())
		{
			throw std::logic_error("No Conversion Possible");
		}

		return windowsCommand.value().command;
	}
	if (commandTarget == CommandTarget::python)
	{
		auto windowsCommand = GetWindowsCommand();
		if (windowsCommand.has_value())
		{
			return PythonCommand("windows PCOMMAND " + windowsCommand.value().command);
		}

		auto linuxCommand = GetLinuxCommand();
		if (linuxCommand.has_value())
		{
			return PythonCommand("linux PCOMMAND " + linuxCommand.value().command);
		}
		throw std::logic_error("No Conversion Possible");
	}

	return "";
}

std::string deamer::file::tool::action::PlatformDependentCommand::CompileLinuxArgument(
	CommandTarget commandTarget) const
{
	if (commandTarget == CommandTarget::os_linux)
	{
		auto linuxCommand = GetLinuxCommand();
		if (!linuxCommand.has_value())
		{
			throw std::logic_error("No Conversion Possible");
		}

		return linuxCommand.value().command;
	}
	if (commandTarget == CommandTarget::os_mac)
	{
		throw std::logic_error("No Conversion Possible");
	}
	if (commandTarget == CommandTarget::os_windows)
	{
		throw std::logic_error("No Conversion Possible");
	}
	if (commandTarget == CommandTarget::python)
	{
		auto linuxCommand = GetLinuxCommand();
		if (linuxCommand.has_value())
		{
			return PythonCommand("linux PCOMMAND " + linuxCommand.value().command);
		}

		throw std::logic_error("No Conversion Possible");
	}

	return "";
}

std::string deamer::file::tool::action::PlatformDependentCommand::CompileMacArgument(
	CommandTarget commandTarget) const
{
	if (commandTarget == CommandTarget::os_linux)
	{
		throw std::logic_error("No Conversion Possible");
	}
	if (commandTarget == CommandTarget::os_mac)
	{
		auto macCommand = GetMacCommand();
		if (!macCommand.has_value())
		{
			throw std::logic_error("No Conversion Possible");
		}

		return macCommand.value().command;
	}
	if (commandTarget == CommandTarget::os_windows)
	{
		throw std::logic_error("No Conversion Possible");
	}
	if (commandTarget == CommandTarget::python)
	{
		auto macCommand = GetMacCommand();
		if (macCommand.has_value())
		{
			return PythonCommand("mac PCOMMAND " + macCommand.value().command);
		}

		throw std::logic_error("No Conversion Possible");
	}

	return "";
}

std::optional<deamer::file::tool::action::PlatformDependentCommand::PlatformDependentCommandMember>
deamer::file::tool::action::PlatformDependentCommand::GetLinuxCommand() const
{
	for (auto command : platformDependentCommands)
	{
		if (command.targetOS == OSType::os_linux)
		{
			return command;
		}
	}

	return std::nullopt;
}

std::optional<deamer::file::tool::action::PlatformDependentCommand::PlatformDependentCommandMember>
deamer::file::tool::action::PlatformDependentCommand::GetWindowsCommand() const
{
	for (auto command : platformDependentCommands)
	{
		if (command.targetOS == OSType::os_windows)
		{
			return command;
		}
	}

	return std::nullopt;
}

std::optional<deamer::file::tool::action::PlatformDependentCommand::PlatformDependentCommandMember>
deamer::file::tool::action::PlatformDependentCommand::GetMacCommand() const
{
	for (auto command : platformDependentCommands)
	{
		if (command.targetOS == OSType::os_mac)
		{
			return command;
		}
	}

	return std::nullopt;
}
