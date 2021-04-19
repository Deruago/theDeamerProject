#ifndef DEAMER_EXTERNAL_CPP_AST_VISITOR_H
#define DEAMER_EXTERNAL_CPP_AST_VISITOR_H

#include "Deamer/External/Cpp/Ast/GraphTraverser.h"
#include "Deamer/External/Cpp/Ast/Tree.h"

namespace deamer::external::cpp::ast
{
	class Visitor : public GraphTraverser
	{
	private:
	public:
		Visitor() = default;
		virtual ~Visitor() = default;

	public:
	};
}

#endif // DEAMER_EXTERNAL_CPP_AST_VISITOR_H
