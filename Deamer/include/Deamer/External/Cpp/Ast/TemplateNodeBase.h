#ifndef DEAMER_EXTERNAL_CPP_AST_TEMPLATENODEBASE_H
#define DEAMER_EXTERNAL_CPP_AST_TEMPLATENODEBASE_H

#include "Deamer/External/Cpp/Ast/Node.h"

namespace deamer::external::cpp::ast
{
	template<typename LanguageBaseNode, typename Derived>
	class TemplateNodeBase : public Node
	{
	public:
		TemplateNodeBase() = default;

		TemplateNodeBase(NodeInformation information_, std::vector<Node*> nodes_ = {},
						 std::vector<size_t> baseValues_ = {})
			: Node(information_, nodes_, baseValues_)
		{
		}

		~TemplateNodeBase() override = default;

	public:
	};
}

#endif // DEAMER_EXTERNAL_CPP_AST_TEMPLATENODEBASE_H
