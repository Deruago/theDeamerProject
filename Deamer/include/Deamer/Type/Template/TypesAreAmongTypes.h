#ifndef DEAMER_TYPE_TEMPLATE_TYPESAREAMONGTYPES_H
#define DEAMER_TYPE_TEMPLATE_TYPESAREAMONGTYPES_H

#include "TypeIsAmongTypes.h"

namespace deamer::type
{
	/*!	\class TypesAreAmongTypes
	 *
	 *	\brief This class can be used to check whether a set of types, are in another set of types.
	 *
	 *	\note This is done on compile time.
	 *
	 *	\details It checks for each of the time (recursively), if the type occurs in the set, if some type is not found it returns false.
	 *	If everything is found, it returns true.
	 *
	 *	\tparam Ts The set of vectors that we may look through.
	 * 
	 */
	template <typename... Ts >
	class TypesAreAmongTypes
	{
	private:
		template<typename CheckType_, typename... CheckTypes_>
		static constexpr bool TypesAreAmongTypes_()
		{
			if constexpr (TypeIsAmongTypes<CheckType_, Ts...>::value)
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
	public:
		/*!	\property value
		 *
		 *	\brief Used to retrieve the boolean result of the function.
		 *
		 *	\tparam CheckTypes The types to check if they occur in the "Ts" set of types.
		 */
		template<typename... CheckTypes>
		static constexpr bool value = TypesAreAmongTypes_<CheckTypes...>();
	};

}

#endif //DEAMER_TYPE_TEMPLATE_TYPESAREAMONGTYPES_H