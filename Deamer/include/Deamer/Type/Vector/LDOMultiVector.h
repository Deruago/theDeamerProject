#ifndef DEAMER_TYPE_VECTOR_LDOMULTIVECTOR_H
#define DEAMER_TYPE_VECTOR_LDOMULTIVECTOR_H

#include "Deamer/Language/Convertor/Definition/ObjectTypeToEnum.h"
#include "Deamer/Language/Type/Definition/Object/Type.h"
#include <map>
#include <set>
#include <vector>

namespace deamer::language::type::definition::object
{
	class Base;
}

namespace deamer::type::vector
{
	class LDOMultiVector
	{
	private:
		mutable std::map<language::type::definition::object::Type,
						 std::set<const language::type::definition::object::Base*>>
			references;

	public:
		LDOMultiVector() = default;
		~LDOMultiVector() = default;

	public:
		template<typename T>
		const std::set<const language::type::definition::object::Base*>& GetBase() const
		{
			constexpr static auto enumValue =
				language::convertor::definition::ObjectTypeToEnum<T>::value;

			const auto& foundObjects = references[enumValue];

			return foundObjects;
		}

		template<typename T>
		std::set<const T*> Get() const
		{
			const auto foundObjects = GetBase<T>();

			std::set<const T*> returnValue;
			for (const auto* object : foundObjects)
			{
				returnValue.insert(static_cast<const T*>(object));
			}
			return returnValue;
		}

		std::map<language::type::definition::object::Type,
				 std::set<const language::type::definition::object::Base*>>::const_iterator
		begin() const noexcept
		{
			return references.begin();
		}

		std::map<language::type::definition::object::Type,
				 std::set<const language::type::definition::object::Base*>>::const_iterator
		end() const noexcept
		{
			return references.end();
		}

		template<typename T>
		void Add(const T* t)
		{
			constexpr static auto enumValue =
				language::convertor::definition::ObjectTypeToEnum<T>::value;

			references[enumValue].insert(t);
		}

		template<typename T>
		void Add(std::vector<const T*>& ts)
		{
			constexpr static auto enumValue =
				language::convertor::definition::ObjectTypeToEnum<T>::value;

			for (auto* t : ts)
			{
				references[enumValue].insert(t);
			}
		}

		template<typename T>
		void Add(std::vector<T*>& ts)
		{
			constexpr static auto enumValue =
				language::convertor::definition::ObjectTypeToEnum<T>::value;

			for (auto* t : ts)
			{
				references[enumValue].insert(t);
			}
		}

		template<typename T>
		bool Contains(T* reference) const
		{
			using T_stripped = std::remove_cv_t<T>;
			const auto& localReferences_specialized_type = GetBase<T_stripped>();
			const auto& localReferences_base_type =
				GetBase<language::type::definition::object::Base>();

			const auto* reference_stripped = (T_stripped*)reference;

			// if it contains reference to "reference", the count is == 1
			return localReferences_specialized_type.count(reference_stripped) == 1 ||
				   localReferences_base_type.count(reference_stripped) == 1;
		}
	};
}

#endif // DEAMER_TYPE_VECTOR_LDOMULTIVECTOR_H
