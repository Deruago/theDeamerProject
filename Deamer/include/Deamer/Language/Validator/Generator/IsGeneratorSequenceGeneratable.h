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

#ifndef DEAMER_LANGUAGE_VALIDATOR_GENERATOR_ISGENERATORSEQUENCEGENERATABLE_H
#define DEAMER_LANGUAGE_VALIDATOR_GENERATOR_ISGENERATORSEQUENCEGENERATABLE_H

#include "Deamer/Language/Validator/Generator/IsGeneratorSequenceGeneratable.h"
#include <type_traits>

namespace deamer::language::validator::generator
{
	/*!	\class IsGeneratorSequenceGeneratable
	 *
	 *	\brief Checks if the given generator sequence is generatable.
	 *
	 *	\details It checks if all dependencies of all generators are covered,
	 *	in the order presented.
	 */
	template<typename... Generators>
	class IsGeneratorSequenceGeneratable
	{
	private:
		template<typename currentGenerator, typename... GeneratorsLeft>
		static constexpr bool Check()
		{
			if constexpr (currentGenerator::IsDefaultGenerator)
			{
				if constexpr (!currentGenerator::template InSetOfGeneratorsAreDependenciesCovered<
								  Generators...>())
				{
					return false;
				}
			}

			if constexpr (sizeof...(GeneratorsLeft) > 0)
			{
				return Check<GeneratorsLeft...>();
			}
			else
			{
				if constexpr (!currentGenerator::IsDefaultGenerator)
				{
					return true;
				}

				return currentGenerator::template InSetOfGeneratorsAreDependenciesCovered<
					Generators...>();
			}
		}

	public:
		static constexpr bool value = Check<Generators...>();
	};
}

#endif // DEAMER_LANGUAGE_VALIDATOR_GENERATOR_ISGENERATORSEQUENCEGENERATABLE_H
