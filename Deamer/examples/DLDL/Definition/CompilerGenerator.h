#ifndef DLDL_DEFINITION_COMPILERGENERATOR_H
#define DLDL_DEFINITION_COMPILERGENERATOR_H

#include "Deamer/Compiler/Generator/Compiler.h"
#include "Language.h"
#include "Grammar/CompilerGenerator.h"
#include "Lexer/CompilerGenerator.h"

namespace DLDL
{
	class CompilerGenerator : public ::deamer::compiler::generator::Compiler<::DLDL::Language>,
							  public ::DLDL::lexer::CompilerGenerator,
							  public ::DLDL::grammar::CompilerGenerator
	{
	public:
		CompilerGenerator()
			: deamer::compiler::generator::Compiler<::DLDL::Language>(),
			  ::DLDL::lexer::CompilerGenerator(),
			  ::DLDL::grammar::CompilerGenerator()
		{
		}

		deamer::file::compiler::Output Generate() override
		{
			deamer::file::compiler::Output output(
				deamer::compiler::generator::Compiler<::DLDL::Language>::GetLanguageDefinition());

			output.AddCompilerOutput(::DLDL::lexer::CompilerGenerator::Generate());
			output.AddCompilerOutput(::DLDL::grammar::CompilerGenerator::Generate());

			return output;
		}
		~CompilerGenerator() override = default;
	};
}

#endif // DLDL_DEFINITION_COMPILERGENERATOR_H
