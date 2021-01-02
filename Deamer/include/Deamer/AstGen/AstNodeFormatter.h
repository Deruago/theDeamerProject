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

#ifndef DEAMER_ASTGEN_ASTNODEFORMATTER_H
#define DEAMER_ASTGEN_ASTNODEFORMATTER_H
#include <string>

#include "Deamer/AstGen/AstNodeVisitorBasedBuilder/AstBuilderVisitorBased.h"

namespace deamer
{
	enum class AstFileType;
	class AstFileFormatter;

	class AstNodeFormatter
	{
	private:
	protected:
		std::string language_name_;
	public:
		std::string output;
		AstNodeFormatter() = default;
		AstNodeFormatter(const std::string& language_name);
		~AstNodeFormatter() = default;

		std::string MakeClassName(const Token* token) const;
	};
}

#endif //DEAMER_ASTGEN_ASTNODEFORMATTER_H