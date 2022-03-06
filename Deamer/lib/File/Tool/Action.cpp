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

#include "Deamer/File/Tool/Action.h"
#include "Deamer/File/Tool/Action/Builder.h"

deamer::file::tool::Action::Action(std::string action_) : action(std::move(action_))
{
}

const std::string& deamer::file::tool::Action::GetAction() const
{
	return action;
}

std::string deamer::file::tool::Action::GetSubShellAction(const file::tool::OSType os,
														  const std::string& directory) const
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

std::unique_ptr<deamer::file::tool::action::Action>
deamer::file::tool::Action::GetGeneralAction() const
{
	auto builder = action::Builder();
	builder.CrossPlatformCommand(GetAction());
	auto generalAction = builder.GetAction();
	return generalAction;
}
