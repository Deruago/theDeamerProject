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

#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/LanguageDefinitionAnalyzer.h"

deamer::LanguageDefinitionAnalyzer::LanguageDefinitionAnalyzer(const LanguageDefinition& languageDefinition_) : languageDefinition(languageDefinition_)
{
}

deamer::Token* deamer::LanguageDefinitionAnalyzer::GetStartToken() const
{
	if (languageDefinition.StartType != nullptr)
		return languageDefinition.StartType;
	else
		if (languageDefinition.GetTypes().empty())
			return nullptr;
		else
			return languageDefinition.GetTypes()[0];
}

// This is done by finding a cycle from NT a to NT a, via NT's.
// The analysis is extremely complex as a huge grammar with a lot of production rules, have a lot of options.
bool deamer::LanguageDefinitionAnalyzer::DoesTokenHaveEmptyRecursion() const
{
	return false;
}
