#ifndef SIMPLELANG2_DEFINITION_COMPILERGENERATOR_H
#define SIMPLELANG2_DEFINITION_COMPILERGENERATOR_H

#include "Deamer/Compiler/Generator/Compiler.h"
#include "Deamer/Lexer/Generator/Flex/Flex.h"
#include "Language.h"

namespace simplelang
{
	class CompilerGenerator : public deamer::compiler::generator::Compiler<Language>
	{
	public:
		CompilerGenerator() : Compiler()
		{
		}
		deamer::file::compiler::Output Generate() override
		{
			deamer::file::compiler::Output output(GetLanguageDefinition());

			deamer::lexer::generator::flex::Flex flex(GetLanguageDefinition());
			output.AddLanguageToolOutput(flex.Generate());

			return output;
		}
		~CompilerGenerator() override = default;
	};
}

#endif // SIMPLELANG2_DEFINITION_COMPILERGENERATOR_H
