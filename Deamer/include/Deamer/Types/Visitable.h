/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

/*
 * This class is needed to be implemented into visitable types.
 * By implementing this visitors can be used to visit the derived class.
 * This can be useful for tree like structures.
 */

#ifndef DEAMER_TYPES_VISITABLE_H
#define DEAMER_TYPES_VISITABLE_H
#include "Deamer/Types/Visitor.h"

namespace deamer
{
	template<typename visitor_type>
	class Visitable
	{
	private:
	protected:
	public:
		Visitable() = default;
		virtual ~Visitable() = default;

		void Accept(visitor_type& visitor)
		{
			visitor.dispatch(*this);
		}
	};
}

#endif //DEAMER_TYPES_VISITABLE_H