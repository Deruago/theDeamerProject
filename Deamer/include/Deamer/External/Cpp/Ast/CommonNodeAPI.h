#ifndef DEAMER_EXTERNAL_CPP_AST_COMMONNODEAPI_H
#define DEAMER_EXTERNAL_CPP_AST_COMMONNODEAPI_H

namespace deamer::external::cpp::ast
{
	/*!	\class CommonNodeAPI
	 *
	 *	\brief This class is used to introduce an common API among several ast nodes.
	 *
	 *	\details This class can be used to introduce common API among several ast/cst nodes.
	 *	This is used by grouped nonterminals, to share common functionality among its subtypes.
	 *
	 *	Note as user you require to create your own template specialization, to implement a custom
	 *API.
	 */
	template<typename T>
	class CommonNodeAPI
	{
	private:
	public:
		CommonNodeAPI() = default;
		virtual ~CommonNodeAPI() = default;

	public:
	};
}

#endif // DEAMER_EXTERNAL_CPP_AST_COMMONNODEAPI_H
