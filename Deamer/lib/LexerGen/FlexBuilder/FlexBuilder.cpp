/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -June 2020 Thimo Bohmer
 * -July 2020 Thimo Bohmer
 */

#include "Deamer/LexerGen/FlexBuilder/FlexBuilder.h"

deamer::FlexBuilder::FlexBuilder(const LanguageDefinition* langDef) : LexerBuilder(langDef)
{
}

std::string deamer::FlexBuilder::NewNodeFunctionalData(Node* node) const
{
    return "{" + langDef->LanguageName + "lval.DeamerNode = (deamer::AstInformation*) malloc(sizeof(deamer::AstInformation)); sscanf(yytext, \"%s\", " + langDef->LanguageName + "lval.DeamerNode->ValueName); " + langDef->LanguageName + "lval.DeamerNode->LineNumber = " + langDef->LanguageName + "lineno; return (" + node->TokenName + ");}\n";
}

void deamer::FlexBuilder::AddNode(Node* node)
{
    regexDeclarationPart += node->TokenName + "   (" + node->Regex + ")\n";

    tokenDeclarationPart += "{" + node->TokenName + "}" + "   " + NewNodeFunctionalData(node);
}

void deamer::FlexBuilder::AddIgnoreNode(Node* node)
{
    AddNode(node);
}

void deamer::FlexBuilder::AddDeleteNode(Node* node)
{
    regexDeclarationPart += node->TokenName + "   (" + node->Regex + ")\n";
 
    tokenDeclarationPart += "{" + node->TokenName + "}\n";
}

bool deamer::FlexBuilder::FinishBuild()
{
    tokenDeclarationPart += "\n%%\n";

    Output =
        declarationPart +
        regexDeclarationPart +
        tokenDeclarationPart +
        functionPart;

    return true;
}

bool deamer::FlexBuilder::StartBuild()
{
    declarationPart +=
			"%option yylineno\n"
			"%option noyywrap\n\n"
			"%{\n"
			"#include <AstNodes.h>\n"
			"#include <Deamer/AstGen/AstInformation.h>\n"
			"#include <Deamer/AstGen/AstNode.h>\n"
            "#include <Deamer/AstGen/AstTree.h>\n"
            "#include <stdio.h>\n"
            "#include <string.h>\n"
            "#include \"../Parser/" + langDef->LanguageName + "parser.tab.h\"\n"
            "void showError();\n"
            "extern int " + langDef->LanguageName + "lex();\n"
            "%}\n\n";
    tokenDeclarationPart += "%%\n";
    return true;
}
