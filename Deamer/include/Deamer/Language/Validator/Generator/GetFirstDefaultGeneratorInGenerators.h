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

#ifndef DEAMER_LANGUAGE_VALIDATOR_GENERATOR_GETFIRSTDEFAULTGENERATORINGENERATORS_H
#define DEAMER_LANGUAGE_VALIDATOR_GENERATOR_GETFIRSTDEFAULTGENERATORINGENERATORS_H

#include <type_traits>

namespace deamer::language::validator::generator
{
	template<bool Q, typename Told>
	class GetFirstDefaultGeneratorInGeneratorsFinal;
	
	template<bool Q, typename Told, typename Tnew, typename... Ts>
	class GetFirstDefaultGeneratorInGeneratorsBase;

	/*!	\class GetFirstDefaultGeneratorInGenerators
	 *
	 *	\brief Returns the first default generator in a pack of generators
	 */
	template<typename Tcurrent, typename... Ts>
	class GetFirstDefaultGeneratorInGenerators : public std::conditional<sizeof...(Ts) == 0, GetFirstDefaultGeneratorInGeneratorsFinal<Tcurrent::IsDefaultGenerator, Tcurrent>, GetFirstDefaultGeneratorInGeneratorsBase<Tcurrent::IsDefaultGenerator, Tcurrent, Ts..., void>>::type
	{};

	template<bool Q, typename Told, typename Tnew, typename... Ts>
	class GetFirstDefaultGeneratorInGeneratorsBase : public std::conditional< sizeof...(Ts) == 0, GetFirstDefaultGeneratorInGeneratorsFinal<Tnew::IsDefaultGenerator, Tnew>, GetFirstDefaultGeneratorInGeneratorsBase <Tnew::IsDefaultGenerator, Tnew, Ts...>>::type
	{
	};

	template<typename Told, typename Tnew, typename... Ts>
	class GetFirstDefaultGeneratorInGeneratorsBase<true, Told, Tnew, Ts...>
	{
	public:
		using type = Told;
	};

	template<bool Q, typename Told>
	class GetFirstDefaultGeneratorInGeneratorsFinal
	{
	public:
		using type = void;
	};

	template<typename Told>
	class GetFirstDefaultGeneratorInGeneratorsFinal<true, Told>
	{
	public:
		using type = Told;
	};
}

#endif //DEAMER_LANGUAGE_VALIDATOR_GENERATOR_GETFIRSTDEFAULTGENERATORINGENERATORS_H