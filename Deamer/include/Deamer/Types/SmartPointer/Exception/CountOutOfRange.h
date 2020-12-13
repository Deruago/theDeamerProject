/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_TYPES_SMARTPOINTER_EXCEPTION_COUNTOUTOFRANGE_H
#define DEAMER_TYPES_SMARTPOINTER_EXCEPTION_COUNTOUTOFRANGE_H

 /*
  * CountOutOfRange exception is throwed whenever a counter tries te reduce its count below 0.
  * As the count is only supporting positive numbers, it will throw this error.
  */

#include <exception>

namespace deamer
{
	class CountOutOfRange : public std::exception
	{
	private:
		const char* text;
	public:
		CountOutOfRange() : text("Count is out of range.") {}
		CountOutOfRange(const char* text_) : text(text_) {}

		const char* what() const noexcept override
		{
			return text;
		}
	};
}

#endif //DEAMER_TYPES_SMARTPOINTER_EXCEPTION_COUNTOUTOFRANGE_H