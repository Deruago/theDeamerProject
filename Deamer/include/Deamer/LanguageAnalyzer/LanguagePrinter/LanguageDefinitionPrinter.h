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

#ifndef DEAMER_LANGUAGEANALYZER_LANGUAGEDEFINITIONPRINTER_H
#define DEAMER_LANGUAGEANALYZER_LANGUAGEDEFINITIONPRINTER_H
#include "Deamer/LanguageAnalyzer/LanguageVisitor/LanguageDefinitionVisitor.h"
#include <vector>
#include <string>

namespace deamer
{
	class LanguageDefinition;

	class LanguageDefinitionPrinter : public LanguageDefinitionVisitor
	{
	protected:
		std::string MakeIndent(unsigned indent) const;
		std::string MakeIndentation(unsigned depth, unsigned indent) const;
		void PrintAllTokens(LanguageDefinition& language_definition) const;
	public:
		LanguageDefinitionPrinter() = default;
		~LanguageDefinitionPrinter() = default;

		virtual void visit(Token& visited_type);
		void first_visit(Rule& visited_type) override;
		void first_visit(Node& visited_type) override;
		void first_visit(Type& visited_type) override;
		void visit(Type& type) override;
		void visit(Node& node) override;
		
		virtual void Print(LanguageDefinition& language_definition);
		void PrintAllRules(LanguageDefinition& language_definition) const;
		void PrintAllNodes(LanguageDefinition& language_definition) const;
		void PrintAllGroupedTypes(LanguageDefinition& language_definition) const;
		void PrintAllIgnoredNodes(LanguageDefinition& language_definition) const;
		void PrintAllIgnoredTypes(LanguageDefinition& language_definition) const;
	};
}

#endif //DEAMER_LANGUAGEANALYZER_LANGUAGEDEFINITIONPRINTER_H