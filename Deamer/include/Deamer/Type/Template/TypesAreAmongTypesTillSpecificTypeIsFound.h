#ifndef DEAMER_TYPE_TEMPLATE_TYPESAREAMONGTYPESTILLSPECIFICTYPEISFOUND_H
#define DEAMER_TYPE_TEMPLATE_TYPESAREAMONGTYPESTILLSPECIFICTYPEISFOUND_H

#include "Deamer/Type/Template/TypeIsAmongTypesTillSpecificTypeIsFound.h"

namespace deamer::type
{
	/*!	\class TypesAreAmongTypesTillSpecificTypeIsFound
	 *
	 *	\brief This class can be used to check whether a set of types, are in another set of types.
	 *Until a given type is found.
	 *
	 *	\note This is done on compile time.
	 *
	 *	\details It checks for each of the time (recursively), if the type occurs in the set, if
	 *some type is not found it returns false. If everything is found, it returns true.
	 *
	 *	You can input a specific type, that stops the search. If not every type is found, the
	 *function will return false.
	 *
	 *	\tparam Ts The set of vectors that we may look through.
	 *
	 */
	template<typename DeadType, typename... Ts>
	class TypesAreAmongTypesTillSpecificTypeIsFound
	{
	private:
		template<typename CheckType_, typename... CheckTypes_>
		static constexpr bool TypesAreAmongTypes_()
		{
			if constexpr (TypeIsAmongTypesTillSpecificTypeIsFound<DeadType, CheckType_,
																  Ts...>::value)
			{
				if constexpr (sizeof...(CheckTypes_) > 0)
				{
					return TypesAreAmongTypes_<CheckTypes_...>();
				}
				else
				{
					return true;
				}
			}
			else
			{
				return false;
			}
		}

		template<typename... CheckTypes_>
		static constexpr bool TypesAreAmongTypes_Proxy()
		{
			if constexpr (sizeof...(CheckTypes_) > 0)
			{
				return TypesAreAmongTypes_<CheckTypes_...>();
			}
			else
			{
				return true;
			}
		}

	public:
		/*!	\property value
		 *
		 *	\brief Used to retrieve the boolean result of the function.
		 *
		 *	\tparam CheckTypes The types to check if they occur in the "Ts" set of types.
		 */
		template<typename... CheckTypes>
		static constexpr bool value = TypesAreAmongTypes_Proxy<CheckTypes...>();
	};

}

#endif // DEAMER_TYPE_TEMPLATE_TYPESAREAMONGTYPESTILLSPECIFICTYPEISFOUND_H
