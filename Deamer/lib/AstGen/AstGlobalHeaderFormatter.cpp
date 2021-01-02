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

#include "Deamer/AstGen/AstGlobalHeaderFormatter.h"
#include "Deamer/AstGen/AstNodeFormatter.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include <sstream>
#include <fstream>


deamer::AstGlobalHeaderFormatter::AstGlobalHeaderFormatter(const std::string& directory, const std::string& language_name)
{
    directory_ = directory;
    language_name_ = language_name;
}

void deamer::AstGlobalHeaderFormatter::CreateGlobalHeaderFile() const
{

    AddCodeToFile("#ifndef ASTNODES_ASTNODES_H\n"
                  "#define ASTNODES_ASTNODES_H\n"
                  "\n");
}

void deamer::AstGlobalHeaderFormatter::AddToken(const Token& token) const
{
    AddCodeToFile("#include \"./" + AstNodeFormatter().MakeClassName(&token) + ".h\"\n");
}

void deamer::AstGlobalHeaderFormatter::FinishGlobalHeaderFile() const
{
    AddCodeToFile("\n"
                  "#endif //ASTNODES_ASTNODES_H\n");
}

void deamer::AstGlobalHeaderFormatter::AddCodeToFile(const std::string& new_code) const
{
    std::ostringstream oss0;
    oss0 << directory_ << "AstNodes.h";
    std::ofstream globalHeaderFile;

    globalHeaderFile.open(oss0.str(), std::ios_base::app);

    globalHeaderFile << new_code;
	
    globalHeaderFile.close();
}