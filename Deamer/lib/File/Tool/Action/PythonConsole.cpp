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

#include "Deamer/File/Tool/Action/PythonConsole.h"
#include "Deamer/File/Tool/Directory.h"
#include "Deamer/File/Tool/LoadFilesystem.h"

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

bool deamer::file::tool::action::PythonConsole::IsAvailable()
{
	return CheckIfConsoleScriptIsAvailable();
}

std::string deamer::file::tool::action::PythonConsole::GetConsoleLocation()
{
	if (CheckIfConsoleScriptIsAvailable())
	{
		return consoleLocation;
	}

	return "./";
}
