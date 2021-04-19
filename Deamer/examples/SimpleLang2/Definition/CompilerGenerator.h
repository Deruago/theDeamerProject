#ifndef SIMPLELANG2_DEFINITION_COMPILERGENERATOR_H
#define SIMPLELANG2_DEFINITION_COMPILERGENERATOR_H

#include "Deamer/Ast/Generation/CPP/CPP.h"
#include "Deamer/Compiler/Generator/Compiler.h"
#include "Deamer/Lexer/Generator/Flex/Flex.h"
#include "Deamer/Parser/Generator/Bison/Bison.h"
#include "Language.h"

namespace simplelang
{
	class CompilerGenerator : public deamer::compiler::generator::Compiler<Language>
	{
	public:
		CompilerGenerator() : deamer::compiler::generator::Compiler<Language>()
		{
		}

		deamer::file::compiler::Output Generate() override
		{
			deamer::file::compiler::Output output(GetLanguageDefinition());

			deamer::lexer::generator::flex::Flex flex(GetLanguageDefinition());
			deamer::parser::generator::bison::Bison bison(GetLanguageDefinition());
			deamer::ast::generation::cpp::CPP ast(GetLanguageDefinition());

			output.AddLanguageToolOutput(flex.Generate());
			output.AddLanguageToolOutput(bison.Generate());
			output.AddLanguageToolOutput(ast.Generate());

			return output;
		}
		~CompilerGenerator() override = default;
	};
}

#endif // SIMPLELANG2_DEFINITION_COMPILERGENERATOR_H
