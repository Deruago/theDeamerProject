#ifndef DEAMER_TYPE_TEMPLATE_TYPEISAMONGTYPESTILLSPECIFICTYPEISFOUND_H
#define DEAMER_TYPE_TEMPLATE_TYPEISAMONGTYPESTILLSPECIFICTYPEISFOUND_H

#include <type_traits>

namespace deamer::type
{
	template<typename DeadType, typename CheckType, typename... Ts>
	class TypeIsAmongTypesTillSpecificTypeIsFound
	{
	private:
		template<typename T_, typename... Ts_>
		static constexpr bool TypeIsAmongTypes_()
		{
			// If we find the deadtype, we are too late to find the values,
			// meaning we can always return false.
			if constexpr (std::is_same<DeadType, T_>::value)
			{
				return false;
			}
			
			if constexpr (std::is_same<CheckType, T_>::value)
				return true;
			else if constexpr (sizeof...(Ts_) > 0)
				return TypeIsAmongTypes_<Ts_...>();
			else
				return false;
		}
	public:
		static constexpr bool value = TypeIsAmongTypes_<Ts...>();
	};
}

#endif //DEAMER_TYPE_TEMPLATE_TYPEISAMONGTYPESTILLSPECIFICTYPEISFOUND_H