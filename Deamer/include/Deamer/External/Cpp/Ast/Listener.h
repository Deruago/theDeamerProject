#ifndef DEAMER_EXTERNAL_CPP_AST_LISTENER_H
#define DEAMER_EXTERNAL_CPP_AST_LISTENER_H

#include "Deamer/External/Cpp/Ast/GraphTraverser.h"
#include "Deamer/External/Cpp/Ast/Tree.h"

namespace deamer::external::cpp::ast
{
	class Listener : public GraphTraverser
	{
	private:
	public:
		Listener() = default;
		virtual ~Listener() = default;
	};
}

#endif // DEAMER_EXTERNAL_CPP_AST_LISTENER_H
