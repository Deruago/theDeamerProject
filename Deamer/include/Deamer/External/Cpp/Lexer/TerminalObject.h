#ifndef DEAMER_EXTERNAL_LEXER_TERMINALOBJECT_H
#define DEAMER_EXTERNAL_LEXER_TERMINALOBJECT_H

#include <iostream>
#include <string>
#include <utility>

namespace deamer::external::cpp::lexer
{
	/*!	\class TerminalObject
	 *
	 *	\brief This class is used to contain data about parsed Terminals, in the lexer stage.
	 */
	class TerminalObject
	{
	public:
		const std::string Value;
		const int LineNumber;
		const int ColumnNumber;

	public:
		TerminalObject(std::string value_, const int lineNumber_ = -1, const int columnNumber_ = -1)
			: Value(std::move(value_)),
			  LineNumber(lineNumber_),
			  ColumnNumber(columnNumber_)
		{
		}

		~TerminalObject() = default;

		void Print() const
		{
			std::cout << "Value: " << Value << " Line number: " << LineNumber
					  << " ColumnNumber: " << ColumnNumber << "\n";
		}
	};
}

#endif // DEAMER_EXTERNAL_LEXER_TERMINALOBJECT_H
