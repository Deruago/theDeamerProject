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

#ifndef DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_TYPEANALYZER_H
#define DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_TYPEANALYZER_H

#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include <vector>

namespace deamer
{
	class Token;
	struct TokenAppearance;
	
	class TypeAnalyzer
	{
	private:
		Type* type_;
		void AddTokenToVectorIfNotAlreadyInVector(std::vector<Token*>& tokens, Token* token) const;

		Rule* CreateRule_Without_Ignored_Tokens(Rule* rule) const;
		bool IsThisRuleUniqueInVector(const std::vector<Rule*>& rules, const Rule& rule) const;
		bool AreRulesEqual(const Rule& rule1, const Rule& rule2) const;

	public:
		TypeAnalyzer(Type& type);
		~TypeAnalyzer() = default;

		bool HasTypeEmptyRule() const;
		
		std::vector<Token*> GetVectorOfUniqueTokensDefiningThisType() const;
		// i.e: t: a a, a a a returns vector with a a a. as a a a is minimal amount of tokens that are needed to cover all rules.
		std::vector<deamer::TokenAppearance> GetVectorOfMinimalAmountOfTokensUsedDefiningThisType() const;
		std::vector<Rule*> GetVectorOfUniqueRulesApplyingIgnoredTokens() const;

		unsigned GetTokenTypesOccuringInType() const;
		unsigned GetTokenTypesOccuringInType(const Type& type, BitwiseEnum<TokenType_t>& tokenType, BitwiseEnum<TokenPermission_t>& tokenPermission) const;
	};
}

#endif //DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_TYPEANALYZER_H