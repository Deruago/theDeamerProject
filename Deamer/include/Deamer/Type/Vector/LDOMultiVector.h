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
			const auto& foundObjects =
				references[language::convertor::definition::ObjectTypeToEnum<T>::value];

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
		void Add(const T* const t)
		{
			references[language::convertor::definition::ObjectTypeToEnum<T>::value].insert(t);
		}

		template<typename T>
		void Add(std::vector<const T*>& ts)
		{
			for (auto* t : ts)
			{
				references[language::convertor::definition::ObjectTypeToEnum<T>::value].insert(t);
			}
		}

		template<typename T>
		void Add(std::vector<T*>& ts)
		{
			for (auto& t : ts)
			{
				references[language::convertor::definition::ObjectTypeToEnum<T>::value].insert(t);
			}
		}

		template<typename T>
		bool Contains(T* reference) const
		{
			const auto& localReferences = GetBase<T>();

			// if it contains reference to "reference", the count is > 0
			return localReferences.count(reference) > 0;
		}
	};
}

#endif // DEAMER_TYPE_VECTOR_LDOMULTIVECTOR_H
