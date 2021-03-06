/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
 /*
  * Part of the DeamerProject.
  * For more information go to: https://github.com/Deruago/theDeamerProject
  */

#include "Deamer/LanguageGen/LanguageGen.h"
#include <fstream>
#include <iostream>
#include <sstream>

deamer::LanguageGen::LanguageGen(LexerType_t lexerType, ParserType_t parserType, const LanguageDefinition& languageDefinition)
	:	languageDefinition(languageDefinition),
		lexerGen(new LexerGen(lexerType, &languageDefinition)),
		parserGen(new ParserGen(parserType, &languageDefinition))
{
}

void deamer::LanguageGen::DirTarget(std::string TargetDir)
{
	Directory = TargetDir;
	lexerGen->DirTarget(TargetDir);
	parserGen->DirTarget(TargetDir);
}

void deamer::LanguageGen::FileTarget(std::string fileTarget)
{
}

void deamer::LanguageGen::SetLexer(LexerType_t lexerType) const
{
	lexerGen->SetTarget(lexerType);
}

void deamer::LanguageGen::SetParser(ParserType_t parserType) const
{
	parserGen->SetTarget(parserType);
}

void deamer::LanguageGen::GenerateLexer() const
{
	lexerGen->Build();
}

void deamer::LanguageGen::GenerateParser() const
{
	parserGen->Build();
}

void deamer::LanguageGen::Build()
{
	lexerGen->Build();
	parserGen->Build();
	CreateDefaultLexerAPI();
	CreateDefaultParserAPI();
	CreateDefaultCompilerAPIHeader();
	CreateDefaultCompilerAPISource();
	CreateDefaultCompilerSource();
}

void deamer::LanguageGen::CreateDefaultLexerAPI() const
{
	const std::string directory = 
		Directory + "Lexer/" + "" + languageDefinition.LanguageName + "Lexer.h";
	
	const std::string LexerAPIFile =
		"#ifndef LEXER_" + languageDefinition.LanguageName + "_LEXERAPIFILE_H\n"
		"#define LEXER_" + languageDefinition.LanguageName + "_LEXERAPIFILE_H\n"
		"\n"
		"#include <Deamer/DefaultAPI/DeamerLexerAPI.h>\n"
		"#include <Deamer/AstGen/AstInformation.h>\n"
		"#include <Deamer/AstGen/AstNode.h>\n"
		"#include <Deamer/AstGen/AstTree.h>\n"
		"\n"
		"namespace " + languageDefinition.LanguageName + "\n"
		"{\n"
		"    class " + languageDefinition.LanguageName + "Lexer : public deamer::DeamerLexerAPI\n"
		"    {\n"
		"        private:\n"
		"        protected:\n"
		"        public:\n"
		"            deamer::AstInformation* LexText(std::string inputText) override;\n"
		"            deamer::AstInformation* LexFile(FILE* inputFile) override;\n"
		"            deamer::AstInformation* LexFile(std::string fileLocation) override;\n"
		"    };\n"
		"}\n"
		"\n"
		"#endif //LEXER_" + languageDefinition.LanguageName + "_LEXERAPIFILE_H\n";
	std::ofstream newLexerAPIFile;
	newLexerAPIFile.open(directory, std::ios_base::app);

	newLexerAPIFile << LexerAPIFile << '\n';

	newLexerAPIFile.close();
}

void deamer::LanguageGen::CreateDefaultParserAPI() const
{
	const std::string directory =
		Directory + "Parser/" + "" + languageDefinition.LanguageName + "Parser.h";
	
	const std::string ParserAPIFile =
		"#ifndef PARSER_" + languageDefinition.LanguageName + "_PARSERAPIFILE_H\n"
		"#define PARSER_" + languageDefinition.LanguageName + "_PARSERAPIFILE_H\n"
		"\n"
		"#include <Deamer/DefaultAPI/DeamerParserAPI.h>\n"
		"#include <Deamer/AstGen/AstNode.h>\n"
		"#include <Deamer/AstGen/AstTree.h>\n"
		"\n"
		"namespace " + languageDefinition.LanguageName + "\n"
		"{\n"
		"    class " + languageDefinition.LanguageName + "Parser : public deamer::DeamerParserAPI\n"
		"    {\n"
		"        private:\n"
		"        protected:\n"
		"        public:\n"
		"            " + languageDefinition.LanguageName + "Parser();\n"
		"            ~" + languageDefinition.LanguageName + "Parser();\n"
		"\n"
		"            deamer::AstNode* ParseText(std::string inputText) override;\n"
		"            deamer::AstNode* ParseFile(FILE* inputFile) override;\n"
		"            deamer::AstNode* ParseFile(std::string fileLocation) override;\n"
		"    };\n"
		"}\n"
		"\n"
		"#endif //PARSER_" + languageDefinition.LanguageName + "_PARSERAPIFILE_H\n";

	std::ofstream newParserAPIFile;
	newParserAPIFile.open(directory, std::ios_base::app);

	newParserAPIFile << ParserAPIFile << '\n';

	newParserAPIFile.close();
}

void deamer::LanguageGen::CreateDefaultCompilerAPIHeader() const
{
	const std::string file_location = Directory + languageDefinition.LanguageName + "Compiler.h";
	if (DoesFileExist(file_location))
		return;

	const std::string CompilerAPIHeaderFile =
		"#ifndef " + languageDefinition.LanguageName + "_COMPILERAPIFILE_H\n"
		"#define " + languageDefinition.LanguageName + "_COMPILERAPIFILE_H\n"
		"\n"
		"#include <Deamer/DefaultAPI/DeamerCompilerAPI.h>\n"
		"#include <" + languageDefinition.LanguageName + "Parser.h>\n"
		"#include <Deamer/CompilerGen/CompiledObject.h>\n"
		"#include <Deamer/AstGen/AstNode.h>\n"
		"#include <Deamer/AstGen/AstTree.h>\n"
		"\n"
		"namespace " + languageDefinition.LanguageName + "\n"
		"{\n"
		"    class " + languageDefinition.LanguageName + "Compiler : public deamer::DeamerCompilerAPI\n"
		"    {\n"
		"        private:\n"
		"        protected:\n"
		"        public:\n"
		"            const bool SupportsCompilation = true; // If this can compile data. Set this to false if it cant\n"
		"            const bool SupportsDebugging = false; // Set this to true if it supports Debugging note that it needs to inherit the specified interface\n"
		"\n"
		"            const std::string Language = \"" + languageDefinition.LanguageName + "\";\n"
		"\n"
		"            " + languageDefinition.LanguageName + "Parser parser = " + languageDefinition.LanguageName + "Parser();\n"
		"            " + languageDefinition.LanguageName + "Compiler();\n"
		"            ~" + languageDefinition.LanguageName + "Compiler();\n"
		"\n"
		"            deamer::CompiledObject* CompileText(std::string inputText) override;\n"
		"            deamer::CompiledObject* CompileFile(FILE* inputFile) override;\n"
		"            deamer::CompiledObject* CompileFile(std::string fileLocation) override;\n"
		"    };\n"
		"}\n"
		"\n"
		"#endif //" + languageDefinition.LanguageName + "_COMPILERAPIFILE_H\n";

	std::ofstream newCompilerAPIHeaderFile;

	newCompilerAPIHeaderFile.open(file_location, std::ios_base::app);

	newCompilerAPIHeaderFile << CompilerAPIHeaderFile << '\n';

	newCompilerAPIHeaderFile.close();
}

void deamer::LanguageGen::CreateDefaultCompilerAPISource() const
{
	const std::string file_location = Directory + languageDefinition.LanguageName + "Compiler.cpp";
	std::cout << file_location << std::endl;
	if (DoesFileExist(file_location))
		return;

	const std::string CompilerAPISourceFile =
		"#include <" + languageDefinition.LanguageName + "Compiler.h>\n"
		"#include <AstVisitor/" + languageDefinition.LanguageName + "_AstPrinter.h>\n"
		""
		"\n"
		+ languageDefinition.LanguageName + "::" + languageDefinition.LanguageName + "Compiler::" + languageDefinition.LanguageName + "Compiler()\n"
		"{\n"
		"\n"
		"}\n\n"
		+ languageDefinition.LanguageName + "::" + languageDefinition.LanguageName + "Compiler::~" + languageDefinition.LanguageName + "Compiler()\n"
		"{\n"
		"\n"
		"}\n\n"
		"deamer::CompiledObject* " + languageDefinition.LanguageName + "::" + languageDefinition.LanguageName + "Compiler::CompileText(std::string inputText)\n"
		"{\n"
		"    deamer::AstNode* ast_node = parser.ParseText(inputText);\n"
		"    " + languageDefinition.LanguageName + "_AstPrinter ast_printer = " + languageDefinition.LanguageName + "_AstPrinter();\n"
		"    if (ast_node != nullptr)\n"
		"    {\n"
		"        ast_printer.Dispatch(*ast_node);\n"
		"    }\n"
		"    return nullptr;\n"
		"}\n\n"
		"deamer::CompiledObject* " + languageDefinition.LanguageName + "::" + languageDefinition.LanguageName + "Compiler::CompileFile(FILE* inputFile)\n"
		"{\n"
		"    deamer::AstNode* ast_node = parser.ParseFile(inputFile);\n"
		"    " + languageDefinition.LanguageName + "_AstPrinter ast_printer = " + languageDefinition.LanguageName + "_AstPrinter();\n"
		"    if (ast_node != nullptr)\n"
		"    {\n"
		"        ast_printer.Dispatch(*ast_node);\n"
		"    }\n"
		"    return nullptr;\n"
		"}\n\n"
		"deamer::CompiledObject* " + languageDefinition.LanguageName + "::" + languageDefinition.LanguageName + "Compiler::CompileFile(std::string fileLocation)\n"
		"{\n"
		"    deamer::AstNode* ast_node = parser.ParseFile(fileLocation);\n"
		"    " + languageDefinition.LanguageName + "_AstPrinter ast_printer = " + languageDefinition.LanguageName + "_AstPrinter();\n"
		"    if (ast_node != nullptr)\n"
		"    {\n"
		"        ast_printer.Dispatch(*ast_node);\n"
		"    }\n"
		"    return nullptr;\n"
		"}\n\n";

	std::ofstream newCompilerAPISourceFile;

	newCompilerAPISourceFile.open(file_location.c_str(), std::ios_base::app);

	newCompilerAPISourceFile << CompilerAPISourceFile << '\n';

	newCompilerAPISourceFile.close();
}

void deamer::LanguageGen::CreateDefaultCompilerSource() const
{
	const std::string file_location = Directory + "Compiler.cpp";
	std::cout << file_location << std::endl;
	if (DoesFileExist(file_location))
		return;

	const std::string CompilerSourceFile =
		"#include <" + languageDefinition.LanguageName + "Compiler.h>\n"\
		"\n"
		"int main(int argc, char** argv)\n"
		"{\n"
		"    " + languageDefinition.LanguageName + "::" + languageDefinition.LanguageName + "Compiler compiler = " + languageDefinition.LanguageName + "::" + languageDefinition.LanguageName + "Compiler();\n"
		"    compiler.CompileFile(argv[1]);\n"
		"}\n";

	std::ofstream newCompilerAPISourceFile;

	newCompilerAPISourceFile.open(file_location.c_str(), std::ios_base::app);

	newCompilerAPISourceFile << CompilerSourceFile << '\n';

	newCompilerAPISourceFile.close();
}

void deamer::LanguageGen::Write()
{
	lexerGen->Write();
	parserGen->Write();
}

void deamer::LanguageGen::Compile() const
{
	/*Currently only supports Flex and Bison (c++ variant)*/
	std::ostringstream ossLexer;
	ossLexer << "flex -P" << languageDefinition.LanguageName << " " << lexerGen->GetDirectoryLocation() << languageDefinition.LanguageName << "lexer.l";
	std::cout << ossLexer.str() << "\n";
	std::system(ossLexer.str().c_str());

	std::ostringstream ossLexerReplace;
	ossLexerReplace << "mv lex." << languageDefinition.LanguageName << ".c " << lexerGen->GetDirectoryLocation() << "lex." << languageDefinition.LanguageName << ".c";
	std::cout << ossLexerReplace.str() << "\n";
	std::system(ossLexerReplace.str().c_str());

	std::ostringstream ossLexerReplace2;
	ossLexerReplace2 << "mv ./" << lexerGen->GetDirectoryLocation() << "lex." << languageDefinition.LanguageName << ".c ./" << lexerGen->GetDirectoryLocation() << "lex." << languageDefinition.LanguageName << ".cpp";
	std::cout << ossLexerReplace2.str() << "\n";
	std::system(ossLexerReplace2.str().c_str());

	std::ostringstream ossParser;
	ossParser << "bison -d -p" << languageDefinition.LanguageName << " " << parserGen->GetDirectoryLocation() << languageDefinition.LanguageName << "parser.y";
	std::cout << ossParser.str() << "\n";
	std::system(ossParser.str().c_str());

	std::ostringstream ossParserReplace;
	ossParserReplace << "mv ./" << parserGen->GetDirectoryLocation() << languageDefinition.LanguageName << "parser.tab.c " << parserGen->GetDirectoryLocation() << languageDefinition.LanguageName << "parser.tab.cpp";
	std::cout << ossParserReplace.str() << "\n";
	std::system(ossParserReplace.str().c_str());

	/*
	std::ostringstream ossCompileLexer;
	ossCompileLexer << "g++ " << "-I " << deamer::LanguageGen::Directory << "Deamer/include" << " -I " << deamer::LanguageGen::Directory << "AstNodes/"  << " -c " << deamer::LanguageGen::lexerGen->GetDirectoryLocation() << "lex.yy.c" << " -lfl -o" << deamer::LanguageGen::lexerGen->GetDirectoryLocation() << "lex.yy.o";
	std::system(ossCompileLexer.str().c_str());
	//std::cout << ossCompileLexer.str();

	std::ostringstream ossCompileParser;
	ossCompileParser << "g++ " << "-I " << deamer::LanguageGen::Directory << "Deamer/include" << " -I " << deamer::LanguageGen::Directory << "AstNodes/" << " -c " << deamer::LanguageGen::parserGen->GetDirectoryLocation() << "parser.tab.c -lfl -o" << deamer::LanguageGen::parserGen->GetDirectoryLocation() << "parser.tab.o";
	std::system(ossCompileParser.str().c_str());
	//std::cout << ossCompileParser.str();
	*/
}

bool deamer::LanguageGen::DoesFileExist(const std::string& file_location) const
{
	std::ifstream open_file(file_location);
	const bool result = open_file.is_open();
	open_file.close();
	return result;
}

void deamer::LanguageGen::Finish()
{
	Build();
	Write();
	Compile();
}