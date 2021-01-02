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

#ifndef DEAMER_DEFAULTAPI_DEAMERLEXERAPI_H
#define DEAMER_DEFAULTAPI_DEAMERLEXERAPI_H

#include "Deamer/AstGen/AstNode.h"
#include <string>

namespace deamer
{
    class DeamerLexerAPI
    {
    public:
        DeamerLexerAPI() = default;
        virtual ~DeamerLexerAPI() = default;
    	
        virtual AstNode* LexText(std::string inputText) = 0;
        virtual AstNode* LexFile(FILE* inputFile) = 0;
        virtual AstNode* LexFile(std::string fileLocation) = 0;
    };
}

#endif //DEAMER_DEFAULTAPI_DEAMERLEXERAPI_H