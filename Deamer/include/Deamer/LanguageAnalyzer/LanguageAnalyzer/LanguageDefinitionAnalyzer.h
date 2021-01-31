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

#ifndef DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_LANGUAGEDEFINITIONANALYZER_H
#define DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_LANGUAGEDEFINITIONANALYZER_H

#include "Deamer/LanguageGen/LanguageDefinition.h"
#include <tuple>

namespace deamer
{
	class LanguageDefinitionAnalyzer
	{
	private:
		const LanguageDefinition& languageDefinition;
	public:
		LanguageDefinitionAnalyzer(const LanguageDefinition& languageDefinition_);
		~LanguageDefinitionAnalyzer() = default;

		Token* GetStartToken() const;
		bool DoesLanguageHaveEmptyRecursion() const;
		bool CheckIfTypeHasEmptyRecursion(deamer::Type& type) const;
		bool DoesTokenHaveEmptyRecursion(Type& type) const;
	private:
		bool IsTokenViableForEmptyRecursion(Type& type) const;

		bool DoesTypeHaveProductionRuleDirectlyReferingItself(const Type& type) const;
		bool DoesTypeHaveProductionRuleDirectlyReferingItself(const Type& type, const Rule& rule) const;

		bool DoesTypeHaveProductionRuleWhenReducedHasDoubleType(const Type& type) const;
		bool DoesTypeHaveProductionRuleWhenReducedHasDoubleType(const Type& type, const Rule& rule) const;
	};
}

#endif //DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_LANGUAGEDEFINITIONANALYZER_H