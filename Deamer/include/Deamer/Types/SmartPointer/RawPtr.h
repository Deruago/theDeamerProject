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

#ifndef DEAMER_TYPES_SMARTPOINTER_RAWPTR_H
#define DEAMER_TYPES_SMARTPOINTER_RAWPTR_H

/*
 * The RawPtr is a pointer that doesnt deallocate, unless explicitly stated.
 * The benefit of using RawPtr instead of a standard pointer, is that this pointer can be used for:
 *		- Deep copies
 *		- Deleting the pointer
 *		- Initialise Smart Pointers made with Deamer
 *		- Safe access to pointer, if it is nullpointer it throws an error.
 */

#include "Deamer/Types/SmartPointer/Exception/InvalidPointerAccess.h"

namespace deamer
{
	template<typename T> class BaseAutoPtr;
	template<typename T> class DeepCopyAutoPtr;
	template<typename T> class SharedPtr;

	template<typename T>
	class RawPtr
	{
		friend BaseAutoPtr<T>;
		friend DeepCopyAutoPtr<T>;
		friend SharedPtr<T>;
	public:
		using ptr = T*;
		using const_ptr = const T* const;
		using value_type = T;
		using reference = T&;
		using const_reference = const T&;
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
		RawPtr() = default;

		RawPtr(const ptr managedPtr_)
		{
			SetManagedPtr(managedPtr_);
		}
		RawPtr(RawPtr<T>& managedPtr_) : RawPtr(managedPtr_.GetManagedPtr())
		{
		}
		RawPtr(RawPtr<T>&& managedPtr_) noexcept : RawPtr(managedPtr_.GetManagedPtr())
		{
			managedPtr_.SetManagedPtr(nullptr);
		}

		RawPtr<T>& operator=(const RawPtr<T>& managedPtr_)
		{
			if (&managedPtr_ == this)
				return *this;

			SetManagedPtr(managedPtr_.GetManagedPtr());
			return *this;
		}
		
		RawPtr<T>& operator=(RawPtr<T>&& managedPtr_) noexcept
		{
			managedPtr_.SetManagedPtr(nullptr);
			
			SetManagedPtr(managedPtr_.GetManagedPtr());
			return *this;
		}

		void Delete()
		{
			delete managedPtr;
			SetManagedPtr(nullptr);
		}

		~RawPtr() = default;

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

		bool operator==(const ptr comparedPtr)
		{
			return managedPtr == comparedPtr;
		}
		
		bool operator==(const_ptr comparedPtr)
		{
			return managedPtr == comparedPtr;
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

#endif //DEAMER_TYPES_SMARTPOINTER_RAWPTR_H