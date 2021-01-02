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

#ifndef DEAMER_LEXERGEN_LEXERBUILDER_H
#define DEAMER_LEXERGEN_LEXERBUILDER_H

#include "Deamer/Types/Builder.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Node.h"
#include <string>

namespace deamer
{
    class LexerBuilder : public Builder
    {
    protected:
        LexerType_t LexerType;
        const LanguageDefinition* langDef;
    	
        LexerBuilder(const LanguageDefinition* languageDefinition);
    public:
        virtual ~LexerBuilder() = default;
        
        virtual void AddNode(Node* node) = 0; // Writes the node to the file
        virtual void AddIgnoreNode(Node* node) = 0;
        virtual void AddDeleteNode(Node* node) = 0;

        virtual bool StartBuild() = 0;
        virtual bool FinishBuild() = 0;
    };
}

#endif //DEAMER_LEXERGEN_LEXERBUILDER_H
