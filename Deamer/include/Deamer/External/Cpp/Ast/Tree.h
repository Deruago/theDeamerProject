#ifndef DEAMER_EXTERNAL_AST_TREE_H
#define DEAMER_EXTERNAL_AST_TREE_H

#include "Deamer/External/Cpp/Ast/Node.h"

namespace deamer::external::cpp::ast
{
	class Tree
	{
	private:
		const Node* startNode = nullptr;

	public:
		Tree() = default;
		Tree(Node* const node) : startNode(node)
		{
		}
		virtual ~Tree()
		{
			delete startNode;
		}

		void SetStartNode(Node* const node)
		{
			startNode = node;
		}

		const Node* GetStartNode() const
		{
			return startNode;
		}
	};
}

#endif // DEAMER_EXTERNAL_AST_TREE_H
