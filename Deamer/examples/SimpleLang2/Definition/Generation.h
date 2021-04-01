#ifndef SIMPLELANG2_DEFINITION_GENERATION_H
#define SIMPLELANG2_DEFINITION_GENERATION_H

#include "Deamer/Language/Generator/Definition/Property/User/Special/Generation.h"

namespace simplelang
{
	class Language;

	class Generation : public deamer::language::generator::definition::property::user::Generation<
						   simplelang::Language>
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
			grammarDebug;
		deamer::type::SafeReserve<
			deamer::language::type::definition::object::main::GenerateArgument>
			grammarDeclareDeletedTerminals;
		deamer::type::SafeReserve<
			deamer::language::type::definition::object::main::GenerateArgument>
			grammarVector;

	public:
		Generation(simplelang::Language* language)
			: deamer::language::generator::definition::property::user::Generation<
				  simplelang::Language>(language)
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

			lexerDebug.Set(deamer::language::type::definition::object::main::GenerateArgument(
				deamer::tool::type::Tool::Flex, "Debug"));
			grammarDebug.Set(deamer::language::type::definition::object::main::GenerateArgument(
				deamer::tool::type::Tool::Bison, "Debug"));
			grammarDeclareDeletedTerminals.Set(
				deamer::language::type::definition::object::main::GenerateArgument(
					deamer::tool::type::Tool::Bison, "Declare-deleted-terminals"));
			grammarVector.Set(deamer::language::type::definition::object::main::GenerateArgument(
				deamer::tool::type::Tool::Bison, "Vector"));

			AddObject(generateLexer);
			AddObject(generateParser);

			AddObject(integrateLexerAndParser);
			AddObject(integrateLexerAndDeamerAST);
			AddObject(integrateParserAndDeamerAST);

			AddObject(lexerDebug);
			AddObject(grammarDebug);
			AddObject(grammarDeclareDeletedTerminals);
			AddObject(grammarVector);
		}
		~Generation() override = default;
	};
}

#endif // SIMPLELANG2_DEFINITION_GENERATION_H
