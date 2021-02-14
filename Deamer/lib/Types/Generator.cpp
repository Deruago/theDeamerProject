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

#include "Deamer/Types/Generator.h"
#include <filesystem>
#include <sys/types.h>
#include <sys/stat.h>

void deamer::Generator::DirTarget(std::string dirTarget)
{
}

void deamer::Generator::FileTarget(std::string fileTarget)
{
}

void deamer::Generator::Build()
{
}

void deamer::Generator::Write()
{
}

bool deamer::Generator::DoesDirectoryExist(const std::string& Directory) const
{
    struct stat info;

    if(stat(Directory.c_str(), &info ) != 0 )
    {
        return false;
    }
    else if(info.st_mode & S_IFDIR )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool deamer::Generator::CreateDirectory(const std::string& Directory) const
{
	return std::filesystem::create_directory(Directory.c_str());
}

void deamer::Generator::CreateDirectoryIfNotExist(const std::string& Directory) const
{
    if(!DoesDirectoryExist(Directory))
    {
        CreateDirectory(Directory);
    }
}