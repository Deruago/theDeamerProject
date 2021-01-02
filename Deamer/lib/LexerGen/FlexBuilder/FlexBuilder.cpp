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
