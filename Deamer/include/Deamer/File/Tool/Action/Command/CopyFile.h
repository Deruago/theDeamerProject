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

#ifndef DEAMER_FILE_TOOL_ACTION_COMMAND_COPYFILE_H
#define DEAMER_FILE_TOOL_ACTION_COMMAND_COPYFILE_H

#include "Deamer/File/Tool/Action/Command.h"
#include "Deamer/File/Tool/Action/CommandTarget.h"
#include "Deamer/File/Tool/OSType.h"
#include <stdexcept>
#include <string>
#include <utility>

namespace deamer::file::tool::action
{
	/*! \class CopyFile
	 */
	class CopyFile : public Command
	{
	private:
		std::string lhsPath;
		std::string rhsPath;

	public:
		CopyFile(const std::string& lhsPath_, const std::string& rhsPath_);
		virtual ~CopyFile() override = default;

	public:
		virtual std::string CompileArgument(CommandTarget commandTarget) override;
		virtual std::unique_ptr<Command> Copy() override;
	};
}

#endif // DEAMER_FILE_TOOL_ACTION_COMMAND_COPYFILE_H
