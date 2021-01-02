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

#ifndef DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_ERROR_MULTIPLEDECLARATIONTERMINAL_H
#define DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_ERROR_MULTIPLEDECLARATIONTERMINAL_H

#include "Deamer/ThreatAnalyzer/LanguageDefinition/LanguageDefintionThreat.h"
#include "Deamer/ThreatAnalyzer/Threat/ErrorThreat.h"

namespace deamer { namespace threat { namespace analyzer { namespace languagedefinition { namespace error {

	class MultipleDeclarationTerminal : public ErrorThreat, public LanguageDefinitionVisitor
	{
	public:
		const std::string description = "Redeclared Terminal";
		constexpr static unsigned id = static_cast<unsigned>(LanguageDefinitionThreat::multipleDeclarationTerminal);
		MultipleDeclarationTerminal(const LanguageDefinition& languageDefinition_);

		std::vector<ThreatData> AnalyseLanguageDefinition() override;


	private:
		ThreatData MakeThreatData(Node* node) const;
		ThreatCodeDescription MakeThreatCodeDescription(Node* node) const;
		std::string MakeErrorDescription(const Node& node) const;
		bool NonTerminalHasSameNameAsOtherNonTerminal(const Node* a, const Node* b) const;
		bool NonTerminalHasSameNameAsAnyOfAlreadyVisitedTypes(const Node* node) const;
		bool NonTerminalIsInVisitedTypes(Node* node) const;
		bool NonTerminalIsInDuplicatedTypes(const Node* node) const;
		std::vector<Node*> UsedNodes;
		std::vector<Node*> DuplicateNodes;

		void first_visit(Type& visited_type) override;
		void first_visit(Rule& visited_type) override;
		void first_visit(Node& visited_type) override;
		void visit(Type& type) override;
		void visit(Node& node) override;
	public:
		~MultipleDeclarationTerminal() override = default;
	};

}}}}}

#endif //DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_ERROR_MULTIPLEDECLARATIONTERMINAL_H