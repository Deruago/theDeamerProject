#ifndef DEAMER_TYPE_TEMPLATE_TYPEISAMONGTYPES_H
#define DEAMER_TYPE_TEMPLATE_TYPEISAMONGTYPES_H

#include <type_traits>

namespace deamer::type
{
	template<typename CheckType, typename... Ts>
	class TypeIsAmongTypes
	{
	private:
		template<typename T_, typename... Ts_>
		static constexpr bool TypeIsAmongTypes_()
		{
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

#endif //DEAMER_TYPE_TEMPLATE_TYPEISAMONGTYPES_H