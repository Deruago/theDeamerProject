/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_TYPES_VISITOR_H
#define DEAMER_TYPES_VISITOR_H

namespace deamer
{
	class Visitor
	{
	private:
	protected:
	public:
		Visitor() = default;
		virtual ~Visitor() = default;
	};
}

#endif //DEAMER_TYPES_VISITOR_H