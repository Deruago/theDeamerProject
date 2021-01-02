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

#ifndef DEAMER_THREATANALYZER_LANGUAGEDEFINITION_LANGUAGEDEFINITIONTHREAT_H
#define DEAMER_THREATANALYZER_LANGUAGEDEFINITION_LANGUAGEDEFINITIONTHREAT_H

namespace deamer { namespace threat { namespace analyzer { namespace languagedefinition {

	enum class LanguageDefinitionThreat
	{
		//warnings
		unusedTerminal = 0,
		unusedNonTerminal = 1,
		unusedProductionRule = 2,
		uselessRule = 3,
		noStartingSymbolSpecified = 4,
		terminalOvershadowsOtherTerminal = 5,
		
		//errors
		multipleDeclarationTerminal = 6,
		multipleDeclarationNonTerminal = 7,
		multipleDeclarationProductionRule = 8,
		emptyRecursion = 9,
		nonTerminalHasNoProductionRulesAssociated = 10,
	};

}}}}

#endif //DEAMER_THREATANALYZER_LANGUAGEDEFINITION_LANGUAGEDEFINITIONTHREAT_H