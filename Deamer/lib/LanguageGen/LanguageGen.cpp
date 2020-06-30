#include "Deamer/LanguageGen/LanguageGen.h"
#include <iostream>
#include <fstream>
#include <sstream>

LanguageGen::LanguageGen(LexerType_t lexerType, ParserType_t parserType, LanguageDefinition* languageDefinition)
{
    LanguageGen::languageDefinition = languageDefinition;
    LanguageGen::lexerGen = new LexerGen(lexerType, languageDefinition);
    LanguageGen::parserGen = new ParserGen(parserType, languageDefinition);
}

void LanguageGen::DirTarget(std::string TargetDir)
{
    LanguageGen::Directory = TargetDir;
    LanguageGen::lexerGen->DirTarget(TargetDir);
    LanguageGen::parserGen->DirTarget(TargetDir);
}

void LanguageGen::FileTarget(std::string fileTarget)
{
}

void LanguageGen::SetLexer(LexerType_t lexerType)
{
    LanguageGen::lexerGen->SetTarget(lexerType);
}

void LanguageGen::SetParser(ParserType_t parserType)
{
    LanguageGen::parserGen->SetTarget(parserType);
}

void LanguageGen::GenerateLexer()
{
    LanguageGen::lexerGen->Build();
}

void LanguageGen::GenerateParser()
{
    LanguageGen::parserGen->Build();
}

bool LanguageGen::Build()
{
    bool buildIsSuccesfull;
    buildIsSuccesfull = LanguageGen::lexerGen->Build();
    if (!buildIsSuccesfull)
    {
        return buildIsSuccesfull;
    }

    buildIsSuccesfull = LanguageGen::parserGen->Build();
    if (!buildIsSuccesfull)
    {
        return buildIsSuccesfull;
    }

    buildIsSuccesfull = LanguageGen::CreateDefaultLexerAPI();
    if (!buildIsSuccesfull)
    {
        return buildIsSuccesfull;
    }
    
    buildIsSuccesfull = LanguageGen::CreateDefaultParserAPI();
    if (!buildIsSuccesfull)
    {
        return buildIsSuccesfull;
    }

    buildIsSuccesfull = LanguageGen::CreateDefaultCompilerAPIHeader();
    if (!buildIsSuccesfull)
    {
        return buildIsSuccesfull;
    }
    
    buildIsSuccesfull = LanguageGen::CreateDefaultCompilerAPISource();
    return buildIsSuccesfull;
}

bool LanguageGen::CreateDefaultLexerAPI()
{
    std::ostringstream LexerAPIFile;
    LexerAPIFile << "#ifndef LEXER_" << LanguageGen::languageDefinition->GetLanguageName() << "_LEXERAPIFILE_H\n"
                  << "#define LEXER_" << LanguageGen::languageDefinition->GetLanguageName() << "_LEXERAPIFILE_H\n"
                  << "\n"
                  << "#include <Deamer/DefaultAPI/DeamerLexerAPI.h>\n"
                  << "#include <Deamer/AstGen/AstInformation.h>\n"
                  << "#include <Deamer/AstGen/AstNode.h>\n"
                  << "#include <Deamer/AstGen/AstTree.h>\n"
                  << "\n"
                  << "class " << LanguageGen::languageDefinition->GetLanguageName() << "Lexer : public DeamerLexerAPI\n"
                  << "{\n"
                  << "    private:\n"
                  << "    protected:\n"
                  << "    public:\n"
                  << "        AstInformation* LexText(std::string inputText) override;\n"
                  << "        AstInformation* LexFile(FILE* inputFile) override;\n"
                  << "        AstInformation* LexFile(std::string fileLocation) override;\n"
                  << "};\n"
                  << "\n"
                  << "#endif //LEXER_" << LanguageGen::languageDefinition->GetLanguageName() << "_LEXERAPIFILE_H\n";
    std::ostringstream oss0;
    oss0 << LanguageGen::Directory << "Lexer/" << "" << LanguageGen::languageDefinition->GetLanguageName() << "Lexer.h";
    std::ofstream newLexerAPIFile;

    newLexerAPIFile.open(oss0.str(), std::ios_base::app);

    newLexerAPIFile << LexerAPIFile.str() << '\n';
    
    newLexerAPIFile.close();

    return true;
}

bool LanguageGen::CreateDefaultParserAPI()
{
    std::ostringstream ParserAPIFile;
    ParserAPIFile << "#ifndef PARSER_" << LanguageGen::languageDefinition->GetLanguageName() << "_PARSERAPIFILE_H\n"
                  << "#define PARSER_" << LanguageGen::languageDefinition->GetLanguageName() << "_PARSERAPIFILE_H\n"
                  << "\n"
                  << "#include <Deamer/DefaultAPI/DeamerParserAPI.h>\n"
                  << "#include <Deamer/AstGen/AstNode.h>\n"
                  << "#include <Deamer/AstGen/AstTree.h>\n"
                  << "\n"
                  << "class " << LanguageGen::languageDefinition->GetLanguageName() << "Parser : public DeamerParserAPI\n"
                  << "{\n"
                  << "    private:\n"
                  << "    protected:\n"
                  << "    public:\n"
                  << "        AstNode* ParseText(std::string inputText) override;\n"
                  << "        AstNode* ParseFile(FILE* inputFile) override;\n"
                  << "        AstNode* ParseFile(std::string fileLocation) override;\n"
                  << "};\n"
                  << "\n"
                  << "#endif //PARSER_" << LanguageGen::languageDefinition->GetLanguageName() << "_PARSERAPIFILE_H\n";
    std::ostringstream oss0;
    oss0 << LanguageGen::Directory << "Parser/" << "" << LanguageGen::languageDefinition->GetLanguageName() << "Parser.h";
    std::ofstream newParserAPIFile;

    newParserAPIFile.open(oss0.str(), std::ios_base::app);

    newParserAPIFile << ParserAPIFile.str() << '\n';
    
    newParserAPIFile.close();

    return true;
}

bool LanguageGen::CreateDefaultCompilerAPIHeader()
{
    std::ostringstream CompilerAPIHeaderFile;
    CompilerAPIHeaderFile << "#ifndef " << LanguageGen::languageDefinition->GetLanguageName() << "_COMPILERAPIFILE_H\n"
                  << "#define " << LanguageGen::languageDefinition->GetLanguageName() << "_COMPILERAPIFILE_H\n"
                  << "\n"
                  << "#include <Deamer/DefaultAPI/DeamerCompilerAPI.h>\n"
                  << "#include <Deamer/CompilerGen/CompiledObject.h>\n"
                  << "#include <Deamer/AstGen/AstNode.h>\n"
                  << "#include <Deamer/AstGen/AstTree.h>\n"
                  << "\n"
                  << "class " << LanguageGen::languageDefinition->GetLanguageName() << "Parser : public DeamerCompilerAPI\n"
                  << "{\n"
                  << "    private:\n"
                  << "    protected:\n"
                  << "    public:\n"
                  << "        const bool SupportsCompilation = true; // If this can compile data. Set this to false if it cant\n"
                  << "        const bool SupportsDebugging = false; // Set this to true if it supports Debugging note that it needs to inherit the specified interface\n"
                  << "\n"
                  << "        const std::string Language = \"" << LanguageGen::languageDefinition->GetLanguageName() << "\";\n"
                  << "\n"
                  << "        CompiledObject* CompileText(std::string inputText) override;\n"
                  << "        CompiledObject* CompileFile(FILE* inputFile) override;\n"
                  << "        CompiledObject* CompileFile(std::string fileLocation) override;\n"
                  << "};\n"
                  << "\n"
                  << "#endif //" << LanguageGen::languageDefinition->GetLanguageName() << "_COMPILERAPIFILE_H\n";
    std::ostringstream oss0;
    oss0 << LanguageGen::Directory << LanguageGen::languageDefinition->GetLanguageName() << "Compiler.h";
    std::ofstream newCompilerAPIHeaderFile;

    newCompilerAPIHeaderFile.open(oss0.str(), std::ios_base::app);

    newCompilerAPIHeaderFile << CompilerAPIHeaderFile.str() << '\n';
    
    newCompilerAPIHeaderFile.close();

    return true;
}

bool LanguageGen::CreateDefaultCompilerAPISource()
{
    std::ostringstream CompilerAPISourceFile;
    CompilerAPISourceFile << "#ifndef " << LanguageGen::languageDefinition->GetLanguageName() << "_COMPILERAPIFILE_H\n"
                  << "#define " << LanguageGen::languageDefinition->GetLanguageName() << "_COMPILERAPIFILE_H\n"
                  << "\n"
                  << "#include <Deamer/DefaultAPI/DeamerCompilerAPI.h>\n"
                  << "#include <Deamer/CompilerGen/CompiledObject.h>\n"
                  << "#include <Deamer/AstGen/AstNode.h>\n"
                  << "#include <Deamer/AstGen/AstTree.h>\n"
                  << "\n"
                  << "class " << LanguageGen::languageDefinition->GetLanguageName() << "Parser : public DeamerCompilerAPI\n"
                  << "{\n"
                  << "    private:\n"
                  << "    protected:\n"
                  << "    public:\n"
                  << "        const bool SupportsCompilation = true; // If this can compile data. Set this to false if it cant\n"
                  << "        const bool SupportsDebugging = false; // Set this to true if it supports Debugging note that it needs to inherit the specified interface\n"
                  << "\n"
                  << "        const std::string Language = \"" << LanguageGen::languageDefinition->GetLanguageName() << "\";\n"
                  << "\n"
                  << "        CompiledObject* CompileText(std::string inputText) override;\n"
                  << "        CompiledObject* CompileFile(FILE* inputFile) override;\n"
                  << "        CompiledObject* CompileFile(std::string fileLocation) override;\n"
                  << "};\n"
                  << "\n"
                  << "#endif //" << LanguageGen::languageDefinition->GetLanguageName() << "_COMPILERAPIFILE_H\n";
    std::ostringstream oss0;
    oss0 << LanguageGen::Directory << LanguageGen::languageDefinition->GetLanguageName() << "Compiler.cpp";
    std::ofstream newCompilerAPISourceFile;

    newCompilerAPISourceFile.open(oss0.str(), std::ios_base::app);

    newCompilerAPISourceFile << CompilerAPISourceFile.str() << '\n';
    
    newCompilerAPISourceFile.close();

    return true;
}

bool LanguageGen::Write()
{
    LanguageGen::lexerGen->Write();
    LanguageGen::parserGen->Write();

    return true;
}

bool LanguageGen::Compile()
{
    /*Currently only supports Flex and Bison (c++ variant)*/
    std::ostringstream ossLexer;
    ossLexer << "flex -P" << LanguageGen::languageDefinition->GetLanguageName() << " " << LanguageGen::lexerGen->GetDirectoryLocation() << LanguageGen::languageDefinition->GetLanguageName() << "lexer.l";
    std::cout << ossLexer.str() << "\n";
    std::system(ossLexer.str().c_str());

    std::ostringstream ossLexerReplace;
    ossLexerReplace << "mv lex." << LanguageGen::languageDefinition->GetLanguageName() << ".c " << LanguageGen::lexerGen->GetDirectoryLocation() << "lex." << LanguageGen::languageDefinition->GetLanguageName() << ".c";
    std::cout << ossLexerReplace.str() << "\n";
    std::system(ossLexerReplace.str().c_str());

    std::ostringstream ossParser;
    ossParser << "bison -d -p" << LanguageGen::languageDefinition->GetLanguageName() << " " << LanguageGen::parserGen->GetDirectoryLocation() << LanguageGen::languageDefinition->GetLanguageName() << "parser.y";
    std::cout << ossParser.str() << "\n";
    std::system(ossParser.str().c_str());

    /*
    std::ostringstream ossCompileLexer;
    ossCompileLexer << "g++ " << "-I " << LanguageGen::Directory << "Deamer/include" << " -I " << LanguageGen::Directory << "AstNodes/"  << " -c " << LanguageGen::lexerGen->GetDirectoryLocation() << "lex.yy.c" << " -lfl -o" << LanguageGen::lexerGen->GetDirectoryLocation() << "lex.yy.o";
    std::system(ossCompileLexer.str().c_str());
    //std::cout << ossCompileLexer.str();

    std::ostringstream ossCompileParser;
    ossCompileParser << "g++ " << "-I " << LanguageGen::Directory << "Deamer/include" << " -I " << LanguageGen::Directory << "AstNodes/" << " -c " << LanguageGen::parserGen->GetDirectoryLocation() << "parser.tab.c -lfl -o" << LanguageGen::parserGen->GetDirectoryLocation() << "parser.tab.o";
    std::system(ossCompileParser.str().c_str());
    //std::cout << ossCompileParser.str();
    */
   
    return true;
}

bool LanguageGen::Finish()
{
    if(!LanguageGen::Build())
    {
        return false;
    }

    if(!LanguageGen::Write())
    {
        return false;
    }

    if(!LanguageGen::Compile())
    {
        return false;
    }

    return true;
}