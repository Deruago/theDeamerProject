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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_SINGLE_SINGLE_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_SINGLE_SINGLE_H

#include "Deamer/Language/Convertor/Definition/PropertyTypeToEnum.h"
#include "Deamer/Language/Reference/LanguageGenerator.h"
#include "Deamer/Language/Reference/PropertyDefinition.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Check/Check.h"

namespace deamer::language::type::definition::property
{
	class Definition;
}

namespace deamer::language::type::definition::object::main::threat::check
{
	/*! \class Single
	 *
	 *  \brief Base class of all threat checks targeting 1 LPD.
	 *
	 *  \note Single checks may not use reverselookups for outside LPD's.
	 *
	 *  \tparam T The LPD it targets.
	 */
	template<const type::definition::property::Type T,
			 std::enable_if_t<T != property::Type::Unknown, bool> = true>
	class Single : public Check
	{
	public:
		using PropertyReference = reference::PropertyDefinition<T>;

	public:
		virtual ~Single() override = default;

	public:
		[[nodiscard]] std::vector<Threat*> Analyze(Language* language) override
		{
			return AnalyzeDefinition(language);
		}

		[[nodiscard]] std::vector<Threat*>
		Analyze(const reference::LanguageGenerator& language) override
		{
			const auto tmpLanguage = language.GetTemporaryLanguageDefinition();
			auto* tmpLanguagePtr = tmpLanguage.get();
			return AnalyzeDefinition(tmpLanguagePtr);
		}

	protected:
		virtual std::vector<Threat*> AnalyzeDefinition(PropertyReference reference) = 0;
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_SINGLE_SINGLE_H
