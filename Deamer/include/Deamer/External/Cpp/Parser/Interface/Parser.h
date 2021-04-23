#ifndef DEAMER_EXTERNAL_PARSER_INTERFACE_PARSER_H
#define DEAMER_EXTERNAL_PARSER_INTERFACE_PARSER_H

#include "Deamer/External/Cpp/Ast/Tree.h"
#include <string>

namespace deamer::external::cpp::parser
{
	class Parser
	{
	public:
		Parser() = default;
		virtual ~Parser() = default;

	public:
		virtual ast::Tree* Parse(const std::string& text) const = 0;
	};
}

#endif // DEAMER_EXTERNAL_PARSER_INTERFACE_PARSER_H
