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

#include "Deamer/File/Tool/Action/Builder.h"
#include "Deamer/File/Tool/Action/Command/ChangeDirectory.h"
#include "Deamer/File/Tool/Action/Command/CopyFile.h"
#include "Deamer/File/Tool/Action/Command/CrossPlatformCommand.h"
#include "Deamer/File/Tool/Action/Command/MoveFile.h"
#include "Deamer/File/Tool/Action/Command/PlatformDependentCommand.h"
#include "Deamer/File/Tool/Action/Command/RemoveFile.h"
#include "Deamer/File/Tool/Action/Command/SettingCommand.h"

deamer::file::tool::action::Builder::Builder(OSType used_os_) : used_os(used_os_)
{
}

std::unique_ptr<deamer::file::tool::action::Action> deamer::file::tool::action::Builder::GetAction()
{
	auto newAction = std::make_unique<Action>(used_os);
	newAction->SetCommands(std::move(commands));
	commands.clear();

	return newAction;
}

deamer::file::tool::action::Builder&
deamer::file::tool::action::Builder::SetupSetting(Setting setting, const std::string& argument)
{
	auto newCommand = std::make_unique<action::SettingCommand>(setting, argument);
	commands.push_back(std::move(newCommand));

	return *this;
}

deamer::file::tool::action::Builder&
deamer::file::tool::action::Builder::RemoveFile(const std::string& lhsPath)
{
	auto newCommand = std::make_unique<action::RemoveFile>(lhsPath);
	commands.push_back(std::move(newCommand));

	return *this;
}

deamer::file::tool::action::Builder&
deamer::file::tool::action::Builder::MoveFile(const std::string& lhsPath,
											  const std::string& rhsPath)
{
	auto newCommand = std::make_unique<action::MoveFile>(lhsPath, rhsPath);
	commands.push_back(std::move(newCommand));

	return *this;
}

deamer::file::tool::action::Builder&
deamer::file::tool::action::Builder::CopyFile(const std::string& lhsPath,
											  const std::string& rhsPath)
{
	auto newCommand = std::make_unique<action::CopyFile>(lhsPath, rhsPath);
	commands.push_back(std::move(newCommand));

	return *this;
}

deamer::file::tool::action::Builder&
deamer::file::tool::action::Builder::ChangeDirectory(const std::string& lhsPath)
{
	auto newCommand = std::make_unique<action::ChangeDirectory>(lhsPath);
	commands.push_back(std::move(newCommand));

	return *this;
}

deamer::file::tool::action::Builder&
deamer::file::tool::action::Builder::CrossPlatformCommand(const std::string& command)
{
	auto newCommand = std::make_unique<action::CrossPlatformCommand>(command);
	commands.push_back(std::move(newCommand));

	return *this;
}

deamer::file::tool::action::Builder& deamer::file::tool::action::Builder::PlatformSpecificCommand(
	std::vector<PlatformDependentCommand::PlatformDependentCommandMember> platformDependentCommands)
{
	auto newCommand = std::make_unique<action::PlatformDependentCommand>(platformDependentCommands);
	commands.push_back(std::move(newCommand));

	return *this;
}
