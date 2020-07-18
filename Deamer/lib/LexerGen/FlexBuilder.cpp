/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -June 2020 Thimo Bohmer
 * -July 2020 Thimo Bohmer
 */

#include "Deamer/LexerGen/FlexBuilder.h"
#include <sstream>
#include <fstream>
#include <ostream>

deamer::FlexBuilder::FlexBuilder()
{
    
}

deamer::FlexBuilder::FlexBuilder(deamer::LanguageDefinition* langDef) : deamer::FlexBuilder::FlexBuilder()
{
    deamer::FlexBuilder::langDef = langDef;
}

std::string deamer::FlexBuilder::NewNodeFunctionalData(Node* node)
{
    std::ostringstream oss;
    oss << "{" << deamer::FlexBuilder::langDef->GetLanguageName() << "lval.DeamerNode = (deamer::AstInformation*) malloc(sizeof(deamer::AstInformation)); sscanf(yytext, \"%s\", " << deamer::FlexBuilder::langDef->GetLanguageName() << "lval.DeamerNode->ValueName); " << deamer::FlexBuilder::langDef->GetLanguageName() << "lval.DeamerNode->LineNumber = " << deamer::FlexBuilder::langDef->GetLanguageName() << "lineno; return (" << node->TokenName << ");}\n";
    return oss.str();
}

void deamer::FlexBuilder::AddNode(Node* node)
{
    std::ostringstream oss;
    oss << node->TokenName << "   " << "(" << node->Regex << ")\n";
    deamer::FlexBuilder::regexDeclarationPart += oss.str();

    std::ostringstream oss2;
    oss2 << "{" << node->TokenName << "}" << "   " << deamer::FlexBuilder::NewNodeFunctionalData(node);
    deamer::FlexBuilder::tokenDeclarationPart += oss2.str();
}

void deamer::FlexBuilder::AddIgnoreNode(Node* node)
{
    std::ostringstream oss;
    oss << node->TokenName << "   " << "(" << node->Regex << ")\n";
    deamer::FlexBuilder::regexDeclarationPart += oss.str();
    
    std::ostringstream oss2;
    oss2 << "{" << node->TokenName << "}\n";
    deamer::FlexBuilder::tokenDeclarationPart += oss2.str();
}

bool deamer::FlexBuilder::FinishBuild()
{
    deamer::FlexBuilder::tokenDeclarationPart += "\n%%\n";

    std::ostringstream oss;
    oss << deamer::FlexBuilder::declarationPart << deamer::FlexBuilder::regexDeclarationPart << deamer::FlexBuilder::tokenDeclarationPart << deamer::FlexBuilder::functionPart;
    deamer::FlexBuilder::Output = oss.str();

    return true;
}

bool deamer::FlexBuilder::StartBuild()
{
    std::ostringstream oss;
    oss << "%option yylineno\n"
        << "%option noyywrap\n\n"
        << "%{\n"
        << "#include <AstNodes.h>\n"
        << "#include <Deamer/AstGen/AstInformation.h>\n"
        << "#include <Deamer/AstGen/AstNode.h>\n"
        << "#include <Deamer/AstGen/AstTree.h>\n"
        << "#include <stdio.h>\n"
        << "#include <string.h>\n"
        << "#include \"../Parser/" << deamer::FlexBuilder::langDef->GetLanguageName() << "parser.tab.h\"\n"
        << "void showError();\n"
        << "extern int " << deamer::FlexBuilder::langDef->GetLanguageName() << "lex();\n"
        << "%}\n\n";
    deamer::FlexBuilder::declarationPart = oss.str();
    deamer::FlexBuilder::tokenDeclarationPart += "%%\n";
    return true;
}
