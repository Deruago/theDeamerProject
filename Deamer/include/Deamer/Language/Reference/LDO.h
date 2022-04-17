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

#ifndef DEAMER_LANGUAGE_REFERENCE_LDO_H
#define DEAMER_LANGUAGE_REFERENCE_LDO_H

#include "Deamer/Language/Reference/PropertyDefinition.h"
#include "Deamer/Language/Type/Definition/Language.h"
#include <exception>

namespace deamer::language::reference
{
	class LDO_Base
	{
	protected:
		const ::deamer::language::type::definition::object::Base* base;

		LDO_Base(const ::deamer::language::type::definition::object::Base* const base_,
				 const bool check_on_ctor)
			: base(base_)
		{
			if (check_on_ctor)
			{
				if (base_ == nullptr)
				{
					throw std::logic_error("base_ is null-pointer");
				}
			}
		}

	public:
		const ::deamer::language::type::definition::object::Base* GetBaseVariant() const
		{
			return base;
		}
	};

	template<typename T, bool check_on_ctor = false>
	class LDO : public LDO_Base
	{
	public:
		static_assert(!std::is_same_v<T, std::nullptr_t>,
					  "LDO type may not be of type std::nullptr");

		static_assert(std::is_base_of_v<::deamer::language::type::definition::object::Base, T> ||
						  ::std::is_same_v<::deamer::language::type::definition::object::Base, T>,
					  "LDO Should be subclass of the "
					  "::deamer::language::type::definition::object::Base class.");

		using T_bare = T;
		using T_stripped = std::remove_cv_t<std::remove_pointer_t<T>>;
		using type = T_stripped*;
		using const_type = const T_stripped*;
		using const_type_const = const T_stripped* const;

		using type_reference = type&;
		using const_type_const_reference = const_type_const&;

		using base_type = ::deamer::language::type::definition::object::Base*;
		using const_base_type = const ::deamer::language::type::definition::object::Base*;
		using const_base_type_const =
			const ::deamer::language::type::definition::object::Base* const;

	private:
		template<typename T_, bool check_on_ctor_>
		friend class LDO;

	public:
		LDO(const_type_const_reference t) : LDO_Base(t, check_on_ctor)
		{
		}

		LDO(const_base_type_const t) : LDO_Base(t, check_on_ctor)
		{
			if constexpr (check_on_ctor)
			{
				ThrowIfBaseTypeIsInvalid();
			}
		}

		template<typename T_>
		LDO(const LDO<T_, check_on_ctor>& rhs) : LDO_Base(rhs.base, check_on_ctor)
		{
		}

		template<typename T_>
		LDO(const LDO<T_, !check_on_ctor>& rhs) : LDO_Base(rhs.base, check_on_ctor)
		{
		}

		const_type Get() const
		{
			ThrowIfBaseTypeIsInvalid();

			return static_cast<const_type>(base);
		}

		/*! \fn GetRawPointer
		 *
		 *	\brief Returns non const raw pointer dereferenced.
		 *
		 *	\warning If any immutable object is given this function will create a mutable raw
		 *pointer. Thus if the original data was in read only memory, you have a problem (undefined
		 *behaviour). Only use this if you know the data is mutable.
		 */
		type GetRawPointer() const
		{
			ThrowIfBaseTypeIsInvalid();

			return static_cast<type>(
				const_cast<::deamer::language::type::definition::object::Base*>(base));
		}

		const_type operator->() const
		{
			return Get();
		}

		/*!	\fn Verify
		 *
		 *	\brief Verifies if pointer it contains is known in the language.
		 */
		bool Verify(const ::deamer::language::type::definition::Language* const language) const
		{
			for (const auto* const ldo : language->definitionObjects)
			{
				if (ldo == GetBaseVariant())
				{
					return true;
				}
			}

			return false;
		}

		bool Verify(const PropertyDefinitionBase* const reference) const
		{
			return Verify(reference->GetLanguage());
		}

		bool IsBaseTypeValid() const
		{
			return base->Type_ ==
				   ::deamer::language::convertor::definition::ObjectTypeToEnum<T>::value;
		}

		void ThrowIfBaseTypeIsInvalid() const
		{
			if (!IsBaseTypeValid())
			{
				throw std::logic_error("Tried to use incorrect base for LDO reference");
			}
		}

		LDO<T, check_on_ctor>& operator=(const LDO<T, check_on_ctor>& rhs)
		{
			if (this->GetBaseVariant() == rhs.GetBaseVariant())
			{
				return *this;
			}

			this->base = rhs.base;

			return *this;
		}

		template<typename T_, bool check_on_ctor_>
		LDO<T, check_on_ctor>& operator=(const LDO<T_, check_on_ctor_>& rhs)
		{
			if (this->GetBaseVariant() == rhs.GetBaseVariant())
			{
				return *this;
			}

			this->base = rhs.base;

			return *this;
		}
	};

	template<>
	class LDO<::deamer::language::type::definition::object::Base, false> : public LDO_Base
	{
	public:
	private:
		template<typename T_, bool check_on_ctor_>
		friend class LDO;

	public:
		LDO(const ::deamer::language::type::definition::object::Base* t) : LDO_Base(t, false)
		{
		}

		template<typename T_>
		LDO(const LDO<T_, false>& rhs) : LDO_Base(rhs.base, false)
		{
		}

		template<typename T_>
		LDO(const LDO<T_, !false>& rhs) : LDO_Base(rhs.base, false)
		{
		}

		/*!	\fn Promote
		 *
		 *	\brief Promotes the base LDO to any given subtype LDO.
		 */
		template<typename T_>
		LDO<T_, false> Promote() const
		{
			return LDO<T_, false>(this->base);
		}

		const ::deamer::language::type::definition::object::Base* Get() const
		{
			return static_cast<const ::deamer::language::type::definition::object::Base*>(base);
		}

		/*! \fn GetRawPointer
		 *
		 *	\brief Returns non const raw pointer dereferenced.
		 *
		 *	\warning If any immutable object is given this function will create a mutable raw
		 *pointer. Thus if the original data was in read only memory, you have a problem (undefined
		 *behaviour). Only use this if you know the data is mutable.
		 */
		::deamer::language::type::definition::object::Base* GetRawPointer() const
		{
			return const_cast<::deamer::language::type::definition::object::Base*>(base);
		}

		const ::deamer::language::type::definition::object::Base* operator->() const
		{
			return Get();
		}

		/*!	\fn Verify
		 *
		 *	\brief Verifies if pointer it contains is known in the language.
		 */
		bool Verify(const ::deamer::language::type::definition::Language* const language) const
		{
			for (const auto* const ldo : language->definitionObjects)
			{
				if (ldo == GetBaseVariant())
				{
					return true;
				}
			}

			return false;
		}

		bool Verify(const PropertyDefinitionBase* const reference) const
		{
			return Verify(reference->GetLanguage());
		}

		LDO<::deamer::language::type::definition::object::Base, false>&
		operator=(const LDO<::deamer::language::type::definition::object::Base, false>& rhs)
		{
			if (this->GetBaseVariant() == rhs.GetBaseVariant())
			{
				return *this;
			}

			this->base = rhs.base;

			return *this;
		}

		template<typename T_, bool check_on_ctor_>
		LDO<::deamer::language::type::definition::object::Base, false>&
		operator=(const LDO<T_, check_on_ctor_>& rhs)
		{
			if (this->GetBaseVariant() == rhs.GetBaseVariant())
			{
				return *this;
			}

			this->base = rhs.base;

			return *this;
		}
	};

	template<typename T, typename Q, bool check_on_ctor>
	bool operator==(T* const t, LDO<Q, check_on_ctor> q)
	{
		return t == q.GetBaseVariant();
	}

	template<typename T, typename Q, bool check_on_ctor>
	bool operator<(T* const t, LDO<Q, check_on_ctor> q)
	{
		return t < q.GetBaseVariant();
	}

	template<typename T, typename Q, bool check_on_ctor>
	bool operator>(T* const t, LDO<Q, check_on_ctor> q)
	{
		return t > q.GetBaseVariant();
	}

	template<typename T, typename Q, bool check_on_ctor>
	bool operator<=(T* const t, LDO<Q, check_on_ctor> q)
	{
		return t <= q.GetBaseVariant();
	}

	template<typename T, typename Q, bool check_on_ctor>
	bool operator>=(T* const t, LDO<Q, check_on_ctor> q)
	{
		return t >= q.GetBaseVariant();
	}

	template<typename T, typename Q, bool check_on_ctor>
	bool operator==(LDO<T, check_on_ctor> t, Q* const q)
	{
		return t.GetBaseVariant() == q;
	}

	template<typename T, typename Q, bool check_on_ctor>
	bool operator<(LDO<T, check_on_ctor> t, Q* const q)
	{
		return t.GetBaseVariant() < q;
	}

	template<typename T, typename Q, bool check_on_ctor>
	bool operator>(LDO<T, check_on_ctor> t, Q* const q)
	{
		return t.GetBaseVariant() > q;
	}

	template<typename T, typename Q, bool check_on_ctor>
	bool operator<=(LDO<T, check_on_ctor> t, Q* const q)
	{
		return t.GetBaseVariant() <= q;
	}

	template<typename T, typename Q, bool check_on_ctor>
	bool operator>=(LDO<T, check_on_ctor> t, Q* const q)
	{
		return t.GetBaseVariant() >= q;
	}

	template<typename T, typename Q, bool check_on_ctor1, bool check_on_ctor2>
	bool operator==(LDO<T, check_on_ctor1> t, LDO<Q, check_on_ctor2> q)
	{
		return t.GetBaseVariant() == q.GetBaseVariant();
	}

	template<typename T, typename Q, bool check_on_ctor1, bool check_on_ctor2>
	bool operator<(LDO<T, check_on_ctor1> t, LDO<Q, check_on_ctor2> q)
	{
		return t.GetBaseVariant() < q.GetBaseVariant();
	}

	template<typename T, typename Q, bool check_on_ctor1, bool check_on_ctor2>
	bool operator>(LDO<T, check_on_ctor1> t, LDO<Q, check_on_ctor2> q)
	{
		return t.GetBaseVariant() > q.GetBaseVariant();
	}

	template<typename T, bool check_on_ctor1, bool check_on_ctor2>
	bool operator<=(LDO<T, check_on_ctor1> t, LDO<T, check_on_ctor2> q)
	{
		return t.GetBaseVariant() <= q.GetBaseVariant();
	}

	template<typename T, bool check_on_ctor1, bool check_on_ctor2>
	bool operator>=(LDO<T, check_on_ctor1> t, LDO<T, check_on_ctor2> q)
	{
		return t.GetBaseVariant() >= q.GetBaseVariant();
	}
}

#endif // DEAMER_LANGUAGE_REFERENCE_LDO_H
