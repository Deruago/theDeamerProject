#include "Deamer/LexerGen/FlexBuilder.h"
#include <sstream>
#include <fstream>
#include <ostream>

FlexBuilder::FlexBuilder()
{
    
}

std::string FlexBuilder::NewNodeFunctionalData(Node* node)
{
    std::ostringstream oss;
    oss << "{yylval.DeamerNode = (AstInformation*) malloc(sizeof(AstInformation)); sscanf(yytext, \"%s\", yylval.DeamerNode->ValueName); yylval.DeamerNode->LineNumber = yylineno; return (" << node->TokenName << ");}\n";
    return oss.str();
}

void FlexBuilder::AddNode(Node* node)
{
    std::ostringstream oss;
    oss << node->TokenName << "   " << "(" << node->Regex << ")\n";
    FlexBuilder::regexDeclarationPart += oss.str();

    std::ostringstream oss2;
    oss2 << "{" << node->TokenName << "}" << "   " << FlexBuilder::NewNodeFunctionalData(node);
    FlexBuilder::tokenDeclarationPart += oss2.str();
}

bool FlexBuilder::FinishBuild()
{
    FlexBuilder::tokenDeclarationPart += "\n%%\n";

    std::ostringstream oss;
    oss << FlexBuilder::declarationPart << FlexBuilder::regexDeclarationPart << FlexBuilder::tokenDeclarationPart << FlexBuilder::functionPart;
    FlexBuilder::Output = oss.str();

    return true;
}

bool FlexBuilder::StartBuild()
{
    std::ostringstream oss;
    oss << "%option yylineno\n\n"
        << "%{\n"
        << "#include <AstNodes.h>\n"
        << "#include <Deamer/AstGen/AstInformation.h>\n"
        << "#include <Deamer/AstGen/AstNode.h>\n"
        << "#include <Deamer/AstGen/AstTree.h>\n"
        << "#include <stdio.h>\n"
        << "#include <string.h>\n"
        << "#include \"../Parser/parser.tab.h\"\n"
        << "void showError();\n"
        << "extern int yylex();\n"
        << "%}\n\n";
    FlexBuilder::declarationPart = oss.str();
    FlexBuilder::tokenDeclarationPart += "%%\n";
    return true;
}