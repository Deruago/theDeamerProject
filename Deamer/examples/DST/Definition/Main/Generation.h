#ifndef DST_MAIN_DEFINITION_GENERATION_H
#define DST_MAIN_DEFINITION_GENERATION_H

#include "Deamer/Language/Generator/Definition/Property/User/Special/Generation.h"

namespace DST::main
{
	class Language;

	class Generation : public deamer::language::generator::definition::property::user::Generation<
						   DST::main::Language>
	{
	private:
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Generate>
			generateLexer;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Generate>
			generateParser;

		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Integrate>
			integrateLexerAndParser;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Integrate>
			integrateLexerAndDeamerAST;
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Integrate>
			integrateParserAndDeamerAST;

		deamer::type::SafeReserve<
			deamer::language::type::definition::object::main::GenerateArgument>
			lexerDebug;
		deamer::type::SafeReserve<
			deamer::language::type::definition::object::main::GenerateArgument>
			lexerOutputTerminalObjects;
		deamer::type::SafeReserve<
			deamer::language::type::definition::object::main::GenerateArgument>
			grammarDebug;
		deamer::type::SafeReserve<
			deamer::language::type::definition::object::main::GenerateArgument>
			grammarDeclareDeletedTerminals;
		deamer::type::SafeReserve<
			deamer::language::type::definition::object::main::GenerateArgument>
			grammarVector;

	public:
		Generation(DST::main::Language* language)
			: deamer::language::generator::definition::property::user::Generation<
				  DST::main::Language>(language)
		{
			generateLexer.Set(deamer::language::type::definition::object::main::Generate(
				deamer::tool::type::Tool::Flex));
			generateParser.Set(deamer::language::type::definition::object::main::Generate(
				deamer::tool::type::Tool::Bison));

			integrateLexerAndParser.Set(deamer::language::type::definition::object::main::Integrate(
				deamer::tool::type::Tool::Flex, deamer::tool::type::Tool::Bison));
			integrateLexerAndDeamerAST.Set(
				deamer::language::type::definition::object::main::Integrate(
					deamer::tool::type::Tool::Flex, deamer::tool::type::Tool::DeamerAST));
			integrateParserAndDeamerAST.Set(
				deamer::language::type::definition::object::main::Integrate(
					deamer::tool::type::Tool::Bison, deamer::tool::type::Tool::DeamerAST));

			/*lexerDebug.Set(deamer::language::type::definition::object::main::GenerateArgument(
				deamer::tool::type::Tool::Flex, "Debug"));*/
			lexerOutputTerminalObjects.Set(
				deamer::language::type::definition::object::main::GenerateArgument(
					deamer::tool::type::Tool::Flex, "Output-terminal-objects"));
			/*grammarDebug.Set(deamer::language::type::definition::object::main::GenerateArgument(
				deamer::tool::type::Tool::Bison, "Debug"));*/
			grammarDeclareDeletedTerminals.Set(
				deamer::language::type::definition::object::main::GenerateArgument(
					deamer::tool::type::Tool::Bison, "Declare-deleted-terminals"));
			/*grammarVector.Set(deamer::language::type::definition::object::main::GenerateArgument(
				deamer::tool::type::Tool::Bison, "Vector"));*/

			AddObject(generateLexer);
			AddObject(generateParser);

			AddObject(integrateLexerAndParser);
			AddObject(integrateLexerAndDeamerAST);
			AddObject(integrateParserAndDeamerAST);

			AddObject(lexerDebug);
			AddObject(lexerOutputTerminalObjects);
			AddObject(grammarDebug);
			AddObject(grammarDeclareDeletedTerminals);
			AddObject(grammarVector);
		}
		~Generation() override = default;
	};
}

#endif // DST_MAIN_DEFINITION_GENERATION_H
