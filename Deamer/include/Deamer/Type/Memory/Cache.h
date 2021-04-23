#ifndef DEAMER_TYPE_MEMORY_CACHE_H
#define DEAMER_TYPE_MEMORY_CACHE_H

#include <map>
#include <set>

namespace deamer::type::memory
{
	template<typename T, typename T_enum>
	class Cache
	{
	private:
		std::map<T*, std::map<T_enum, std::set<const T*>>> localCache;

	public:
		Cache() = default;
		~Cache() = default;

	public:
		template<typename T_register>
		void Register(T_register* registerObject, T_enum registerEnumValue, T* targetObject)
		{
			localCache[targetObject][registerEnumValue].insert(registerObject);
		}

		template<typename T_register>
		void Register(T_register* registerObject, T_enum registerEnumValue, const T* targetObject)
		{
			auto* targetObject_stripped = (T*)targetObject;
			localCache[targetObject_stripped][registerEnumValue].insert(registerObject);
		}

		template<typename T_register>
		void Register(T_register* registerObject, T_enum registerEnumValue,
					  volatile T* targetObject)
		{
			auto* targetObject_stripped = (T*)targetObject;
			localCache[targetObject_stripped][registerEnumValue].insert(registerObject);
		}

		template<typename T_register>
		void Register(T_register* registerObject, T_enum registerEnumValue,
					  const volatile T* targetObject)
		{
			auto* targetObject_stripped = (T*)targetObject;
			localCache[targetObject_stripped][registerEnumValue].insert(registerObject);
		}

		const std::set<const T*>& Get(T* sourceObject, T_enum targetObjects)
		{
			auto* sourceObject_stripped = (std::remove_cv_t<T>*)sourceObject;
			return localCache[sourceObject_stripped][targetObjects];
		}

		const std::set<const T*>& Get(const T* sourceObject, T_enum targetObjects)
		{
			auto* sourceObject_stripped = (std::remove_cv_t<T>*)sourceObject;
			return localCache[sourceObject_stripped][targetObjects];
		}

		const std::set<const T*>& Get(volatile T* sourceObject, T_enum targetObjects)
		{
			auto* sourceObject_stripped = (std::remove_cv_t<T>*)sourceObject;
			return localCache[sourceObject_stripped][targetObjects];
		}

		const std::set<const T*>& Get(const volatile T* sourceObject, T_enum targetObjects)
		{
			auto* sourceObject_stripped = (std::remove_cv_t<T>*)sourceObject;
			return localCache[sourceObject_stripped][targetObjects];
		}

		void Clear()
		{
			localCache.clear();
		}
	};
}

#endif // DEAMER_TYPE_MEMORY_CACHE_H
