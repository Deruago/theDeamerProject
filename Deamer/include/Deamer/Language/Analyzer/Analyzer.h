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

#ifndef DEAMER_LANGUAGE_ANALYZER_ANALYZER_H
#define DEAMER_LANGUAGE_ANALYZER_ANALYZER_H

#include "Deamer/Language/Validator/Analyzer/GetAnalyzerFromObjectType.h"

namespace deamer::language::analyzer
{
	template<typename LDO_type>
	class Analyzer
	{
	public:
		using LDO_Analyzer =
			typename validator::analyzer::GetAnalyzerFromObjectType<LDO_type>::type;

	private:
		LDO_Analyzer ldoAnalyzer;

	public:
		Analyzer(const reference::PropertyDefinitionBase* reference, const LDO_type* ldo)
			: ldoAnalyzer(reference, ldo)
		{
			std::cout << reference << " " << reference->GetLanguageCache() << "\n";
		}

		~Analyzer() = default;

	public:
		const LDO_Analyzer* operator->() const
		{
			return &this->ldoAnalyzer;
		}
	};
}

#endif // DEAMER_LANGUAGE_ANALYZER_ANALYZER_H
