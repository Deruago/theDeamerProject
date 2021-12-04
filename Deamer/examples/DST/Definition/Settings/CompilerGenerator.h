#ifndef DST_SETTING_DEFINITION_COMPILERGENERATOR_H
#define DST_SETTING_DEFINITION_COMPILERGENERATOR_H

#include "Deamer/Ast/Generation/CPP/CPP.h"
#include "Deamer/Compiler/Generator/Compiler.h"
#include "Deamer/Lexer/Generator/Flex/Flex.h"
#include "Deamer/Parser/Generator/Bison/Bison.h"
#include "Deamer/Tool/Type/DLDLConverter/DLDLConverter.h"
#include "Deamer/Tool/Type/SyntaxHighlighter/UDL/UDL.h"
#include "Language.h"

namespace DST::setting
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
			deamer::tool::type::syntaxhighlighter::udl::UDL udl(GetLanguageDefinition());
			deamer::tool::type::dldlconverter::DLDLConverter dldlConverter(GetLanguageDefinition());

			output.AddLanguageToolOutput(flex.Generate());
			output.AddLanguageToolOutput(bison.Generate());
			output.AddLanguageToolOutput(ast.Generate());
			output.AddLanguageToolOutput(udl.Generate());
			output.AddLanguageToolOutput(dldlConverter.Generate());

			return output;
		}
		~CompilerGenerator() override = default;
	};
}

#endif // DST_SETTING_DEFINITION_COMPILERGENERATOR_H
