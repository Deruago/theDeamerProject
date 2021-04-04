#ifndef DEAMER_EXTERNAL_LEXER_INTERFACE_LEXER_H
#define DEAMER_EXTERNAL_LEXER_INTERFACE_LEXER_H

#include "Deamer/External/Cpp/Lexer/TerminalObject.h"
#include <string>
#include <vector>

namespace deamer::external::cpp::lexer
{
	class Lexer
	{
	public:
		Lexer() = default;
		virtual ~Lexer() = default;

	public:
		virtual std::vector<const TerminalObject*> Tokenize(const std::string& text) const = 0;
	};
}

#endif // DEAMER_EXTERNAL_LEXER_INTERFACE_LEXER_H
