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

#ifndef DEAMER_TYPES_BUILDER_H
#define DEAMER_TYPES_BUILDER_H

/*
Defines abstract class Builder.
*/

#include <string>
#include <iostream>

namespace deamer
{
    class Builder
    {
        protected:
            std::string Output;
            std::string Directory;
            std::string FileName;
            Builder();
        public:
            void SetDirTarget(std::string dirName);
            void SetFileTarget(std::string fileName);
            std::string GetOutput() const; // Returns the output
            void WriteOutputToFile() const;
            void WriteOutputToFile(const std::string& file_name, const std::string& file_content) const;
    };
}

#endif //DEAMER_TYPES_BUILDER_H