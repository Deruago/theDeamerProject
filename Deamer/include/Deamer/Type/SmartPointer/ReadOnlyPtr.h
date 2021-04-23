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

#ifndef DEAMER_TYPE_SMARTPOINTER_READONLYPTR_H
#define DEAMER_TYPE_SMARTPOINTER_READONLYPTR_H

 /*
  * The RawPtr is a pointer that doesnt deallocate, unless explicitly stated.
  * The benefit of using RawPtr instead of a standard pointer, is that this pointer can be used for:
  *		- Deep copies
  *		- Deleting the pointer
  *		- Initialise Smart Pointers made with Deamer
  *		- Safe access to pointer, if it is nullpointer it throws an error.
  *
  *	It is the base of all Deamer Smart Pointers
  */

#include "Deamer/Type/SmartPointer/Exception/InvalidPointerAccess.h"
#include "Deamer/Type/SmartPointer/SharedPtr.h"
#include "Deamer/Type/SmartPointer/RawPtr.h"

namespace deamer::type
{
	template<typename T>
	class ReadOnlyPtr
	{
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
		ReadOnlyPtr() = default;

		ReadOnlyPtr(const ptr managedPtr_)
		{
			SetManagedPtr(managedPtr_);
		}
		ReadOnlyPtr(ReadOnlyPtr<T>& managedPtr_) : ReadOnlyPtr(managedPtr_.GetManagedPtr())
		{
		}
		ReadOnlyPtr(ReadOnlyPtr<T>&& managedPtr_) noexcept : ReadOnlyPtr(managedPtr_.GetManagedPtr())
		{
		}
		ReadOnlyPtr(SharedPtr<T>& managedPtr_) : ReadOnlyPtr(managedPtr_.GetManagedPtr())
		{
		}
		ReadOnlyPtr(SharedPtr<T>&& managedPtr_) noexcept : ReadOnlyPtr(managedPtr_.GetManagedPtr())
		{
		}
		ReadOnlyPtr(RawPtr<T>& managedPtr_) : ReadOnlyPtr(managedPtr_.GetManagedPtr())
		{
		}
		ReadOnlyPtr(RawPtr<T>&& managedPtr_) noexcept : ReadOnlyPtr(managedPtr_.GetManagedPtr())
		{
		}

		ReadOnlyPtr<T>& operator=(const ReadOnlyPtr<T>& managedPtr_) = delete;
		ReadOnlyPtr<T>& operator=(ReadOnlyPtr<T>&& managedPtr_) = delete;

		~ReadOnlyPtr()
		{
			managedPtr = nullptr;
		}

		ptr operator->() const
		{
			if (managedPtr == nullptr)
			{
				throw InvalidPointerAccess{};
			}
			return managedPtr;
		}

		bool IsDeleted() const
		{
			return managedPtr == nullptr;
		}
	};
}

#endif //DEAMER_TYPE_SMARTPOINTER_READONLYPTR_H
