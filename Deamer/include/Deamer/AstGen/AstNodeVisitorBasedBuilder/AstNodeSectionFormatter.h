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

#ifndef DEAMER_ASTGEN_ASTNODEVISITORBASEDBUILDER_ASTNODEFORMATTER_H
#define DEAMER_ASTGEN_ASTNODEVISITORBASEDBUILDER_ASTNODEFORMATTER_H

#include "Deamer/AstGen/AstNodeFormatter.h"
#include "Deamer/AstGen/AstNodeVisitorBasedBuilder/AstBuilderVisitorBased.h"
#include <string>

namespace deamer
{
	enum class AstFileType;
	class AstFileFormatter;

	namespace AstVisitorBuilder {
	class AstNodeSectionFormatter: public AstNodeFormatter
	{
	private:
	protected:
	public:
		std::string output;
		AstNodeSectionFormatter(const std::string& language_name);
		~AstNodeSectionFormatter() = default;

		void MakeAstNode(Token* token, AstFileType ast_file_type);
	};
}}

#endif //DEAMER_ASTGEN_ASTNODEVISITORBASEDBUILDER_ASTNODEFORMATTER_H