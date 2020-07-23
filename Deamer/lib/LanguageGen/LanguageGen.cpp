/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -June 2020 Thimo B�hmer
 * -July 2020 Thimo B�hmer
 */

#include "Deamer/LanguageGen/LanguageGen.h"
#include <fstream>
#include <sstream>

deamer::LanguageGen::LanguageGen(LexerType_t lexerType, ParserType_t parserType, LanguageDefinition* languageDefinition)
{
    LanguageGen::languageDefinition = languageDefinition;
    lexerGen = new LexerGen(lexerType, languageDefinition);
    parserGen = new ParserGen(parserType, languageDefinition);
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

bool deamer::LanguageGen::Build()
{
    bool buildIsSuccesfull;
    buildIsSuccesfull = lexerGen->Build();
    if (!buildIsSuccesfull)
    {
        return buildIsSuccesfull;
    }

    buildIsSuccesfull = parserGen->Build();
    if (!buildIsSuccesfull)
    {
        return buildIsSuccesfull;
    }

    buildIsSuccesfull = CreateDefaultLexerAPI();
    if (!buildIsSuccesfull)
    {
        return buildIsSuccesfull;
    }
    
    buildIsSuccesfull = CreateDefaultParserAPI();
    if (!buildIsSuccesfull)
    {
        return buildIsSuccesfull;
    }

    buildIsSuccesfull = CreateDefaultCompilerAPIHeader();
    if (!buildIsSuccesfull)
    {
        return buildIsSuccesfull;
    }
    
    buildIsSuccesfull = CreateDefaultCompilerAPISource();
    return buildIsSuccesfull;
}

bool deamer::LanguageGen::CreateDefaultLexerAPI() const
{
    std::ostringstream LexerAPIFile;
    LexerAPIFile << "#ifndef LEXER_" << languageDefinition->GetLanguageName() << "_LEXERAPIFILE_H\n"
                  << "#define LEXER_" << languageDefinition->GetLanguageName() << "_LEXERAPIFILE_H\n"
                  << "\n"
                  << "#include <Deamer/DefaultAPI/DeamerLexerAPI.h>\n"
                  << "#include <Deamer/AstGen/AstInformation.h>\n"
                  << "#include <Deamer/AstGen/AstNode.h>\n"
                  << "#include <Deamer/AstGen/AstTree.h>\n"
                  << "\n"
                  << "namespace " << languageDefinition->GetLanguageName() << "\n"
                  << "{\n"
                  << "    class " << languageDefinition->GetLanguageName() << "Lexer : public deamer::DeamerLexerAPI\n"
                  << "    {\n"
                  << "        private:\n"
                  << "        protected:\n"
                  << "        public:\n"
                  << "            deamer::AstInformation* LexText(std::string inputText) override;\n"
                  << "            deamer::AstInformation* LexFile(FILE* inputFile) override;\n"
                  << "            deamer::AstInformation* LexFile(std::string fileLocation) override;\n"
                  << "    };\n"
                  << "}\n"
                  << "\n"
                  << "#endif //LEXER_" << languageDefinition->GetLanguageName() << "_LEXERAPIFILE_H\n";
    std::ostringstream oss0;
    oss0 << Directory << "Lexer/" << "" << languageDefinition->GetLanguageName() << "Lexer.h";
    std::ofstream newLexerAPIFile;

    newLexerAPIFile.open(oss0.str(), std::ios_base::app);

    newLexerAPIFile << LexerAPIFile.str() << '\n';
    
    newLexerAPIFile.close();

    return true;
}

bool deamer::LanguageGen::CreateDefaultParserAPI() const
{
    std::ostringstream ParserAPIFile;
    ParserAPIFile << "#ifndef PARSER_" << languageDefinition->GetLanguageName() << "_PARSERAPIFILE_H\n"
                  << "#define PARSER_" << languageDefinition->GetLanguageName() << "_PARSERAPIFILE_H\n"
                  << "\n"
                  << "#include <Deamer/DefaultAPI/DeamerParserAPI.h>\n"
                  << "#include <Deamer/AstGen/AstNode.h>\n"
                  << "#include <Deamer/AstGen/AstTree.h>\n"
                  << "\n"
                  << "namespace " << languageDefinition->GetLanguageName() << "\n"
                  << "{\n"
                  << "    class " << languageDefinition->GetLanguageName() << "Parser : public deamer::DeamerParserAPI\n"
                  << "    {\n"
                  << "        private:\n"
                  << "        protected:\n"
                  << "        public:\n"
                  << "            " << languageDefinition->GetLanguageName() << "Parser();\n"
                  << "            ~" << languageDefinition->GetLanguageName() << "Parser();\n"
                  << "\n"
                  << "            deamer::AstNode* ParseText(std::string inputText) override;\n"
                  << "            deamer::AstNode* ParseFile(FILE* inputFile) override;\n"
                  << "            deamer::AstNode* ParseFile(std::string fileLocation) override;\n"
                  << "    };\n"
                  << "}\n"
                  << "\n"
                  << "#endif //PARSER_" << languageDefinition->GetLanguageName() << "_PARSERAPIFILE_H\n";
    std::ostringstream oss0;
    oss0 << Directory << "Parser/" << "" << languageDefinition->GetLanguageName() << "Parser.h";
    std::ofstream newParserAPIFile;

    newParserAPIFile.open(oss0.str(), std::ios_base::app);

    newParserAPIFile << ParserAPIFile.str() << '\n';
    
    newParserAPIFile.close();

    return true;
}

bool deamer::LanguageGen::CreateDefaultCompilerAPIHeader() const
{
    std::ostringstream CompilerAPIHeaderFile;
    CompilerAPIHeaderFile << "#ifndef " << languageDefinition->GetLanguageName() << "_COMPILERAPIFILE_H\n"
                  << "#define " << languageDefinition->GetLanguageName() << "_COMPILERAPIFILE_H\n"
                  << "\n"
                  << "#include <Deamer/DefaultAPI/DeamerCompilerAPI.h>\n"
                  << "#include <Deamer/CompilerGen/CompiledObject.h>\n"
                  << "#include <Deamer/AstGen/AstNode.h>\n"
                  << "#include <Deamer/AstGen/AstTree.h>\n"
                  << "\n"
                  << "namespace " << languageDefinition->GetLanguageName() << "\n"
                  << "{\n"
                  << "    class " << languageDefinition->GetLanguageName() << "Compiler : public deamer::DeamerCompilerAPI\n"
                  << "    {\n"
                  << "        private:\n"
                  << "        protected:\n"
                  << "        public:\n"
                  << "            const bool SupportsCompilation = true; // If this can compile data. Set this to false if it cant\n"
                  << "            const bool SupportsDebugging = false; // Set this to true if it supports Debugging note that it needs to inherit the specified interface\n"
                  << "\n"
                  << "            const std::string Language = \"" << languageDefinition->GetLanguageName() << "\";\n"
                  << "\n"
                  << "            " << languageDefinition->GetLanguageName() << "Compiler();\n"
                  << "            ~" << languageDefinition->GetLanguageName() << "Compiler();\n"
                  << "\n"
                  << "            deamer::CompiledObject* CompileText(std::string inputText) override;\n"
                  << "            deamer::CompiledObject* CompileFile(FILE* inputFile) override;\n"
                  << "            deamer::CompiledObject* CompileFile(std::string fileLocation) override;\n"
                  << "    };\n"
                  << "}\n"
                  << "\n"
                  << "#endif //" << languageDefinition->GetLanguageName() << "_COMPILERAPIFILE_H\n";
    std::ostringstream oss0;
    oss0 << Directory << languageDefinition->GetLanguageName() << "Compiler.h";
    std::ofstream newCompilerAPIHeaderFile;

    newCompilerAPIHeaderFile.open(oss0.str(), std::ios_base::app);

    newCompilerAPIHeaderFile << CompilerAPIHeaderFile.str() << '\n';
    
    newCompilerAPIHeaderFile.close();

    return true;
}

bool deamer::LanguageGen::CreateDefaultCompilerAPISource() const
{
    std::ostringstream CompilerAPISourceFile;
    CompilerAPISourceFile 
                  << "#include <" << languageDefinition->GetLanguageName() << "Compiler.h>\n"
                  << "#include <" << languageDefinition->GetLanguageName() << "Parser.h>\n"
                  << "\n"
                  << languageDefinition->GetLanguageName() << "::" << languageDefinition->GetLanguageName() << "Compiler::" << languageDefinition->GetLanguageName() << "Compiler()\n"
                  << "{\n"
                  << "\n"
                  << "}\n\n"
                  << languageDefinition->GetLanguageName() << "::" << languageDefinition->GetLanguageName() << "Compiler::~" << languageDefinition->GetLanguageName() << "Compiler()\n"
                  << "{\n"
                  << "\n"
                  << "}\n\n"
                  << "deamer::CompiledObject* " << languageDefinition->GetLanguageName() << "::" << languageDefinition->GetLanguageName() << "Compiler::CompileText(std::string inputText)\n"
                  << "{\n"
                  << "    return nullptr;\n"
                  << "}\n\n"
                  << "deamer::CompiledObject* " << languageDefinition->GetLanguageName() << "::" << languageDefinition->GetLanguageName() << "Compiler::CompileFile(FILE* inputFile)\n"
                  << "{\n"
                  << "    return nullptr;\n"
                  << "}\n\n"
                  << "deamer::CompiledObject* " << languageDefinition->GetLanguageName() << "::" << languageDefinition->GetLanguageName() << "Compiler::CompileFile(std::string fileLocation)\n"
                  << "{\n"
                  << "    return nullptr;\n"
                  << "}\n\n";
    std::ostringstream oss0;
    oss0 << Directory << languageDefinition->GetLanguageName() << "Compiler.cpp";
    std::ofstream newCompilerAPISourceFile;

    newCompilerAPISourceFile.open(oss0.str(), std::ios_base::app);

    newCompilerAPISourceFile << CompilerAPISourceFile.str() << '\n';
    
    newCompilerAPISourceFile.close();

    return true;
}

bool deamer::LanguageGen::Write()
{
    lexerGen->Write();
    parserGen->Write();

    return true;
}

bool deamer::LanguageGen::Compile() const
{
    /*Currently only supports Flex and Bison (c++ variant)*/
    std::ostringstream ossLexer;
    ossLexer << "flex -P" << languageDefinition->GetLanguageName() << " " << lexerGen->GetDirectoryLocation() << languageDefinition->GetLanguageName() << "lexer.l";
    std::cout << ossLexer.str() << "\n";
    std::system(ossLexer.str().c_str());

    std::ostringstream ossLexerReplace;
    ossLexerReplace << "mv lex." << languageDefinition->GetLanguageName() << ".c " << lexerGen->GetDirectoryLocation() << "lex." << languageDefinition->GetLanguageName() << ".c";
    std::cout << ossLexerReplace.str() << "\n";
    std::system(ossLexerReplace.str().c_str());

    std::ostringstream ossLexerReplace2;
    ossLexerReplace2 << "mv ./" << lexerGen->GetDirectoryLocation() << "lex." << languageDefinition->GetLanguageName() << ".c ./" << lexerGen->GetDirectoryLocation() << "lex." << languageDefinition->GetLanguageName() << ".cpp";
    std::cout << ossLexerReplace2.str() << "\n";
    std::system(ossLexerReplace2.str().c_str());

    std::ostringstream ossParser;
    ossParser << "bison -d -p" << languageDefinition->GetLanguageName() << " " << parserGen->GetDirectoryLocation() << languageDefinition->GetLanguageName() << "parser.y";
    std::cout << ossParser.str() << "\n";
    std::system(ossParser.str().c_str());

    std::ostringstream ossParserReplace;
    ossParserReplace << "mv ./" << parserGen->GetDirectoryLocation() << languageDefinition->GetLanguageName() << "parser.tab.c " << parserGen->GetDirectoryLocation() << languageDefinition->GetLanguageName() << "parser.tab.cpp";
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
   
    return true;
}

bool deamer::LanguageGen::Finish()
{
    if(!LanguageGen::Build())
    {
        return false;
    }

    if(!LanguageGen::Write())
    {
        return false;
    }

    if(!Compile())
    {
        return false;
    }

    return true;
}