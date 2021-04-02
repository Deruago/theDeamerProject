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

#include "Deamer/Language/Type/Definition/Language.h"

namespace deamer::language::reference
{
	class LDO_Base
	{
	protected:
		const type::definition::object::Base* const base;

		LDO_Base(const type::definition::object::Base* const base_, const bool check_on_ctor)
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
		const type::definition::object::Base* GetBaseVariant() const
		{
			return base;
		}
	};

	template<typename T, bool check_on_ctor = false>
	class LDO : public LDO_Base
	{
	public:
		using T_stripped = std::remove_cv_t<std::remove_pointer_t<T>>;
		using type = T_stripped*;
		using const_type = const T_stripped*;
		using const_type_const = const T_stripped* const;

		using base_type = type::definition::object::Base*;
		using const_base_type = const type::definition::object::Base*;
		using const_base_type_const = const type::definition::object::Base* const;

	private:
		friend LDO<T_stripped, !check_on_ctor>;

	public:
		LDO(const_type_const t) : LDO_Base(t, check_on_ctor)
		{
		}

		LDO(const_base_type_const t) : LDO_Base(t, check_on_ctor)
		{
			if constexpr (check_on_ctor)
			{
				ThrowIfBaseTypeIsInvalid();
			}
		}

		LDO(const LDO& rhs) : LDO_Base(rhs.base, check_on_ctor)
		{
		}

		LDO(const LDO<T_stripped, !check_on_ctor>& rhs) : LDO_Base(rhs.base, check_on_ctor)
		{
		}

		const_type Get() const
		{
			ThrowIfBaseTypeIsInvalid();

			return static_cast<const_type>(base);
		}

		const_type operator->() const
		{
			return Get();
		}

		/*!	\fn Verify
		 *
		 *	\brief Verifies if pointer it contains is known in the language.
		 */
		bool Verify(type::definition::Language* language) const
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

		bool IsBaseTypeValid() const
		{
			return base->Type_ == convertor::definition::ObjectTypeToEnum<T>::value;
		}

		void ThrowIfBaseTypeIsInvalid() const
		{
			if (!IsBaseTypeValid())
			{
				throw std::logic_error("Tried to use incorrect base for LDO reference");
			}
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

	template<typename T, bool check_on_ctor1, bool check_on_ctor2>
	bool operator==(LDO<T, check_on_ctor1> t, LDO<T, check_on_ctor2> q)
	{
		return t.GetBaseVariant() == q.GetBaseVariant();
	}

	template<typename T, bool check_on_ctor1, bool check_on_ctor2>
	bool operator<(LDO<T, check_on_ctor1> t, LDO<T, check_on_ctor2> q)
	{
		return t.GetBaseVariant() < q.GetBaseVariant();
	}

	template<typename T, bool check_on_ctor1, bool check_on_ctor2>
	bool operator>(LDO<T, check_on_ctor1> t, LDO<T, check_on_ctor2> q)
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
