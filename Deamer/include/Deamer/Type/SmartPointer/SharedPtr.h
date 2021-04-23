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

#ifndef DEAMER_TYPE_SMARTPOINTER_SHAREDPTR_H
#define DEAMER_TYPE_SMARTPOINTER_SHAREDPTR_H

/*
 * SharedPtr is a pointer that uses reference counting, to automatically deallocate the pointer.
 */

#include "Deamer/Type/SmartPointer/RawPtr.h"
#include "Deamer/Type/SmartPointer/ReferenceCounter.h"

namespace deamer::type
{
	template<typename T>
	class SharedPtr
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
		ReferenceCounter counter;
		
	protected:
		void SetManagedPtr(const ptr managedPtr_)
		{
			managedPtr = managedPtr_;
		}
		ptr GetManagedPtr() const
		{
			return managedPtr;
		}
		void Delete()
		{
			delete managedPtr;
			SetManagedPtr(nullptr);
		}
	public:
		SharedPtr() = default;

		SharedPtr(const ptr managedPtr_)
		{
			this->SetManagedPtr(managedPtr_);
			counter.Initialise();
		}

		SharedPtr(SharedPtr<T>& managedPtr_)
		{
			managedPtr = managedPtr_.GetManagedPtr();
			counter = managedPtr_.counter;
		}

		SharedPtr(SharedPtr<T>&& managedPtr_) noexcept
		{
			managedPtr = managedPtr_.GetManagedPtr();
			counter = managedPtr_.counter;
		}

		SharedPtr(RawPtr<T>& managedPtr_)
		{
			this->SetManagedPtr(managedPtr_.GetManagedPtr());
			managedPtr_.SetManagedPtr(nullptr);
			counter.Initialise();
		}

		SharedPtr(RawPtr<T>&& managedPtr_) noexcept
		{
			this->SetManagedPtr(managedPtr_.GetManagedPtr());
			managedPtr_.SetManagedPtr(nullptr);
			counter.Initialise();
		}
		~SharedPtr()
		{
			if (this->counter.IsLastReference() && this->GetManagedPtr() != nullptr)
			{
				this->Delete();
			}
		}

		SharedPtr<T>& operator=(const SharedPtr<T>& managedPtr_) = delete;
		SharedPtr<T>& operator=(SharedPtr<T>&& managedPtr_) = delete;
		
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

#endif //DEAMER_TYPE_SMARTPOINTER_SHAREDPTR_H
