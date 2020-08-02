/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -June 2020 Thimo Bohmer
 * -July 2020 Thimo Bohmer
 */

#include "Deamer/LexerGen/FlexBuilder/FlexBuilder.h"
#include <sstream>
#include <ostream>

deamer::FlexBuilder::FlexBuilder()
{
    
}

deamer::FlexBuilder::FlexBuilder(LanguageDefinition* langDef) : FlexBuilder()
{
    FlexBuilder::langDef = langDef;
}

std::string deamer::FlexBuilder::NewNodeFunctionalData(Node* node) const
{
    std::ostringstream oss;
    oss << "{" << langDef->LanguageName << "lval.DeamerNode = (deamer::AstInformation*) malloc(sizeof(deamer::AstInformation)); sscanf(yytext, \"%s\", " << langDef->LanguageName << "lval.DeamerNode->ValueName); " << langDef->LanguageName << "lval.DeamerNode->LineNumber = " << langDef->LanguageName << "lineno; return (" << node->TokenName << ");}\n";
    return oss.str();
}

void deamer::FlexBuilder::AddNode(Node* node)
{
    std::ostringstream oss;
    oss << node->TokenName << "   " << "(" << node->Regex << ")\n";
    regexDeclarationPart += oss.str();

    std::ostringstream oss2;
    oss2 << "{" << node->TokenName << "}" << "   " << NewNodeFunctionalData(node);
    tokenDeclarationPart += oss2.str();
}

void deamer::FlexBuilder::AddIgnoreNode(Node* node)
{
    std::ostringstream oss;
    oss << node->TokenName << "   " << "(" << node->Regex << ")\n";
    regexDeclarationPart += oss.str();
    
    std::ostringstream oss2;
    oss2 << "{" << node->TokenName << "}\n";
    tokenDeclarationPart += oss2.str();
}

bool deamer::FlexBuilder::FinishBuild()
{
    tokenDeclarationPart += "\n%%\n";

    std::ostringstream oss;
    oss << declarationPart << regexDeclarationPart << tokenDeclarationPart << functionPart;
    Output = oss.str();

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
        << "#include \"../Parser/" << langDef->LanguageName << "parser.tab.h\"\n"
        << "void showError();\n"
        << "extern int " << langDef->LanguageName << "lex();\n"
        << "%}\n\n";
    declarationPart = oss.str();
    tokenDeclarationPart += "%%\n";
    return true;
}
