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