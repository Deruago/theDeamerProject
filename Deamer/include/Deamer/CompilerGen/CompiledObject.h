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

#ifndef DEAMER_COMPILERGEN_COMPILEDOBJECT_H
#define DEAMER_COMPILERGEN_COMPILEDOBJECT_H

#include "Deamer/CompilerGen/CompilerGenConstants.h"
#include <string>

namespace deamer
{
    class CompiledObject
    {
        private:
        protected:
        public:
            CompiledObject(CompiledOutputType_t compiledOutputType, std::string languageName);
            CompiledOutputType_t CompiledOutputType; // Defines the type of output
            std::string LanguageName; // Used to define which language it comes from
    };
}

#endif //DEAMER_COMPILERGEN_COMPILEDOBJECT_H