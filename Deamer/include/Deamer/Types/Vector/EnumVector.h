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

#ifndef DEAMER_TYPES_VECTOR_ENUMVECTOR_H
#define DEAMER_TYPES_VECTOR_ENUMVECTOR_H

/*
 * EnumVector is a vector that allocates and directly maps Enums to spots in the vector. This makes the use
 * of outside switch statements redundant. It is a better alternative to std::map.
 *
 * Using this vector you don't need a map to map enum with spots.
 *
 * Note the efficiency is only available when using clang++ with -O2 OR GCC -O1
 * Using this this vector is as efficient as inline switch case enum to index mapping.
 */

#include <algorithm>
#include <utility>

template<size_t n>
class EnumVectorBase
{
	
};

template<class T, class E, const E... Es>
class EnumVector
{
public:
	using iterator = T*;
	using value_type = T;
	using reference = T&;
	using const_reference = const T&;
private:
	constexpr static size_t enum_n = sizeof...(Es);
	iterator BeginX;
private:
	template <const E ... Is>
	unsigned GetIndex(const E i, const std::integer_sequence<E, Is...>) {
		auto ret = -1;
		auto count = 0;
		std::initializer_list<int>({ (i == Is ? (ret = count) : count++)... });
		return ret;
	}

	unsigned GetIndex(const E i)
	{
		auto is = std::integer_sequence<E, Es...>{};
		return GetIndex(i, is);
	}
public:
	EnumVector()
	{
		BeginX = new T[enum_n];
	}


	T& operator[](const E e)
	{
		const unsigned index = GetIndex(e);
		return BeginX[index];
	}

	T& operator[](const size_t n)
	{
		return BeginX[n];
	}
};

/*

switch(enumType)
{
case type::a:
	return 1;
case type::b:
	return 2;
case type::c:
	return 3;
case type::d:
	return 4;

}


1. make sequence
2. input something
3. get something from sequence

//*/

#endif //DEAMER_TYPES_VECTOR_ENUMVECTOR_H