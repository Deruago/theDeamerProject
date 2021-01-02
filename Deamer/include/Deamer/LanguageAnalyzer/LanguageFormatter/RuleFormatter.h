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

#ifndef DEAMER_LANGUAGEANALYZER_LANGUAGEFORMATTER_RULEFORMATTER_H
#define DEAMER_LANGUAGEANALYZER_LANGUAGEFORMATTER_RULEFORMATTER_H
#include <string>

#include "Deamer/ParserGen/BisonBuilder/BisonRuleSectionFormatter.h"

namespace deamer
{
	class Token;

	class RuleFormatter
	{
	private:
	protected:
	public:
		RuleFormatter() = default;
		~RuleFormatter() = default;

		std::string MakeConstructorArguments(Token* token_subject, Rule& rule);
		std::string MakeConstructorPrototype(Token* token_subject, Rule& rule);
		std::string MakeConstructors(Token* token_subject, Rule& rule);
		std::string MakeConstructor(Token* token, Rule& rule);
	};
}

#endif //DEAMER_LANGUAGEANALYZER_LANGUAGEFORMATTER_RULEFORMATTER_H