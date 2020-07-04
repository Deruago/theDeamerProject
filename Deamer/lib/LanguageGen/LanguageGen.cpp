#include "Deamer/LanguageGen/LanguageGen.h"
#include <iostream>
#include <fstream>
#include <sstream>

deamer::LanguageGen::LanguageGen(LexerType_t lexerType, ParserType_t parserType, deamer::LanguageDefinition* languageDefinition)
{
    deamer::LanguageGen::languageDefinition = languageDefinition;
    deamer::LanguageGen::lexerGen = new LexerGen(lexerType, languageDefinition);
    deamer::LanguageGen::parserGen = new ParserGen(parserType, languageDefinition);
}

void deamer::LanguageGen::DirTarget(std::string TargetDir)
{
    deamer::LanguageGen::Directory = TargetDir;
    deamer::LanguageGen::lexerGen->DirTarget(TargetDir);
    deamer::LanguageGen::parserGen->DirTarget(TargetDir);
}

void deamer::LanguageGen::FileTarget(std::string fileTarget)
{
}

void deamer::LanguageGen::SetLexer(LexerType_t lexerType)
{
    deamer::LanguageGen::lexerGen->SetTarget(lexerType);
}

void deamer::LanguageGen::SetParser(ParserType_t parserType)
{
    deamer::LanguageGen::parserGen->SetTarget(parserType);
}

void deamer::LanguageGen::GenerateLexer()
{
    deamer::LanguageGen::lexerGen->Build();
}

void deamer::LanguageGen::GenerateParser()
{
    deamer::LanguageGen::parserGen->Build();
}

bool deamer::LanguageGen::Build()
{
    bool buildIsSuccesfull;
    buildIsSuccesfull = deamer::LanguageGen::lexerGen->Build();
    if (!buildIsSuccesfull)
    {
        return buildIsSuccesfull;
    }

    buildIsSuccesfull = deamer::LanguageGen::parserGen->Build();
    if (!buildIsSuccesfull)
    {
        return buildIsSuccesfull;
    }

    buildIsSuccesfull = deamer::LanguageGen::CreateDefaultLexerAPI();
    if (!buildIsSuccesfull)
    {
        return buildIsSuccesfull;
    }
    
    buildIsSuccesfull = deamer::LanguageGen::CreateDefaultParserAPI();
    if (!buildIsSuccesfull)
    {
        return buildIsSuccesfull;
    }

    buildIsSuccesfull = deamer::LanguageGen::CreateDefaultCompilerAPIHeader();
    if (!buildIsSuccesfull)
    {
        return buildIsSuccesfull;
    }
    
    buildIsSuccesfull = deamer::LanguageGen::CreateDefaultCompilerAPISource();
    return buildIsSuccesfull;
}

bool deamer::LanguageGen::CreateDefaultLexerAPI()
{
    std::ostringstream LexerAPIFile;
    LexerAPIFile << "#ifndef LEXER_" << deamer::LanguageGen::languageDefinition->GetLanguageName() << "_LEXERAPIFILE_H\n"
                  << "#define LEXER_" << deamer::LanguageGen::languageDefinition->GetLanguageName() << "_LEXERAPIFILE_H\n"
                  << "\n"
                  << "#include <Deamer/DefaultAPI/DeamerLexerAPI.h>\n"
                  << "#include <Deamer/AstGen/AstInformation.h>\n"
                  << "#include <Deamer/AstGen/AstNode.h>\n"
                  << "#include <Deamer/AstGen/AstTree.h>\n"
                  << "\n"
                  << "namespace " << deamer::LanguageGen::languageDefinition->GetLanguageName() << "\n"
                  << "{\n"
                  << "    class " << deamer::LanguageGen::languageDefinition->GetLanguageName() << "Lexer : public deamer::DeamerLexerAPI\n"
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
                  << "#endif //LEXER_" << deamer::LanguageGen::languageDefinition->GetLanguageName() << "_LEXERAPIFILE_H\n";
    std::ostringstream oss0;
    oss0 << deamer::LanguageGen::Directory << "Lexer/" << "" << deamer::LanguageGen::languageDefinition->GetLanguageName() << "Lexer.h";
    std::ofstream newLexerAPIFile;

    newLexerAPIFile.open(oss0.str(), std::ios_base::app);

    newLexerAPIFile << LexerAPIFile.str() << '\n';
    
    newLexerAPIFile.close();

    return true;
}

bool deamer::LanguageGen::CreateDefaultParserAPI()
{
    std::ostringstream ParserAPIFile;
    ParserAPIFile << "#ifndef PARSER_" << deamer::LanguageGen::languageDefinition->GetLanguageName() << "_PARSERAPIFILE_H\n"
                  << "#define PARSER_" << deamer::LanguageGen::languageDefinition->GetLanguageName() << "_PARSERAPIFILE_H\n"
                  << "\n"
                  << "#include <Deamer/DefaultAPI/DeamerParserAPI.h>\n"
                  << "#include <Deamer/AstGen/AstNode.h>\n"
                  << "#include <Deamer/AstGen/AstTree.h>\n"
                  << "\n"
                  << "namespace " << deamer::LanguageGen::languageDefinition->GetLanguageName() << "\n"
                  << "{\n"
                  << "    class " << deamer::LanguageGen::languageDefinition->GetLanguageName() << "Parser : public deamer::DeamerParserAPI\n"
                  << "    {\n"
                  << "        private:\n"
                  << "        protected:\n"
                  << "        public:\n"
                  << "            " << deamer::LanguageGen::languageDefinition->GetLanguageName() << "Parser();\n"
                  << "            ~" << deamer::LanguageGen::languageDefinition->GetLanguageName() << "Parser();\n"
                  << "\n"
                  << "            deamer::AstNode* ParseText(std::string inputText) override;\n"
                  << "            deamer::AstNode* ParseFile(FILE* inputFile) override;\n"
                  << "            deamer::AstNode* ParseFile(std::string fileLocation) override;\n"
                  << "    };\n"
                  << "}\n"
                  << "\n"
                  << "#endif //PARSER_" << deamer::LanguageGen::languageDefinition->GetLanguageName() << "_PARSERAPIFILE_H\n";
    std::ostringstream oss0;
    oss0 << deamer::LanguageGen::Directory << "Parser/" << "" << deamer::LanguageGen::languageDefinition->GetLanguageName() << "Parser.h";
    std::ofstream newParserAPIFile;

    newParserAPIFile.open(oss0.str(), std::ios_base::app);

    newParserAPIFile << ParserAPIFile.str() << '\n';
    
    newParserAPIFile.close();

    return true;
}

bool deamer::LanguageGen::CreateDefaultCompilerAPIHeader()
{
    std::ostringstream CompilerAPIHeaderFile;
    CompilerAPIHeaderFile << "#ifndef " << deamer::LanguageGen::languageDefinition->GetLanguageName() << "_COMPILERAPIFILE_H\n"
                  << "#define " << deamer::LanguageGen::languageDefinition->GetLanguageName() << "_COMPILERAPIFILE_H\n"
                  << "\n"
                  << "#include <Deamer/DefaultAPI/DeamerCompilerAPI.h>\n"
                  << "#include <Deamer/CompilerGen/CompiledObject.h>\n"
                  << "#include <Deamer/AstGen/AstNode.h>\n"
                  << "#include <Deamer/AstGen/AstTree.h>\n"
                  << "\n"
                  << "namespace " << deamer::LanguageGen::languageDefinition->GetLanguageName() << "\n"
                  << "{\n"
                  << "    class " << deamer::LanguageGen::languageDefinition->GetLanguageName() << "Compiler : public deamer::DeamerCompilerAPI\n"
                  << "    {\n"
                  << "        private:\n"
                  << "        protected:\n"
                  << "        public:\n"
                  << "            const bool SupportsCompilation = true; // If this can compile data. Set this to false if it cant\n"
                  << "            const bool SupportsDebugging = false; // Set this to true if it supports Debugging note that it needs to inherit the specified interface\n"
                  << "\n"
                  << "            const std::string Language = \"" << deamer::LanguageGen::languageDefinition->GetLanguageName() << "\";\n"
                  << "\n"
                  << "            " << deamer::LanguageGen::languageDefinition->GetLanguageName() << "Compiler();\n"
                  << "            ~" << deamer::LanguageGen::languageDefinition->GetLanguageName() << "Compiler();\n"
                  << "\n"
                  << "            deamer::CompiledObject* CompileText(std::string inputText) override;\n"
                  << "            deamer::CompiledObject* CompileFile(FILE* inputFile) override;\n"
                  << "            deamer::CompiledObject* CompileFile(std::string fileLocation) override;\n"
                  << "    };\n"
                  << "}\n"
                  << "\n"
                  << "#endif //" << deamer::LanguageGen::languageDefinition->GetLanguageName() << "_COMPILERAPIFILE_H\n";
    std::ostringstream oss0;
    oss0 << deamer::LanguageGen::Directory << deamer::LanguageGen::languageDefinition->GetLanguageName() << "Compiler.h";
    std::ofstream newCompilerAPIHeaderFile;

    newCompilerAPIHeaderFile.open(oss0.str(), std::ios_base::app);

    newCompilerAPIHeaderFile << CompilerAPIHeaderFile.str() << '\n';
    
    newCompilerAPIHeaderFile.close();

    return true;
}

bool deamer::LanguageGen::CreateDefaultCompilerAPISource()
{
    std::ostringstream CompilerAPISourceFile;
    CompilerAPISourceFile 
                  << "#include <" << deamer::LanguageGen::languageDefinition->GetLanguageName() << "Compiler.h>\n"
                  << "#include <" << deamer::LanguageGen::languageDefinition->GetLanguageName() << "Parser.h>\n"
                  << "\n"
                  << deamer::LanguageGen::languageDefinition->GetLanguageName() << "::" << deamer::LanguageGen::languageDefinition->GetLanguageName() << "Compiler::" << deamer::LanguageGen::languageDefinition->GetLanguageName() << "Compiler()\n"
                  << "{\n"
                  << "\n"
                  << "}\n\n"
                  << deamer::LanguageGen::languageDefinition->GetLanguageName() << "::" << deamer::LanguageGen::languageDefinition->GetLanguageName() << "Compiler::~" << deamer::LanguageGen::languageDefinition->GetLanguageName() << "Compiler()\n"
                  << "{\n"
                  << "\n"
                  << "}\n\n"
                  << "deamer::CompiledObject* " << deamer::LanguageGen::languageDefinition->GetLanguageName() << "::" << deamer::LanguageGen::languageDefinition->GetLanguageName() << "Compiler::CompileText(std::string inputText)\n"
                  << "{\n"
                  << "\n"
                  << "}\n\n"
                  << "deamer::CompiledObject* " << deamer::LanguageGen::languageDefinition->GetLanguageName() << "::" << deamer::LanguageGen::languageDefinition->GetLanguageName() << "Compiler::CompileFile(FILE* inputFile)\n"
                  << "{\n"
                  << "\n"
                  << "}\n\n"
                  << "deamer::CompiledObject* " << deamer::LanguageGen::languageDefinition->GetLanguageName() << "::" << deamer::LanguageGen::languageDefinition->GetLanguageName() << "Compiler::CompileFile(std::string fileLocation)\n"
                  << "{\n"
                  << "\n"
                  << "}\n\n";
    std::ostringstream oss0;
    oss0 << deamer::LanguageGen::Directory << deamer::LanguageGen::languageDefinition->GetLanguageName() << "Compiler.cpp";
    std::ofstream newCompilerAPISourceFile;

    newCompilerAPISourceFile.open(oss0.str(), std::ios_base::app);

    newCompilerAPISourceFile << CompilerAPISourceFile.str() << '\n';
    
    newCompilerAPISourceFile.close();

    return true;
}

bool deamer::LanguageGen::Write()
{
    deamer::LanguageGen::lexerGen->Write();
    deamer::LanguageGen::parserGen->Write();

    return true;
}

bool deamer::LanguageGen::Compile()
{
    /*Currently only supports Flex and Bison (c++ variant)*/
    std::ostringstream ossLexer;
    ossLexer << "flex -P" << deamer::LanguageGen::languageDefinition->GetLanguageName() << " " << deamer::LanguageGen::lexerGen->GetDirectoryLocation() << deamer::LanguageGen::languageDefinition->GetLanguageName() << "lexer.l";
    std::cout << ossLexer.str() << "\n";
    std::system(ossLexer.str().c_str());

    std::ostringstream ossLexerReplace;
    ossLexerReplace << "mv lex." << deamer::LanguageGen::languageDefinition->GetLanguageName() << ".c " << deamer::LanguageGen::lexerGen->GetDirectoryLocation() << "lex." << deamer::LanguageGen::languageDefinition->GetLanguageName() << ".c";
    std::cout << ossLexerReplace.str() << "\n";
    std::system(ossLexerReplace.str().c_str());

    std::ostringstream ossLexerReplace2;
    ossLexerReplace2 << "mv ./" << deamer::LanguageGen::lexerGen->GetDirectoryLocation() << "lex." << deamer::LanguageGen::languageDefinition->GetLanguageName() << ".c ./" << deamer::LanguageGen::lexerGen->GetDirectoryLocation() << "lex." << deamer::LanguageGen::languageDefinition->GetLanguageName() << ".cpp";
    std::cout << ossLexerReplace2.str() << "\n";
    std::system(ossLexerReplace2.str().c_str());

    std::ostringstream ossParser;
    ossParser << "bison -d -p" << deamer::LanguageGen::languageDefinition->GetLanguageName() << " " << deamer::LanguageGen::parserGen->GetDirectoryLocation() << deamer::LanguageGen::languageDefinition->GetLanguageName() << "parser.y";
    std::cout << ossParser.str() << "\n";
    std::system(ossParser.str().c_str());

    std::ostringstream ossParserReplace;
    ossParserReplace << "mv ./" << deamer::LanguageGen::parserGen->GetDirectoryLocation() << deamer::LanguageGen::languageDefinition->GetLanguageName() << "parser.tab.c " << deamer::LanguageGen::parserGen->GetDirectoryLocation() << deamer::LanguageGen::languageDefinition->GetLanguageName() << "parser.tab.cpp";
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
    if(!deamer::LanguageGen::Build())
    {
        return false;
    }

    if(!deamer::LanguageGen::Write())
    {
        return false;
    }

    if(!deamer::LanguageGen::Compile())
    {
        return false;
    }

    return true;
}