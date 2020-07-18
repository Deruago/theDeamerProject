/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -June 2020 Thimo Bohmer
 * -July 2020 Thimo Bohmer
 */

#include "Deamer/ParserGen/BisonBuilder.h"
#include <sstream>
#include <fstream>
#include <ostream>

deamer::BisonBuilder::BisonBuilder()
{

}

deamer::BisonBuilder::BisonBuilder(deamer::LanguageDefinition* langDef) : deamer::BisonBuilder::BisonBuilder()
{
    deamer::BisonBuilder::langDef = langDef;
}

void deamer::BisonBuilder::AddNode(deamer::Node* node)
{
    std::ostringstream oss;
    oss << "%token " << node->TokenName << '\n';
    deamer::BisonBuilder::tokenDeclarationPart += oss.str();

    std::ostringstream oss2;
    oss2 << "%type <DeamerNode> " << node->TokenName << '\n';
    deamer::BisonBuilder::typeDeclarationPart += oss2.str();
}

void deamer::BisonBuilder::AddType(deamer::Type* type)
{
    std::ostringstream oss;
    oss << "%type <ASTNODE> " << type->TokenName << '\n';
    deamer::BisonBuilder::typeDeclarationPart += oss.str();

    std::ostringstream oss2;
    if (!deamer::BisonBuilder::IsFirstType)
    {
        oss2 << ";\n\n";
    }
    else
    {
        deamer::BisonBuilder::firstType = type;
    }
    

    deamer::BisonBuilder::IsFirstType = false;

    oss2 << type->TokenName << ":\n";
    deamer::BisonBuilder::curRuleSizeOfType = type->Rules.size();
    deamer::BisonBuilder::currentRulesBuilt = 0;
    deamer::BisonBuilder::ruleDeclarationPart += oss2.str();
    deamer::BisonBuilder::curType = type;
}

void deamer::BisonBuilder::AddRule(deamer::Rule* rule)
{
    std::ostringstream oss;
    oss << "    "; 
    
    if (deamer::BisonBuilder::currentRulesBuilt >= 1)
    {
        oss << "| ";
    }
    else
    {
        oss << "  ";
    }
    

    deamer::BisonBuilder::WriteRule(rule, &oss);
    deamer::BisonBuilder::WriteRuleModificationPart(rule, &oss);
    
    oss << '\n';
    deamer::BisonBuilder::ruleDeclarationPart += oss.str();

    deamer::BisonBuilder::currentRulesBuilt += 1;
}

/*
void deamer::BisonBuilder::WriteRuleModificationPart(Rule* rule, std::ostringstream* oss)
{
    *oss << "{\n";
    for(int i = 0; i < rule->Tokens.size(); i++)
    {
        if (!rule->Tokens[i]->IsNode)
        {
            continue;
        }

        *oss << "        std::cout << $" << i + 1 << ".ValueName;\n";
    }
    *oss << "    }";
}
*/

void deamer::BisonBuilder::WriteRuleModificationPart(deamer::Rule* rule, std::ostringstream* oss)
{
    *oss << "{\n";
    if (deamer::BisonBuilder::curType == deamer::BisonBuilder::firstType)
    {
        *oss << "      " << deamer::BisonBuilder::langDef->GetLanguageName() << "::" << "AstTree_" << deamer::BisonBuilder::curType->TokenName << "* ASTTREE_" << deamer::BisonBuilder::curType->TokenName << " = new " << deamer::BisonBuilder::langDef->GetLanguageName() << "::" << "AstTree_" << deamer::BisonBuilder::curType->TokenName << "({";
    }
    else
    {
        *oss << "      $$ = new " << deamer::BisonBuilder::langDef->GetLanguageName() << "::" << "AstNode_" << deamer::BisonBuilder::curType->TokenName << "({";
    }

    //This makes sure we dont create random ',' when nothing can be added.
    int j = 0;
    bool createdFirstParam = false;
    while(j < rule->Tokens.size() && !createdFirstParam)
    {
        if (rule->Tokens[j]->CreateAst)
        {
            if (rule->Tokens[j]->IsNode)
            {
                *oss << "new " << deamer::BisonBuilder::langDef->GetLanguageName() << "::" << "AstNode_" << rule->Tokens[j]->TokenName << "($" << j + 1 << ")";
            }
            else
            {
                *oss << "$" << j + 1;
            }
            createdFirstParam = true;
        }
        j++;
    }

    for(int i = j; i < rule->Tokens.size(); i++)
    {
        if (!rule->Tokens[i]->CreateAst)
        {
            continue;
        }

        *oss << ", ";
        if (rule->Tokens[i]->IsNode)
        {
            *oss << "new " << deamer::BisonBuilder::langDef->GetLanguageName() << "::" << "AstNode_" << rule->Tokens[i]->TokenName << "($" << i + 1 << ")";
        }
        else
        {
            *oss << "$" << i + 1;
        }
    }
    *oss << "});\n";
    if (deamer::BisonBuilder::curType == deamer::BisonBuilder::firstType)
    {
        *oss << "      ASTTREE_" << deamer::BisonBuilder::curType->TokenName << "->SetCurrentTree(ASTTREE_" << deamer::BisonBuilder::curType->TokenName << ");\n";
    }
    *oss << "    }";
}

void deamer::BisonBuilder::WriteRule(deamer::Rule* rule, std::ostringstream* oss)
{
    for(int i = 0; i < rule->Tokens.size(); i++)
    {
        *oss << rule->Tokens[i]->TokenName;
        if (i < rule->Tokens.size())
        {
            *oss << ' ';
        }
    }
}

bool deamer::BisonBuilder::FinishBuild()
{
    std::ostringstream extendedFunctionPart;
    extendedFunctionPart << "void " << deamer::BisonBuilder::langDef->GetLanguageName() << "error(char *s)\n" << "{\n" << "    printf(\"Syntax error on line %s\\n\", s);\n" << "}\n\n";
    extendedFunctionPart << "deamer::AstNode* " << deamer::BisonBuilder::langDef->GetLanguageName() << "::" << deamer::BisonBuilder::langDef->GetLanguageName() << "Parser::ParseText(std::string inputText)\n"
                         << "{\n"
                         << "    FILE* tmpFile = fmemopen((void*)inputText.c_str(), inputText.size(), \"r\");\n"
                         << "    if (tmpFile == nullptr)\n"
                         << "    {\n"
                         << "        return nullptr;\n"
                         << "    }\n"
                         << "    " << deamer::BisonBuilder::langDef->GetLanguageName() << "in = tmpFile;\n"
                         << "    " << deamer::BisonBuilder::langDef->GetLanguageName() << "parse();\n"
                         << "    return AstTree_" << deamer::BisonBuilder::firstType->TokenName << "::currentTree;\n"
                         << "}\n\n";
    extendedFunctionPart << "deamer::AstNode* " << deamer::BisonBuilder::langDef->GetLanguageName() << "::" << deamer::BisonBuilder::langDef->GetLanguageName() << "Parser::ParseFile(FILE* inputFile)\n"
                         << "{\n"
                         << "    if (inputFile == nullptr)\n"
                         << "    {\n"
                         << "        return nullptr;\n"
                         << "    }\n"
                         << "    " << deamer::BisonBuilder::langDef->GetLanguageName() << "in = inputFile;\n"
                         << "    " << deamer::BisonBuilder::langDef->GetLanguageName() << "parse();\n"
                         << "    return AstTree_" << deamer::BisonBuilder::firstType->TokenName << "::currentTree;\n"
                         << "}\n\n";
    extendedFunctionPart << "deamer::AstNode* " << deamer::BisonBuilder::langDef->GetLanguageName() << "::" << deamer::BisonBuilder::langDef->GetLanguageName() << "Parser::ParseFile(std::string fileLocation)\n"
                         << "{\n"
                         << "    FILE* inputFile = fopen(fileLocation.c_str(), \"r\");;\n"
                         << "    if (inputFile == nullptr)\n"
                         << "    {\n"
                         << "        return nullptr;\n"
                         << "    }\n"
                         << "    " << deamer::BisonBuilder::langDef->GetLanguageName() << "in = inputFile;\n"
                         << "    " << deamer::BisonBuilder::langDef->GetLanguageName() << "parse();\n"
                         << "    return AstTree_" << deamer::BisonBuilder::firstType->TokenName << "::currentTree;\n"
                         << "}\n\n";
    extendedFunctionPart << deamer::BisonBuilder::langDef->GetLanguageName() << "::" << deamer::BisonBuilder::langDef->GetLanguageName() << "Parser::" << deamer::BisonBuilder::langDef->GetLanguageName() << "Parser()\n"
                         << "{\n"
                         << "}\n\n";
    extendedFunctionPart << deamer::BisonBuilder::langDef->GetLanguageName() << "::" << deamer::BisonBuilder::langDef->GetLanguageName() << "Parser::~" << deamer::BisonBuilder::langDef->GetLanguageName() << "Parser()\n"
                         << "{\n"
                         << "}\n\n";

    std::ostringstream oss;
    oss << deamer::BisonBuilder::includePart << deamer::BisonBuilder::tokenDeclarationPart <<  '\n' << deamer::BisonBuilder::typeDeclarationPart << '\n' << deamer::BisonBuilder::unionDeclarationPart << deamer::BisonBuilder::ruleDeclarationPart << ";\n\n\n%%\n\n\n" << extendedFunctionPart.str();
    deamer::BisonBuilder::Output = oss.str();
    return true;
}

bool deamer::BisonBuilder::StartBuild()
{
    deamer::BisonBuilder::IsFirstType = true;
    std::ostringstream oss;
    oss << "%union{\n"
        << "    deamer::AstInformation* DeamerNode;\n"
        << "    deamer::AstInformation* DeamerType;\n"
        << "    deamer::AstNode* ASTNODE;\n"
        << "}\n\n\n";
    deamer::BisonBuilder::unionDeclarationPart = oss.str();

    std::ostringstream oss2;
    oss2 << "\n%%\n\n\n";
    deamer::BisonBuilder::ruleDeclarationPart = oss2.str();

    std::ostringstream oss3;
    oss3 << "%{\n" 
         << "#include <AstNodes.h>\n"
         << "#include <Deamer/AstGen/AstInformation.h>\n"
         << "#include <Deamer/AstGen/AstNode.h>\n"
         << "#include <Deamer/AstGen/AstTree.h>\n"
         << "#include \"./" << deamer::BisonBuilder::langDef->GetLanguageName() << "Parser.h\"\n"
         << "#include <iostream>\n"
         << "#include <cstring>\n"
         << "#include <stdio.h>\n"
         << "\n"
         << "#ifndef YY_parse_NERRS\n"
         << "#define YY_parse_NERRS " << deamer::BisonBuilder::langDef->GetLanguageName() << "nerrs\n"
         << "#endif //YY_parse_NERRS\n"
         << "#ifndef YY_parse_LLOC\n"
         << "#define YY_parse_LLOC " << deamer::BisonBuilder::langDef->GetLanguageName() << "lloc\n"
         << "#endif //YY_parse_LLOC\n"
         << "\n"
         << "#define YYERROR_VERBOSE\n"
         << "\n"
         << "extern \"C\" void " << deamer::BisonBuilder::langDef->GetLanguageName() << "error(char* s);\n" 
         << "extern \"C\" int " << deamer::BisonBuilder::langDef->GetLanguageName() << "parse();\n" 
         << "extern \"C\" FILE* " << deamer::BisonBuilder::langDef->GetLanguageName() << "in;\n" 
         << "int " << deamer::BisonBuilder::langDef->GetLanguageName() << "lex();\n" 
         << "%}\n\n";
    deamer::BisonBuilder::includePart = oss3.str();
    return true;
}