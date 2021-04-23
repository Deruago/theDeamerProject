#ifndef DST_DEFINITION_COMPILERGENERATOR_H
#define DST_DEFINITION_COMPILERGENERATOR_H

#include "Deamer/Compiler/Generator/Compiler.h"
#include "Language.h"
#include "Main/CompilerGenerator.h"
#include "Settings/CompilerGenerator.h"

namespace DST
{
	class CompilerGenerator : public ::deamer::compiler::generator::Compiler<::DST::Language>,
							  public ::DST::setting::CompilerGenerator,
							  public ::DST::main::CompilerGenerator
	{
	public:
		CompilerGenerator()
			: deamer::compiler::generator::Compiler<::DST::Language>(),
			  ::DST::setting::CompilerGenerator(),
			  ::DST::main::CompilerGenerator()
		{
		}

		deamer::file::compiler::Output Generate() override
		{
			deamer::file::compiler::Output output(
				deamer::compiler::generator::Compiler<::DST::Language>::GetLanguageDefinition());

			output.AddCompilerOutput(::DST::setting::CompilerGenerator::Generate());
			output.AddCompilerOutput(::DST::main::CompilerGenerator::Generate());

			return output;
		}
		~CompilerGenerator() override = default;
	};
}

#endif // DST_DEFINITION_COMPILERGENERATOR_H
