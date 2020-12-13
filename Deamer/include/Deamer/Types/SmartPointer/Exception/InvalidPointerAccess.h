/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_TYPES_SMARTPOINTER_EXCEPTION_INVALIDPOINTERACCESS_H
#define DEAMER_TYPES_SMARTPOINTER_EXCEPTION_INVALIDPOINTERACCESS_H

/*
 * Invalid pointer access exception is throwed whenever a smart pointer tries to access a nullpointer.
 * This is illegal, thus causing an invalid pointer access exception.
 */

#include <exception>

namespace deamer
{
	class InvalidPointerAccess : public std::exception
	{
	private:
	    const char* text;
	public:
	    InvalidPointerAccess() : text("Invalid pointer access") {}
	    InvalidPointerAccess(const char* text_) : text(text_) {}

	    const char* what() const noexcept override
	    {
	        return text;
	    }
	};
}

#endif //DEAMER_TYPES_SMARTPOINTER_EXCEPTION_INVALIDPOINTERACCESS_H