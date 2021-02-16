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

/*
 * This type is used to extend normal enums to support bit manipulation.
 * Because of the added functionality of bit manipulation. Enums can support flag like behaviour.
 * Which can be useful in some scenario's.
 * Note the enum should manually set enums to values of powers of 2
 */

#ifndef DEAMER_TYPES_BITWISEENUM_H
#define DEAMER_TYPES_BITWISEENUM_H

#include <vector>

template<class T>
class BitwiseEnum
{
public:
	unsigned bitwise_value = 0;

	unsigned value() const;
	T enum_value() const;
	unsigned active_flags() const;
	unsigned operator()() const;

	void operator=(T b);
	void operator|=(T b);
	void operator&=(T b);
	void operator^=(T b);
	
	void operator=(unsigned b);
	void operator|=(unsigned  b);
	void operator&=(unsigned  b);
	void operator^=(unsigned  b);

	unsigned operator&(T b) const;
	unsigned operator^(T b) const;
	unsigned operator|(T b) const;

	bool operator==(std::vector<T> b_vector) const;
	bool operator!=(std::vector<T> b_vector) const;
	bool operator==(T b) const;
	bool operator!=(T b) const;

	void set_flag(T a);
	void set_flag(T a, bool cond);
	void clear_flag(T a);
	void set_flags(std::vector<T> a_vector);
	void clear_flags(std::vector<T> a_vector);
	
	bool is_flag_set(T a) const;
	bool is_flag_not_set(T a) const;
	bool has_flag(T a) const;
	bool has_flags(T a) const;
	bool are_flags_set(std::vector<T> a_vector) const;
	bool are_flags_not_set(std::vector<T> a_vector) const;
};

template <class T>
unsigned BitwiseEnum<T>::operator()() const
{
	return bitwise_value;
}

template <class T>
void BitwiseEnum<T>::operator=(T b)
{
	bitwise_value = static_cast<unsigned>(b);
}

template <class T>
void BitwiseEnum<T>::operator|=(T b)
{
	bitwise_value = operator|(b);
}

template <class T>
void BitwiseEnum<T>::operator&=(T b)
{
	bitwise_value = operator&(b);
}

template <class T>
void BitwiseEnum<T>::operator^=(T b)
{
	bitwise_value = operator^(b);
}

template <class T>
void BitwiseEnum<T>::operator=(unsigned b)
{
	bitwise_value = b;
}

template <class T>
void BitwiseEnum<T>::operator|=(unsigned b)
{
	bitwise_value |= b;
}

template <class T>
void BitwiseEnum<T>::operator&=(unsigned b)
{
	bitwise_value &= b;
}

template <class T>
void BitwiseEnum<T>::operator^=(unsigned b)
{
	bitwise_value ^= b;
}

template <class T>
unsigned BitwiseEnum<T>::operator&(T b) const
{
	return bitwise_value & static_cast<unsigned>(b);
}

template <class T>
unsigned BitwiseEnum<T>::operator^(T b) const
{
	return bitwise_value ^ static_cast<unsigned>(b);
}

template <class T>
unsigned BitwiseEnum<T>::operator|(T b) const
{
	return bitwise_value | static_cast<unsigned>(b);
}

template <class T>
bool BitwiseEnum<T>::operator==(std::vector<T> b_vector) const
{
	for (T b : b_vector)
	{
		if (operator!=(b))
			return false;
	}
	return true;
}

template <class T>
bool BitwiseEnum<T>::operator!=(std::vector<T> b_vector) const
{
	for (T b : b_vector)
	{
		if (operator==(b))
			return false;
	}
	return true;
}

template <class T>
bool BitwiseEnum<T>::operator==(T b) const
{
	return bitwise_value & static_cast<unsigned>(b);
}

template <class T>
bool BitwiseEnum<T>::operator!=(T b) const
{
	return ~bitwise_value & static_cast<unsigned>(b);
}

template <class T>
unsigned BitwiseEnum<T>::value() const
{
	return bitwise_value;
}

template <class T>
T BitwiseEnum<T>::enum_value() const
{
	return static_cast<T>(value());
}

template <class T>
unsigned BitwiseEnum<T>::active_flags() const
{
	unsigned tmp_value = value();
	unsigned active_flags_ = 0;
	while (tmp_value != 0)
	{
		active_flags_ += tmp_value & 1;
		tmp_value >>= 1;
	}
	return active_flags_;
}

template <class T>
void BitwiseEnum<T>::set_flag(T a)
{
	bitwise_value = operator|(a);
}

template <class T>
void BitwiseEnum<T>::set_flag(T a, bool cond)
{
	if (cond)
		set_flag(a);
	else
		clear_flag(a);
}

template <class T>
void BitwiseEnum<T>::clear_flag(T a)
{
	bitwise_value &= ~static_cast<unsigned>(a);
}

template <class T>
void BitwiseEnum<T>::set_flags(std::vector<T> a_vector)
{
	for (T a : a_vector)
		set_flag(a);
}

template <class T>
void BitwiseEnum<T>::clear_flags(std::vector<T> a_vector)
{
	for (T a : a_vector)
		clear_flag(a);
}

template <class T>
bool BitwiseEnum<T>::is_flag_set(T a) const
{
	return operator==(a);
}

template <class T>
bool BitwiseEnum<T>::is_flag_not_set(T a) const
{
	return operator!=(a);
}

template <class T>
bool BitwiseEnum<T>::has_flag(T a) const
{
	return is_flag_set(a);
}

template <class T>
bool BitwiseEnum<T>::has_flags(T a) const
{
	return are_flags_set(a);
}

template <class T>
bool BitwiseEnum<T>::are_flags_set(std::vector<T> a_vector) const
{
	return operator==(a_vector);
}

template <class T>
bool BitwiseEnum<T>::are_flags_not_set(std::vector<T> a_vector) const
{
	return operator!=(a_vector);
}

#endif //DEAMER_TYPES_BITWISEENUM_H
