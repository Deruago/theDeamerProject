/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
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

	template<typename T>
	class RawPtr
	{
		friend BaseAutoPtr<T>;
		friend DeepCopyAutoPtr<T>;
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

		bool IsDeleted() const
		{
			return managedPtr == nullptr;
		}
	};
}

#endif //DEAMER_TYPES_SMARTPOINTER_RAWPTR_H