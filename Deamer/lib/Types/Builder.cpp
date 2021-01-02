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
#include "Deamer/Types/Builder.h"
#include <iostream>
#include <fstream>
#include <sstream>

deamer::Builder::Builder()
{
    
}

void deamer::Builder::SetDirTarget(std::string dirName)
{
    Directory = dirName;
}

void deamer::Builder::SetFileTarget(std::string fileName)
{
    FileName = fileName;
}

std::string deamer::Builder::GetOutput() const
{
    return Output;
}

void deamer::Builder::WriteOutputToFile() const
{
    std::ostringstream file_path;
    file_path << Directory << FileName;
    std::ofstream new_file;

    new_file.open(file_path.str(), std::ios_base::app);

    new_file << Output << '\n';
    
    new_file.close();
}


void deamer::Builder::WriteOutputToFile(const std::string& file_name, const std::string& file_content) const
{
    std::ostringstream file_path;
    file_path << Directory << file_name;
    std::ofstream new_file;

    new_file.open(file_path.str(), std::ios_base::app);

    new_file << file_content << '\n';

    new_file.close();
}