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

#ifndef DEAMER_LANGUAGE_EXCEPTION_REQUESTEDPROPERTYDEFINITIONNOTFOUND_H
#define DEAMER_LANGUAGE_EXCEPTION_REQUESTEDPROPERTYDEFINITIONNOTFOUND_H

#include <exception>

namespace deamer::language::exception
{
	/*! \class RequestedPropertyDefinitionNotFound
	 *
	 *	\brief This is thrown by property references, when they cannot find a requested definition.
	 */
	class RequestedPropertyDefinitionNotFound final : public std::exception
	{
	public:
		RequestedPropertyDefinitionNotFound() : std::exception()
		{
		}

		char const* what() const noexcept override
		{
			return "Requested definition couldn't be found.";
		}
	};
}

#endif //DEAMER_LANGUAGE_EXCEPTION_REQUESTEDPROPERTYDEFINITIONNOTFOUND_H
