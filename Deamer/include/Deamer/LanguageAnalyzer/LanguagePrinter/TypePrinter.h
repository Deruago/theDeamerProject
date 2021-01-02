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

#ifndef DEAMER_LANGUAGEANALYZER_LANGUAGEPRINTER_TYPEPRINTER_H
#define DEAMER_LANGUAGEANALYZER_LANGUAGEPRINTER_TYPEPRINTER_H
#include "Deamer/LanguageAnalyzer/LanguagePrinter/LanguageDefinitionPrinter.h"

namespace deamer
{
	class TypePrinter : LanguageDefinitionPrinter
	{
	private:
	protected:
	public:
		TypePrinter() = default;
		~TypePrinter() = default;

		void visit(Token& visited_type) override;
		void first_visit(Rule& visited_type) override;
		void first_visit(Node& visited_type) override;
		void first_visit(Type& visited_type) override;
		void visit(Type& type) override;
		void visit(Node& node) override;

		void Print(LanguageDefinition& language_definition) override;
	};
}

#endif //DEAMER_LANGUAGEANALYZER_LANGUAGEPRINTER_TYPEPRINTER_H