#ifndef DEAMER_EXTERNAL_AST_NODE_H
#define DEAMER_EXTERNAL_AST_NODE_H

#include "Deamer/External/Cpp/Ast/GraphTraverser.h"
#include "Deamer/External/Cpp/Lexer/TerminalObject.h"
#include <string>
#include <utility>
#include <vector>

namespace deamer::external::cpp::ast
{
	/*!	\enum NodeValue
	 *
	 *	\brief Defines the different node core types.
	 *
	 *	\details Terminal: it contains a value
	 *	NonTerminal: it contains no value, but has underlying nodes.
	 */
	enum class NodeValue
	{
		unknown,

		terminal,
		nonterminal,

		// contains non terminals or terminals
		vector,
	};

	enum class ProductionRuleType
	{
		unknown,

		user,
		optimization,
		translation,
	};

	/*! \class MatchedProductionRule
	 *
	 *	\brief Contains information about the matched production rule of a given ast.
	 */
	class MatchedProductionRule
	{
	public:
		size_t id;
		ProductionRuleType type;

	public:
		MatchedProductionRule(size_t id_ = 0,
							  ProductionRuleType type_ = ProductionRuleType::unknown)
			: id(id_),
			  type(type_)
		{
		}

		bool operator==(const MatchedProductionRule& rhs) const
		{
			return this->id == rhs.id && this->type == rhs.type;
		}
	};

	class Node;

	class NodeInformation
	{
	public:
		size_t type;
		std::string value;

		int line_number;
		int column_number;

		NodeValue nodeValue;
		Node* parent = nullptr;
		MatchedProductionRule match;

	public:
		NodeInformation() = default;

		template<typename T>
		NodeInformation(T type_, NodeValue nodeValue_, MatchedProductionRule match_,
						std::string value_, int line_number_, int column_number_)
			: type(static_cast<size_t>(type_)),
			  value(std::move(value_)),
			  line_number(line_number_),
			  column_number(column_number_),
			  nodeValue(nodeValue_),
			  match(match_)
		{
		}

		template<typename T>
		NodeInformation(T type_, NodeValue nodeValue_, MatchedProductionRule match_)
			: NodeInformation(type_, nodeValue_, match_, "", -1, -1)
		{
		}

		template<typename T>
		NodeInformation(T type_, NodeValue nodeValue_, std::string value_, int line_number_,
						int column_number_)
			: NodeInformation(type_, nodeValue_, MatchedProductionRule(), value_, line_number_,
							  column_number_)
		{
		}

		template<typename T>
		NodeInformation(T type_, NodeValue nodeValue_, const lexer::TerminalObject* terminalObject)
			: NodeInformation(type_, nodeValue_, MatchedProductionRule(), terminalObject->Value,
							  terminalObject->LineNumber, terminalObject->ColumnNumber)
		{
			delete terminalObject;
		}
	};

	/*!	\class Node
	 *
	 *	\brief Node describing an AST matched symbol.
	 *
	 *	\details When constant, it may modify its nodeinformation.
	 *	This allows us to correctly control the AST.
	 */
	class Node
	{
	private:
		mutable NodeInformation information;

		std::vector<Node*> nodes;
		std::vector<size_t> baseValues;

	public:
		Node() = default;

		Node(NodeInformation information_, std::vector<Node*> nodes_ = {},
			 std::vector<size_t> baseValues_ = {})
			: information(std::move(information_)),
			  nodes(nodes_),
			  baseValues(baseValues_)
		{
			for (const auto* node : nodes)
			{
				node->information.parent = this;
			}
		}

		virtual ~Node()
		{
			for (const auto* node : nodes)
			{
				delete node;
			}
		}

	public:
		/*!	\fn GetNodes
		 *
		 *	\brief Gets all nodes underlying this node.
		 *
		 *	\details Will give a vector of base node types.
		 */
		std::vector<const Node*> GetNodes() const
		{
			std::vector<const Node*> nodesRe;
			for (const auto* node : nodes)
			{
				nodesRe.push_back(node);
			}

			return nodesRe;
		}

		/*!	\fn Get
		 *
		 *	\brief Returns a node based on the enumeration value.
		 */
		template<typename T>
		std::vector<const Node*> Get(T t) const
		{
			const auto t_derived = static_cast<size_t>(t);
			std::vector<const Node*> foundNodes;

			for (const auto* node : nodes)
			{
				if (node->GetType() == t_derived)
				{
					foundNodes.push_back(node);
				}
			}

			return foundNodes;
		}

		template<typename T>
		const Node* Get(T t, size_t index) const
		{
			return Get(t)[index];
		}

		/*!	\fn GetMatchedProductionRule
		 *
		 *	\brief Returns the matched production rule
		 *
		 *	\details The production rule returned, can either be an user defined rule
		 *	or an AST optimization rule.
		 */
		MatchedProductionRule GetMatchedProductionRule() const
		{
			return information.match;
		}

		/*!	\fn GetLineNumber
		 *
		 *	\brief Returns line number of the node
		 *
		 *	\details If the ast is not a terminal, the number returned is 0.
		 */
		size_t GetLineNumber() const
		{
			return information.line_number;
		}

		/*!	\fn GetColumnNumber
		 *
		 *	\brief Returns column number of the node
		 *
		 *	\details If the ast is not a terminal, the number returned is 0.
		 */
		size_t GetColumnNumber() const
		{
			return information.column_number;
		}

		/*!	\fn GetNodeValueType
		 *
		 *	\brief Returns NodeValue type of this node.
		 */
		NodeValue GetNodeValueType() const
		{
			return information.nodeValue;
		}

		/*!	\fn GetType
		 *
		 *	\brief Gives an size_t value representing the AST/CST type.
		 */
		size_t GetType() const
		{
			return information.type;
		}

		std::string GetValue() const
		{
			return information.value;
		}

		const Node* GetParent() const
		{
			return information.parent;
		}

		virtual void Accept(const GraphTraverser& traverser) const
		{
			traverser.Dispatch(this);
		}
	};
}

#endif // DEAMER_EXTERNAL_AST_NODE_H
