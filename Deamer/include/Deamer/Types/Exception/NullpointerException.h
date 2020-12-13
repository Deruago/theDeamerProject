/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_TYPES_NULLPOINTEREXCEPTION_H
#define DEAMER_TYPES_NULLPOINTEREXCEPTION_H

 /*
  * CountOutOfRange exception is throwed whenever a counter tries te reduce its count below 0.
  * As the count is only supporting positive numbers, it will throw this error.
  */

#include <exception>

namespace deamer
{
	class NullpointerException : public std::exception
	{
	private:
		const char* text;
	public:
		NullpointerException() : text("Tried to dereference nullpointer.") {}
		NullpointerException(const char* text_) : text(text_) {}

		const char* what() const noexcept override
		{
			return text;
		}
	};
}

#endif //DEAMER_TYPES_NULLPOINTEREXCEPTION_H