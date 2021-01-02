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
 * This class is needed to be implemented into visitable types.
 * By implementing this visitors can be used to visit the derived class.
 * This can be useful for tree like structures.
 */

#ifndef DEAMER_TYPES_VISITABLE_H
#define DEAMER_TYPES_VISITABLE_H

namespace deamer
{
	template<typename Derived, typename visitor_type>
	class Visitable
	{
	private:
	protected:
	public:
		Visitable() = default;
		virtual ~Visitable() = default;

		void Accept(visitor_type& visitor)
		{
			visitor.dispatch(static_cast<Derived&>(*this));
		}
	};
}

#endif //DEAMER_TYPES_VISITABLE_H