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

#ifndef DEAMER_ASTGEN_ASTGEN_H
#define DEAMER_ASTGEN_ASTGEN_H

#include "Deamer/Types/Generator.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include "Deamer/AstGen/AstBuilder.h"
#include <string>
#include <memory>


namespace deamer
{
    enum class AstBuilderType;
	
    class AstGen : public Generator
    {
        private:
            std::unique_ptr<AstBuilder> astBuilder;
            const LanguageDefinition& language_definition_;
        public:
            AstGen(const LanguageDefinition& language_definition, AstBuilderType ast_builder_type);
            //AstGen(std::string dirTarget);
            void DirTarget(std::string dirTarget) override;
            void FileTarget(std::string fileTarget) override;
            void CreateAstNodes(); // Creates a full set of AstNode Classes based of langDef and creates an global header file with all astnode includes
    };
}

#endif //DEAMER_ASTGEN_ASTGEN_H