/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_TYPES_SMARTPOINTER_DEEPCOPUAUTOPTR_H
#define DEAMER_TYPES_SMARTPOINTER_DEEPCOPUAUTOPTR_H

/*
 * DeepCopyAutoPtr is a ptr that deep-copies itself whenever a copy happens, but moves itself when it gets moved.
 * This is useful for when you want to have the BaseAutoPtr behaviour, but added that you can copy it properly.
 * Note:
 *		- When moving the pointer, it transfers ownership
 *		- When copying the pointer, it will create a deep copy
 */

#include "Deamer/Types/SmartPointer/BaseAutoPtr.h"

namespace deamer
{
	template<typename T>
	class DeepCopyAutoPtr
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
		DeepCopyAutoPtr(const ptr managedPtr_)
		{
			this->SetManagedPtr(managedPtr_);
		}
		
		DeepCopyAutoPtr(RawPtr<T> managedPtr_) : DeepCopyAutoPtr<T>(managedPtr_.GetManagedPtr())
		{
			managedPtr_.SetManagedPtr(nullptr);
		}

		DeepCopyAutoPtr(DeepCopyAutoPtr<T>& managedPtr_)
		{
			const RawPtr<T> deepCopy = managedPtr_.DeepCopy();
			this->SetManagedPtr(deepCopy.GetManagedPtr());
		}

		DeepCopyAutoPtr(DeepCopyAutoPtr<T>&& managedPtr_) noexcept : BaseAutoPtr<T>(managedPtr_.GetManagedPtr())
		{
			managedPtr_.SetManagedPtr(nullptr);
		}

		~DeepCopyAutoPtr()
		{
			if (this->GetManagedPtr() != nullptr)
			{
				this->Delete();
			}
		}

		DeepCopyAutoPtr<T>& operator=(const DeepCopyAutoPtr<T>& managedPtr_) = delete;
		DeepCopyAutoPtr<T>& operator=(DeepCopyAutoPtr<T>&& managedPtr_) = delete;

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

		bool IsDeleted() const
		{
			return managedPtr == nullptr;
		}
	};
}

#endif //DEAMER_TYPES_SMARTPOINTER_DEEPCOPUAUTOPTR_H