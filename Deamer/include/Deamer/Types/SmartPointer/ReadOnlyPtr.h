/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_TYPES_SMARTPOINTER_READONLYPTR_H
#define DEAMER_TYPES_SMARTPOINTER_READONLYPTR_H

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

#include "Deamer/Types/SmartPointer/Exception/InvalidPointerAccess.h"
#include "Deamer/Types/SmartPointer/SharedPtr.h"
#include "Deamer/Types/SmartPointer/RawPtr.h"

namespace deamer
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

#endif //DEAMER_TYPES_SMARTPOINTER_READONLYPTR_H