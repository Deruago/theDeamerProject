/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/Types/BitwiseEnum.h"

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
void BitwiseEnum<T>::clear_flag(T a)
{
	bitwise_value &= ~static_cast<unsigned>(a);
}

template <class T>
void BitwiseEnum<T>::set_flags(std::vector<T> a_vector)
{
	for(T a : a_vector)
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
bool BitwiseEnum<T>::are_flags_set(std::vector<T> a_vector)
{
	return operator==(a_vector);
}

template <class T>
bool BitwiseEnum<T>::are_flags_not_set(std::vector<T> a_vector)
{
	return operator!=(a_vector);
}