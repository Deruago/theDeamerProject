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

#ifndef DEAMER_ASTGEN_ASTNODEINTERPRETERBASEDBUILDER_ASTBUILDER_H
#define DEAMER_ASTGEN_ASTNODEINTERPRETERBASEDBUILDER_ASTBUILDER_H

#include "Deamer/AstGen/AstBuilder.h"
#include "Deamer/AstGen/AstEnumHeaderSectionFormatter.h"
#include "Deamer/AstGen/AstGlobalHeaderFormatter.h"
#include <string>

namespace deamer {
	class Token;
	class FileClassSection;
	namespace AstInterpreterBuilder {
	
		class AstBuilderInterpreterBased : public AstBuilder
		{
		private:
			AstEnumHeaderSectionFormatter enum_header_section_formatter_ = AstEnumHeaderSectionFormatter("", "");
			AstGlobalHeaderFormatter global_header_formatter_ = AstGlobalHeaderFormatter("", "");

			deamer::FileClassSection* GetAstNodeFileBuilderClass() const;
			std::string FillAstSourceFile(Token* token) const;
			std::string FillAstHeaderFile(Token* token) const;
		public:
			AstBuilderInterpreterBased(const std::string& directory, const std::string& language_name);

			void StartBuild() override;
			void Build(Node& node) override;
			void Build(Type& type) override;
			void FinishBuild() override;
	};
}}

#endif //DEAMER_ASTGEN_ASTNODEINTERPRETERBASEDBUILDER_ASTBUILDER_H