#include <sstream>
#include "Deamer/LexerGen/FlexBuilder.h"

FlexBuilder::FlexBuilder()
{
    FlexBuilder::WriteToFile = false;
}

void FlexBuilder::AddNode(Node* node)
{
    std::ostringstream oss;
    oss << node->TokenName << "   " << "(" << node->Regex << ")\n";
    FlexBuilder::regexDeclarationPart += oss.str();

    std::ostringstream oss2;
    oss2 << "{" << node->TokenName << "}" << "   " << "{sscanf(yytext, \"%s\", yylval.name); return (" << node->TokenName << ");}\n";
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
    oss << "%{\n" << "#include <stdio.h>\n#include <string.h>\n#include \"./parser.tab.h\"\nvoid showError();\nextern int yylex();\n" << "%}\n" << "\n";
    //oss << "%define IOSTREAM\n\n";
    FlexBuilder::declarationPart = oss.str();
    FlexBuilder::tokenDeclarationPart += "%%\n";
    return true;
}