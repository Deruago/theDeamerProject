/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
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