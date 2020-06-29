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
    return buildIsSuccesfull;
}

bool LanguageGen::CreateDefaultLexerAPI()
{
    std::ostringstream LexerAPIFile;
    LexerAPIFile << "#ifndef LEXER_LEXERAPIFILE_H\n"
                  << "#define LEXER_LEXERAPIFILE_H\n"
                  << "\n"
                  << "#include <Deamer/DefaultAPI/DeamerLexerAPI.h>\n"
                  << "#include <Deamer/AstGen/AstInformation.h>\n"
                  << "#include <Deamer/AstGen/AstNode.h>\n"
                  << "#include <Deamer/AstGen/AstTree.h>\n"
                  << "\n"
                  << "class DeamerLexer : public DeamerLexerAPI\n"
                  << "{\n"
                  << "    private:\n"
                  << "    protected:\n"
                  << "    public:\n"
                  << "        AstInformation* LexText(std::string inputText) override;\n"
                  << "        AstInformation* LexFile(FILE* inputFile) override;\n"
                  << "        AstInformation* LexFile(std::string fileLocation) override;\n"
                  << "};\n"
                  << "\n"
                  << "#endif //LEXER_LEXERAPIFILE_H\n";
    std::ostringstream oss0;
    oss0 << LanguageGen::Directory << "Lexer/" << "DeamerLexer.h";
    std::ofstream newLexerAPIFile;

    newLexerAPIFile.open(oss0.str(), std::ios_base::app);

    newLexerAPIFile << LexerAPIFile.str() << '\n';
    
    newLexerAPIFile.close();

    return true;
}

bool LanguageGen::CreateDefaultParserAPI()
{
    std::ostringstream ParserAPIFile;
    ParserAPIFile << "#ifndef PARSER_PARSERAPIFILE_H\n"
                  << "#define PARSER_PARSERAPIFILE_H\n"
                  << "\n"
                  << "#include <Deamer/DefaultAPI/DeamerParserAPI.h>\n"
                  << "#include <Deamer/AstGen/AstNode.h>\n"
                  << "#include <Deamer/AstGen/AstTree.h>\n"
                  << "\n"
                  << "class DeamerParser : public DeamerParserAPI\n"
                  << "{\n"
                  << "    private:\n"
                  << "    protected:\n"
                  << "    public:\n"
                  << "        AstNode* ParseText(std::string inputText) override;\n"
                  << "        AstNode* ParseFile(FILE* inputFile) override;\n"
                  << "        AstNode* ParseFile(std::string fileLocation) override;\n"
                  << "};\n"
                  << "\n"
                  << "#endif //PARSER_PARSERAPIFILE_H\n";
    std::ostringstream oss0;
    oss0 << LanguageGen::Directory << "Parser/" << "DeamerParser.h";
    std::ofstream newParserAPIFile;

    newParserAPIFile.open(oss0.str(), std::ios_base::app);

    newParserAPIFile << ParserAPIFile.str() << '\n';
    
    newParserAPIFile.close();

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
    ossLexer << "flex " << LanguageGen::lexerGen->GetFileLocation();
    std::system(ossLexer.str().c_str());

    std::ostringstream ossLexerReplace;
    ossLexerReplace << "mv lex.yy.c " << LanguageGen::lexerGen->GetDirectoryLocation() << "lex.yy.c";
    std::system(ossLexerReplace.str().c_str());

    std::ostringstream ossParser;
    ossParser << "bison -d " << LanguageGen::parserGen->GetFileLocation();
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