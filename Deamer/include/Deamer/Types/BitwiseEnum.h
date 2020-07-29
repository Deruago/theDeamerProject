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
	void clear_flag(T a);
	void set_flags(std::vector<T> a_vector);
	void clear_flags(std::vector<T> a_vector);
	
	bool is_flag_set(T a);
	bool is_flag_not_set(T a);
	bool are_flags_set(std::vector<T> a_vector);
	bool are_flags_not_set(std::vector<T> a_vector);
};

#endif //DEAMER_TYPES_BITWISEENUM_H
