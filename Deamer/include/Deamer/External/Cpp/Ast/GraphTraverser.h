#ifndef DEAMER_EXTERNAL_CPP_AST_GRAPHTRAVERSER_H
#define DEAMER_EXTERNAL_CPP_AST_GRAPHTRAVERSER_H

namespace deamer::external::cpp::ast
{
	class Node;

	class GraphTraverser
	{
	private:
	public:
		GraphTraverser() = default;
		virtual ~GraphTraverser() = default;

	public:
		virtual void Dispatch(const Node* node) const = 0;
	};
}

#endif // DEAMER_EXTERNAL_CPP_AST_GRAPHTRAVERSER_H
