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

#ifndef DEAMER_TYPE_SMARTPOINTER_BASEAUTOPTR_H
#define DEAMER_TYPE_SMARTPOINTER_BASEAUTOPTR_H

/*
 * BaseAutoPtr is a simple managed pointer that deallocates itself after it runs out of scope.
 * BaseAutoPtr is the base of most smart pointers, that automatically delete themselves, when they run out of scope.
 * Smart pointers that don't automatically delete themselves when running out of scope, use RawPtr as base instead.
 * 
 * Whenever you move or copy this pointer, the ownership is moved as well.
 * When you try to call the old smart pointer, it will throw an exception.
 *
 * Note: every copy and move will transfer ownership.
 */

#include "Deamer/Type/SmartPointer/RawPtr.h"

namespace deamer::type
{
	template<typename T>
	class BaseAutoPtr
	{
	public:
		using ptr = T*;
		using const_ptr = const T* const;
		using value_type = T;
		using reference = T&;
		using const_reference = const T&;
		constexpr static auto T_size = sizeof(T);
	private:
		ptr managedPtr = nullptr;
	protected:
		void SetManagedPtr(const ptr managedPtr_)
		{
			managedPtr = managedPtr_;
		}
		ptr GetManagedPtr() const
		{
			return managedPtr;
		}
	public:
		BaseAutoPtr() = default;
		
		BaseAutoPtr(const ptr managedPtr_)
		{
			this->SetManagedPtr(managedPtr_);
		}

		BaseAutoPtr(BaseAutoPtr<T>& managedPtr_) : BaseAutoPtr<T>(managedPtr_.GetManagedPtr())
		{
			managedPtr_.SetManagedPtr(nullptr);
		}

		BaseAutoPtr(BaseAutoPtr<T>&& managedPtr_) noexcept : BaseAutoPtr<T>(managedPtr_.GetManagedPtr())
		{
			managedPtr_.SetManagedPtr(nullptr);
		}

		BaseAutoPtr(RawPtr<T>& managedPtr_) : BaseAutoPtr<T>(managedPtr_.GetManagedPtr())
		{
			managedPtr_.SetManagedPtr(nullptr);
		}

		BaseAutoPtr(RawPtr<T>&& managedPtr_) noexcept : BaseAutoPtr<T>(managedPtr_.GetManagedPtr())
		{
			managedPtr_.SetManagedPtr(nullptr);
		}

		~BaseAutoPtr()
		{
			if (this->GetManagedPtr() != nullptr)
			{
				this->Delete();
			}
		}

		BaseAutoPtr<T>& operator=(const BaseAutoPtr<T>& managedPtr_) = delete;
		BaseAutoPtr<T>& operator=(BaseAutoPtr<T>&& managedPtr_) = delete;

		void Delete()
		{
			delete managedPtr;
			SetManagedPtr(nullptr);
		}

		ptr operator->() const
		{
			if (managedPtr == nullptr)
			{
				throw InvalidPointerAccess{};
			}
			return managedPtr;
		}

		RawPtr<T> DeepCopy() const
		{
			if (managedPtr == nullptr)
			{
				throw InvalidPointerAccess{};
			}

			ptr newManagedPtr = new T(*managedPtr);
			RawPtr<T> newRawPtr(newManagedPtr);
			return newRawPtr;
		}

		T& GetReferenceToItem() const
		{
			return *managedPtr;
		}

		bool IsDeleted() const
		{
			return managedPtr == nullptr;
		}
	};
}

#endif //DEAMER_TYPE_SMARTPOINTER_BASEAUTOPTR_H
