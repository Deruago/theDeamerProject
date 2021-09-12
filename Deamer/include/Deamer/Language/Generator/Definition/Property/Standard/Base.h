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

#ifndef DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_STANDARD_BASE_H
#define DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_STANDARD_BASE_H

#include "Deamer/Language/Convertor/Definition/PropertyTypeToEnum.h"
#include "Deamer/Language/Convertor/Definition/PropertyTypesToEnums.h"
#include "Deamer/Language/Generator/Definition/Base.h"
#include "Deamer/Language/Generator/Definition/Property/Standard/BaseAPI.h"
#include "Deamer/Language/Validator/Definition/GetObjectEnumsFromPropertyType.h"
#include "Deamer/Type/Template/TypeIsAmongTypes.h"
#include "Deamer/Type/Template/TypesAreAmongTypes.h"
#include "Deamer/Type/Template/TypesAreAmongTypesTillSpecificTypeIsFound.h"

namespace deamer::language::generator::definition::property::standard
{
	/*!	\class Base
	 *
	 *	\brief This is the base class of all default generators.
	 *
	 *	\tparam LanguageDefinitionType Used to specify the language definition class used to
	 *generate a specific language.
	 *
	 *	\tparam PropertyType Used to deduce the allowed Object Types for the property definition.
	 *
	 *	\tparam Dependencies The LPD dependencies this generator requires to be generated first.
	 */
	template<typename LanguageDefinitionType, typename PropertyType, typename... Dependencies>
	class Base : public BaseAPI<LanguageDefinitionType, PropertyType, Dependencies...>
	{
	public:
		Base(LanguageDefinitionType* const language_)
			: BaseAPI<LanguageDefinitionType, PropertyType, Dependencies...>(language_)
		{
			static_assert(
				std::is_base_of<definition::Base, LanguageDefinitionType>::value,
				"Given Language definition type is not a derived class of a Language generator!");
		}
		virtual ~Base() = default;

		/*!	\fn InSetOfGeneratorsAreRequiredDependenciesCovered
		 *
		 *	\brief Checks if the dependency chain is valid, based on a set of generators.
		 *
		 *	\details Generators first need to be converted to their output/target, this function
		 *does this.
		 *
		 *	\tparam Generators_ A set of generators.
		 */
		template<typename... Generators_>
		static constexpr bool InSetOfGeneratorsAreDependenciesCovered()
		{
			return InSetOfGeneratorsAreDependenciesCovered_<sizeof...(Generators_),
															Generators_...>();
		}

		/*!	\fn InSetOfGeneratorsAreRequiredDependenciesCovered_
		 *
		 *	\brief Converts a set of generators into their targets.
		 *	And checks if in the end, if the dependency chain is valid.
		 *
		 *	\tparam counter_ Used to track the remaining generators, that need to be converted.
		 *
		 *	\tparam CurrentGenerator_ Current generator.
		 *
		 *	\tparam Generators_ Remaining generators.
		 */
		template<const size_t counter_, typename CurrentGenerator_, typename... Generators_>
		static constexpr bool InSetOfGeneratorsAreDependenciesCovered_()
		{
			if constexpr (counter_ > 0)
			{
				return InSetOfGeneratorsAreDependenciesCovered_<
					counter_ - 1, Generators_...,
					typename CurrentGenerator_::TargetPropertyDefinition_t>();
			}
			else
			{
				return AreRequiredDependenciesCoveredTillThisIsFound<CurrentGenerator_,
																	 Generators_...>();
			}
		}

		/*!	\fn InSetOfGeneratorsAreRequiredDependenciesCovered
		 *
		 *	\brief Checks if all dependencies are covered, based on a set of generators.
		 *
		 *	\details Generators first need to be converted to their output/target, this function
		 *does this.
		 *
		 *	\tparam Generators_ A set of generators.
		 */
		template<typename... Generators_>
		static constexpr bool InSetOfGeneratorsAreRequiredDependenciesCovered()
		{
			return InSetOfGeneratorsAreRequiredDependenciesCovered_<sizeof...(Generators_),
																	Generators_...>();
		}

		/*!	\fn InSetOfGeneratorsAreRequiredDependenciesCovered_
		 *
		 *	\brief Converts a set of generators into their targets. And checks in the end if the
		 *dependencies are covered.
		 *
		 *	\tparam counter_ Used to track the remaining generators, that need to be converted.
		 *
		 *	\tparam CurrentGenerator_ Current generator.
		 *
		 *	\tparam Generators_ Remaining generators.
		 */
		template<const size_t counter_, typename CurrentGenerator_, typename... Generators_>
		static constexpr bool InSetOfGeneratorsAreRequiredDependenciesCovered_()
		{
			if constexpr (counter_ > 0)
			{
				return InSetOfGeneratorsAreRequiredDependenciesCovered_<
					counter_ - 1, Generators_...,
					typename CurrentGenerator_::TargetPropertyDefinition_t>();
			}
			else
			{
				return AreRequiredDependenciesCovered<CurrentGenerator_, Generators_...>();
			}
		}

		/*!	\fn AreRequiredDependenciesCoveredTillThisIsFound
		 *
		 *	\brief Checks whether all required dependencies are covered, before we use them.
		 *
		 *	\tparam DependenciesIncludingThis_ A pack of LPD dependencies.
		 */
		template<typename... DependenciesIncludingThis_>
		static constexpr bool AreRequiredDependenciesCoveredTillThisIsFound()
		{
			return ::deamer::type::TypesAreAmongTypesTillSpecificTypeIsFound<
				PropertyType, DependenciesIncludingThis_...>::template value<Dependencies...>;
		}

		/*!	\fn AreRequiredDependenciesCovered
		 *
		 *	\brief Checks whether all required dependencies are covered for this generator. (The
		 *order doesn't matter)
		 *
		 *	\tparam AvailableDependencies_ A pack of LPD dependencies.
		 */
		template<typename... AvailableDependencies_>
		static constexpr bool AreRequiredDependenciesCovered()
		{
			return ::deamer::type::TypesAreAmongTypes<AvailableDependencies_...>::template value<
				Dependencies...>;
		}

		/*!	\fn IsDependencyInRequiredDependencies
		 *
		 *	\brief Checks whether a given dependency is required by this generator.
		 *
		 *	\tparam Dependency_ The LPD dependency to check.
		 */
		template<typename Dependency_>
		static constexpr bool IsDependencyInRequiredDependencies()
		{
			return ::deamer::type::TypeIsAmongTypes<Dependency_, Dependencies...>();
		}
	};
}

#endif // DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_STANDARD_BASE_H
