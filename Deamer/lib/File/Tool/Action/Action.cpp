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

#include "Deamer/File/Tool/Action/Action.h"
#include "Deamer/File/Tool/Action/Command/ChangeDirectory.h"
#include "Deamer/File/Tool/Directory.h"
#include "Deamer/File/Tool/LoadFilesystem.h"
#include <iostream>

static bool loadedDeamerDir = false;
static bool deamerDirExists = false;
static std::string consoleLocation = "./";

static void LoadInDeamerDir()
{
	deamer::file::tool::Directory dir;
	auto loader = deamer::file::tool::LoadFilesystem(dir);
	while (!loader.DirectContainsDirectory(".deamer") && !loader.ReachedRoot())
	{
		loader.Upper();
	}
	if (loader.ReachedRoot())
	{
		return;
	}
	loader.Enter(".deamer").Enter("dldl").Enter("scripts").DirectLoad();

	bool exists = false;
	for (const auto& file : dir.GetFiles())
	{
		if (file.GetFilename() == "Console" && file.GetExtension() == "py")
		{
			exists = true;
			break;
		}
	}

	consoleLocation = loader.GetPath() + "Console.py";
	deamerDirExists = exists;
}

static bool CheckIfConsoleScriptIsAvailable()
{
	if (!loadedDeamerDir)
	{
		loadedDeamerDir = true;
		LoadInDeamerDir();
	}

	return deamerDirExists;
}

static std::string GetPathToConsoleScript()
{
	return consoleLocation;
}

deamer::file::tool::action::Action::Action(OSType used_os_) : used_os(used_os_)
{
}

deamer::file::tool::action::Action::Action(const Action& action)
{
	if (&action == this)
	{
		return;
	}

	this->empty = action.empty;
	this->used_os = action.used_os;
	for (const auto& command : action.commands)
	{
		commands.push_back(command->Copy());
	}
}

deamer::file::tool::action::Action::Action(Action&& action) noexcept
{
	if (&action == this)
	{
		return;
	}

	this->empty = action.empty;
	this->used_os = action.used_os;
	this->commands = std::move(action.commands);
}

::deamer::file::tool::action::Action&
deamer::file::tool::action::Action::operator+=(const Action& action)
{
	if (&action == this)
	{
		return *this;
	}

	this->empty &= action.empty;
	for (const auto& command : action.commands)
	{
		this->commands.push_back(command->Copy());
	}

	return *this;
}

::deamer::file::tool::action::Action&
deamer::file::tool::action::Action::operator+=(Action&& action) noexcept
{
	if (&action == this)
	{
		return *this;
	}

	this->empty &= action.empty;
	for (auto& command : action.commands)
	{
		this->commands.push_back(std::move(command));
	}

	return *this;
}

std::string deamer::file::tool::action::Action::ConstructArgument(CommandTarget commandTarget,
																  const std::string& directoryPath,
																  bool force) const
{
	if (commandTarget == CommandTarget::python && !force)
	{
		if (!CheckIfConsoleScriptIsAvailable())
		{
			commandTarget = CommandTarget::os_linux; // Linux compatibility mode is default behavior
													 // of Deamer CC
		}
	}

	auto dirChange = std::make_unique<ChangeDirectory>(directoryPath);
	std::string commandList = dirChange->CompileArgument(commandTarget);
	for (const auto& command : commands)
	{
		switch (commandTarget)
		{
		case CommandTarget::unknown:
		case CommandTarget::python: {
			commandList += " ";
			break;
		}
		case CommandTarget::os_windows: {
			commandList += " && ";
			break;
		}
		case CommandTarget::os_linux:
		case CommandTarget::os_mac: {
			commandList += " ; ";
			break;
		}
		}

		std::string newCommand;
		try
		{
			newCommand = command->CompileArgument(commandTarget);
		} catch (std::logic_error&)
		{
			return "";
		}
		commandList += newCommand;
	}

	if (commandTarget == CommandTarget::python)
	{
		const auto copyCommandList = commandList;
		const auto newSettings = ConstructPythonConsoleSpecialSettings(commandTarget);
		commandList = newSettings + " " + copyCommandList;
	}

	if (used_os == OSType::os_linux)
	{
		return ConstructForLinux(commandTarget, commandList);
	}
	else if (used_os == OSType::os_windows)
	{
		return ConstructForWindows(commandTarget, commandList);
	}
	else if (used_os == OSType::os_mac)
	{
		return ConstructForMac(commandTarget, commandList);
	}
	else
	{
		throw std::logic_error("Unknown OS");
	}
}

bool deamer::file::tool::action::Action::IsEmpty() const
{
	return empty;
}

void deamer::file::tool::action::Action::SetCommands(
	std::vector<std::unique_ptr<Command>> commands_)
{
	if (commands_.empty())
	{
		return;
	}

	empty = false;
	commands = std::move(commands_);
}

std::unique_ptr<deamer::file::tool::action::Action> deamer::file::tool::action::Action::Copy() const
{
	std::vector<std::unique_ptr<Command>> copiedCommands;
	for (const auto& command : commands)
	{
		copiedCommands.push_back(command->Copy());
	}

	auto newAction = std::make_unique<Action>();
	newAction->SetCommands(std::move(copiedCommands));
	newAction->used_os = this->used_os;
	return newAction;
}

std::string deamer::file::tool::action::Action::ConstructPythonConsoleSpecialSettings(
	CommandTarget commandTarget) const
{
	std::string ourOs;
	if (used_os == OSType::os_linux)
	{
		ourOs = "linux";
	}
	else if (used_os == OSType::os_windows)
	{
		ourOs = "windows";
	}
	else if (used_os == OSType::os_mac)
	{
		ourOs = "windows";
	}
	else
	{
		ourOs = "linux";
	}

	return "\"SETTING OUR_OS " + ourOs + "\"";
}

std::string deamer::file::tool::action::Action::ConstructForLinux(CommandTarget commandTarget,
																  const std::string& commands) const
{
	if (commandTarget == CommandTarget::python)
	{
		return "(python3 " + GetPathToConsoleScript() + " " + commands + ")";
	}

	// if (commandTarget == CommandTarget::linux)
	return "(" + commands + ")";
}

std::string
deamer::file::tool::action::Action::ConstructForWindows(CommandTarget commandTarget,
														const std::string& commands) const
{
	if (commandTarget == CommandTarget::os_linux)
	{
		return "bash -c \"(" + commands + ")\"";
	}
	if (commandTarget == CommandTarget::python)
	{
		return "(python3 " + GetPathToConsoleScript() + " " + commands + ")";
	}

	// if (commandTarget == CommandTarget::windows)
	return "(" + commands + ")"; // Not tested
}

std::string deamer::file::tool::action::Action::ConstructForMac(CommandTarget commandTarget,
																const std::string& commands) const
{
	if (commandTarget == CommandTarget::python)
	{
		return "(python3 " + GetPathToConsoleScript() + " " + commands + ")";
	}

	// if (commandTarget == CommandTarget::mac)
	return "(" + commands + ")";
}
