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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_SINGLE_DEAMER_LEXICON_NONSTANDARDNAMINGCONVENTION_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_SINGLE_DEAMER_LEXICON_NONSTANDARDNAMINGCONVENTION_H

#include "Deamer/Language/Type/Definition/Object/Main/Threat/Check/Single/Single.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Threat/Analyzer/Deamer/Lexicon/NonStandardNamingConvention.h"

namespace deamer::language::type::definition::property
{
	class Definition;
}

namespace deamer::language::type::definition::object::main::threat::check::deamer::lexicon
{
	/*! \class NonStandardNamingConvention
	 *
	 *  \brief Checks each terminal for proper naming conventions.
	 */
	class NonStandardNamingConvention
		: public Single<property::Type::Lexicon>,
		  public CheckOutput<threat::deamer::lexicon::NonStandardNamingConvention>
	{
	protected:
		/*!	\fn AnalyzeDefinition
		 */
		std::vector<Threat*> AnalyzeDefinition(PropertyReference reference) override
		{
			std::vector<Threat*> threats;

			const auto& lexicon = reference.GetDefinition<property::Type::Lexicon>();

			for (auto* const terminal : lexicon.Terminals)
			{
				if (NonTerminalFollowsConvention(terminal->Name))
				{
					continue;
				}

				threats.push_back(
					new threat::deamer::lexicon::NonStandardNamingConvention(terminal));
			}

			return threats;
		}

	private:
		bool NonTerminalFollowsConvention(const std::string& name)
		{
			if (name.find("deamerreserved") == 0)
			{
				return true;
			}

			for (const auto& character : name)
			{
				if (::isalpha(character) && !::isupper(character))
				{
					return false;
				}
			}

			return true;
		}
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_SINGLE_DEAMER_LEXICON_NONSTANDARDNAMINGCONVENTION_H
