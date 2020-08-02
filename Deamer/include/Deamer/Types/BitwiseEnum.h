/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
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
	unsigned operator()() const;

	void operator=(T b);
	void operator|=(T b);
	void operator&=(T b);
	void operator^=(T b);

	unsigned operator&(T b);
	unsigned operator^(T b);
	unsigned operator|(T b);

	bool operator==(std::vector<T> b_vector);
	bool operator!=(std::vector<T> b_vector);
	bool operator==(T b);
	bool operator!=(T b);

	void set_flag(T a);
	void set_flag(T a, bool cond);
	void clear_flag(T a);
	void set_flags(std::vector<T> a_vector);
	void clear_flags(std::vector<T> a_vector);
	
	bool is_flag_set(T a);
	bool is_flag_not_set(T a);
	bool has_flag(T a);
	bool has_flags(T a);
	bool are_flags_set(std::vector<T> a_vector);
	bool are_flags_not_set(std::vector<T> a_vector);
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
unsigned BitwiseEnum<T>::operator&(T b)
{
	return bitwise_value & static_cast<unsigned>(b);
}

template <class T>
unsigned BitwiseEnum<T>::operator^(T b)
{
	return bitwise_value ^ static_cast<unsigned>(b);
}

template <class T>
unsigned BitwiseEnum<T>::operator|(T b)
{
	return bitwise_value | static_cast<unsigned>(b);
}

template <class T>
bool BitwiseEnum<T>::operator==(std::vector<T> b_vector)
{
	for (T b : b_vector)
	{
		if (operator!=(b))
			return false;
	}
	return true;
}

template <class T>
bool BitwiseEnum<T>::operator!=(std::vector<T> b_vector)
{
	for (T b : b_vector)
	{
		if (operator==(b))
			return false;
	}
	return true;
}

template <class T>
bool BitwiseEnum<T>::operator==(T b)
{
	return bitwise_value & static_cast<unsigned>(b);
}

template <class T>
bool BitwiseEnum<T>::operator!=(T b)
{
	return ~bitwise_value & static_cast<unsigned>(b);
}

template <class T>
unsigned BitwiseEnum<T>::value() const
{
	return bitwise_value;
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
bool BitwiseEnum<T>::is_flag_set(T a)
{
	return operator==(a);
}

template <class T>
bool BitwiseEnum<T>::is_flag_not_set(T a)
{
	return operator!=(a);
}

template <class T>
bool BitwiseEnum<T>::has_flag(T a)
{
	return is_flag_set(a);
}

template <class T>
bool BitwiseEnum<T>::has_flags(T a)
{
	return are_flags_set(a);
}

template <class T>
bool BitwiseEnum<T>::are_flags_set(std::vector<T> a_vector)
{
	return operator==(a_vector);
}

template <class T>
bool BitwiseEnum<T>::are_flags_not_set(std::vector<T> a_vector)
{
	return operator!=(a_vector);
}

#endif //DEAMER_TYPES_BITWISEENUM_H
