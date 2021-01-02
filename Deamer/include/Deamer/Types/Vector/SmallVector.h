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

#ifndef DEAMER_TYPES_VECTOR_SMALLVECTOR_H
#define DEAMER_TYPES_VECTOR_SMALLVECTOR_H

/*
 * SmallVector<class T, size_t vector_size> is a template that allocates vector_size elements in front.
 * This results in better time and space complexity.
 *
 * When using SmallVector as function argument, or you dont know the what kind of SmallVector to expect. Always use SmallVectorBase.
 * Thus using SmallVector only when initializing.
 */

#include <algorithm>
#include <cstring>
#include <utility>

template <class T>
class SmallVectorBase
{
public:
	using iterator = T*;
	using value_type = T;
	using reference = T&;
	using const_reference = const T&;
	
	constexpr size_t element_size() const;
private:
	iterator BeginX = nullptr;
	size_t Size = 0;
	size_t vector_capacity = 0;

	void set_size(const size_t newSize);
	void destroy_range(const T* start, T* end);
	void grow(const size_t newCapacity, const size_t oldCapacity, const size_t elementSize);
	void grow(const size_t newCapacity)
	{
		grow(newCapacity, capacity(), element_size());
	}

	void ReplaceBegin();
	void ReplaceBegin(iterator newBegin);
	void UpdateBegin(const iterator newBegin);

	void DeleteBegin()
	{
		if (BeginX != nullptr)
			delete[] BeginX;
		BeginX = nullptr;
	}

	void InitialiseBegin(const size_t newCapacity)
	{
		DeleteBegin();

		UpdateBegin(new T[newCapacity]);
		vector_capacity = newCapacity;
	}

public:
	SmallVectorBase() = default;
	SmallVectorBase(const size_t newVectorCapacity)
		: vector_capacity(newVectorCapacity)
	{
		InitialiseBegin(vector_capacity);
	}
	SmallVectorBase(const SmallVectorBase& smallVector, const size_t newVectorCapacity)
		: vector_capacity(newVectorCapacity)
	{
		operator=(smallVector);
	}
	SmallVectorBase(SmallVectorBase&& smallVector, const size_t newVectorCapacity)
	{
	};

	SmallVectorBase(const SmallVectorBase& smallVector) : SmallVectorBase(smallVector, smallVector.capacity()) {};
	
	SmallVectorBase& operator=(const SmallVectorBase& smallVector)
	{
		if (this == &smallVector)
			return *this;

		if (smallVector.size() > vector_capacity)
		{
			if (BeginX == nullptr)
				InitialiseBegin(smallVector.size());
			else
				grow(smallVector.size());
		}
		else
		{
			DeleteBegin();
			InitialiseBegin(vector_capacity);
		}

		std::copy(smallVector.begin(), smallVector.end(), BeginX);
		Size = smallVector.size();
		return *this;
	}

	~SmallVectorBase()
	{
		DeleteBegin();
	}
public:
	iterator begin() const;
	iterator end() const;

	void push_back(const T& t);
	void push_back(T&& t);
	void pop_back();

	void clear();

	reference operator[](const size_t n)
	{
		if (n < size())
			return begin()[n];
		return begin()[0];
	}
	
	const_reference operator[](const size_t n) const
	{
		if (n < size())
			return begin()[n];
		return begin()[0];
	}
	
	bool empty() const;
	unsigned capacity() const;
	unsigned size() const;
};

template <class T, size_t vector_size>
class SmallVector : public SmallVectorBase<T>
{
public:
	SmallVector() : SmallVectorBase<T>(vector_size) {};
	SmallVector(const SmallVector& smallVector) : SmallVectorBase<T>(smallVector, vector_size) { };
};

template <class T>
constexpr size_t SmallVectorBase<T>::element_size() const
{
	return sizeof(T);
}

template <class T>
void SmallVectorBase<T>::set_size(const size_t newSize)
{
	if (newSize <= capacity())
		Size = newSize;
}

template <class T>
void SmallVectorBase<T>::push_back(const T& t)
{
	if (Size == capacity())
		grow(capacity() * 2, capacity(), element_size());
	*end() = T(t);
	set_size(Size + 1);
}

template <class T>
void SmallVectorBase<T>::push_back(T&& t)
{
	if (Size == capacity())
		grow(capacity(), capacity(), element_size());
	*end() = T(std::move(t));
	set_size(Size + 1);
}

template <class T>
void SmallVectorBase<T>::pop_back()
{
	set_size(Size - 1);
	end()->~T();
}

template <class T>
void SmallVectorBase<T>::clear()
{
	destroy_range(begin(), end());
	set_size(0);
}

template <class T>
void SmallVectorBase<T>::destroy_range(const T* start, T* end)
{
	while (start != end)
	{
		--end;
		end->~T();
	}
}

template <class T>
void SmallVectorBase<T>::grow(const size_t newCapacity, const size_t oldCapacity, const size_t elementSize)
{
	T* newArray = new T[newCapacity];
	if (newArray == nullptr)
		return;
	
	memcpy(newArray, begin(), oldCapacity * elementSize);

	ReplaceBegin(newArray);
	vector_capacity = newCapacity;
}

template <class T>
void SmallVectorBase<T>::ReplaceBegin()
{
	ReplaceBegin(nullptr);
}

template <class T>
void SmallVectorBase<T>::ReplaceBegin(iterator newBegin)
{
	delete[] BeginX;
	UpdateBegin(newBegin);
}

template <class T>
void SmallVectorBase<T>::UpdateBegin(const iterator newBegin)
{
	BeginX = newBegin;
}

template <class T>
typename SmallVectorBase<T>::iterator SmallVectorBase<T>::begin() const
{
	return BeginX;
}

template <class T>
typename SmallVectorBase<T>::iterator SmallVectorBase<T>::end() const
{
	return begin() + Size;
}

template <class T>
bool SmallVectorBase<T>::empty() const
{
	return Size == 0;
}

template <class T>
unsigned SmallVectorBase<T>::capacity() const
{
	return vector_capacity;
}

template <class T>
unsigned SmallVectorBase<T>::size() const
{
	return Size;
}

#endif //DEAMER_TYPES_VECTOR_SMALLVECTOR_H
