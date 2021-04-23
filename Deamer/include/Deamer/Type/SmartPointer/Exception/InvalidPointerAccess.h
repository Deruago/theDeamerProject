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

#ifndef DEAMER_TYPE_SMARTPOINTER_EXCEPTION_INVALIDPOINTERACCESS_H
#define DEAMER_TYPE_SMARTPOINTER_EXCEPTION_INVALIDPOINTERACCESS_H

/*
 * Invalid pointer access exception is throwed whenever a smart pointer tries to access a nullpointer.
 * This is illegal, thus causing an invalid pointer access exception.
 */

#include <exception>

namespace deamer::type
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

#endif //DEAMER_TYPE_SMARTPOINTER_EXCEPTION_INVALIDPOINTERACCESS_H
