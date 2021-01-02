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

#ifndef DEAMER_PARSERGEN_PARSERBUILDER_H
#define DEAMER_PARSERGEN_PARSERBUILDER_H

#include "Deamer/Types/Builder.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include <string>

namespace deamer
{
    class Node;
    class Type;
    class Rule;
    class LanguageDefinition;
	
    class ParserBuilder : public Builder
    {
    protected:
        ParserType_t parserType;
        const LanguageDefinition* langDef;

    	ParserBuilder(const LanguageDefinition* languageDefinition);
    public:
        virtual ~ParserBuilder() = default;


    	virtual void AddNode(Node* node) = 0; // Writes the node to the file
        virtual void AddType(Type* type) = 0; // Writes the type to the file
        virtual void AddRule(Rule* rule) = 0; // Writes the rule to the file, Note: Type already includes rules so this could be unneccessary
        virtual bool StartBuild() = 0;
        virtual bool FinishBuild() = 0;
    };
}

#endif //DEAMER_PARSERGEN_PARSERBUILDER_H