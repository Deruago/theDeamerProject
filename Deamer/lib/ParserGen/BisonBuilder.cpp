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
#include <ostream>

deamer::BisonBuilder::BisonBuilder()
{

}

deamer::BisonBuilder::BisonBuilder(LanguageDefinition* langDef) : BisonBuilder()
{
    BisonBuilder::langDef = langDef;
}

void deamer::BisonBuilder::AddNode(Node* node)
{
    std::ostringstream oss;
    oss << "%token " << node->TokenName << '\n';
    tokenDeclarationPart += oss.str();

    std::ostringstream oss2;
    oss2 << "%type <DeamerNode> " << node->TokenName << '\n';
    typeDeclarationPart += oss2.str();
}

void deamer::BisonBuilder::AddType(Type* type)
{
    std::ostringstream oss;
    oss << "%type <ASTNODE> " << type->TokenName << '\n';
    typeDeclarationPart += oss.str();

    std::ostringstream oss2;
    if (!IsFirstType)
    {
        oss2 << ";\n\n";
    }
    else
    {
        firstType = type;
    }
    

    IsFirstType = false;

    oss2 << type->TokenName << ":\n";
    curRuleSizeOfType = type->Rules.size();
    currentRulesBuilt = 0;
    ruleDeclarationPart += oss2.str();
    curType = type;
}

void deamer::BisonBuilder::AddRule(Rule* rule)
{
    std::ostringstream oss;
    oss << "    "; 
    
    if (currentRulesBuilt >= 1)
    {
        oss << "| ";
    }
    else
    {
        oss << "  ";
    }
    

    WriteRule(rule, &oss);
    WriteRuleModificationPart(rule, &oss);
    
    oss << '\n';
    ruleDeclarationPart += oss.str();

    currentRulesBuilt += 1;
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

void deamer::BisonBuilder::WriteRuleModificationPart(Rule* rule, std::ostringstream* oss) const
{
    *oss << "{\n";
    if (curType == firstType)
    {
        *oss << "      " << langDef->GetLanguageName() << "::" << "AstTree_" << curType->TokenName << "* ASTTREE_" << curType->TokenName << " = new " << langDef->GetLanguageName() << "::" << "AstTree_" << curType->TokenName << "({";
    }
    else
    {
        *oss << "      $$ = new " << langDef->GetLanguageName() << "::" << "AstNode_" << curType->TokenName << "({";
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
                *oss << "new " << langDef->GetLanguageName() << "::" << "AstNode_" << rule->Tokens[j]->TokenName << "($" << j + 1 << ")";
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
            *oss << "new " << langDef->GetLanguageName() << "::" << "AstNode_" << rule->Tokens[i]->TokenName << "($" << i + 1 << ")";
        }
        else
        {
            *oss << "$" << i + 1;
        }
    }
    *oss << "});\n";
    if (curType == firstType)
    {
        *oss << "      ASTTREE_" << curType->TokenName << "->SetCurrentTree(ASTTREE_" << curType->TokenName << ");\n";
    }
    *oss << "    }";
}

void deamer::BisonBuilder::WriteRule(Rule* rule, std::ostringstream* oss)
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
    extendedFunctionPart << "void " << langDef->GetLanguageName() << "error(char *s)\n" << "{\n" << "    printf(\"Syntax error on line %s\\n\", s);\n" << "}\n\n";
    extendedFunctionPart << "deamer::AstNode* " << langDef->GetLanguageName() << "::" << langDef->GetLanguageName() << "Parser::ParseText(std::string inputText)\n"
                         << "{\n"
                         << "    FILE* tmpFile = fmemopen((void*)inputText.c_str(), inputText.size(), \"r\");\n"
                         << "    if (tmpFile == nullptr)\n"
                         << "    {\n"
                         << "        return nullptr;\n"
                         << "    }\n"
                         << "    " << langDef->GetLanguageName() << "in = tmpFile;\n"
                         << "    " << langDef->GetLanguageName() << "parse();\n"
                         << "    return AstTree_" << firstType->TokenName << "::currentTree;\n"
                         << "}\n\n";
    extendedFunctionPart << "deamer::AstNode* " << langDef->GetLanguageName() << "::" << langDef->GetLanguageName() << "Parser::ParseFile(FILE* inputFile)\n"
                         << "{\n"
                         << "    if (inputFile == nullptr)\n"
                         << "    {\n"
                         << "        return nullptr;\n"
                         << "    }\n"
                         << "    " << langDef->GetLanguageName() << "in = inputFile;\n"
                         << "    " << langDef->GetLanguageName() << "parse();\n"
                         << "    return AstTree_" << firstType->TokenName << "::currentTree;\n"
                         << "}\n\n";
    extendedFunctionPart << "deamer::AstNode* " << langDef->GetLanguageName() << "::" << langDef->GetLanguageName() << "Parser::ParseFile(std::string fileLocation)\n"
                         << "{\n"
                         << "    FILE* inputFile = fopen(fileLocation.c_str(), \"r\");;\n"
                         << "    if (inputFile == nullptr)\n"
                         << "    {\n"
                         << "        return nullptr;\n"
                         << "    }\n"
                         << "    " << langDef->GetLanguageName() << "in = inputFile;\n"
                         << "    " << langDef->GetLanguageName() << "parse();\n"
                         << "    return AstTree_" << firstType->TokenName << "::currentTree;\n"
                         << "}\n\n";
    extendedFunctionPart << langDef->GetLanguageName() << "::" << langDef->GetLanguageName() << "Parser::" << langDef->GetLanguageName() << "Parser()\n"
                         << "{\n"
                         << "}\n\n";
    extendedFunctionPart << langDef->GetLanguageName() << "::" << langDef->GetLanguageName() << "Parser::~" << langDef->GetLanguageName() << "Parser()\n"
                         << "{\n"
                         << "}\n\n";

    std::ostringstream oss;
    oss << includePart << tokenDeclarationPart <<  '\n' << typeDeclarationPart << '\n' << unionDeclarationPart << ruleDeclarationPart << ";\n\n\n%%\n\n\n" << extendedFunctionPart.str();
    Output = oss.str();
    return true;
}

bool deamer::BisonBuilder::StartBuild()
{
    IsFirstType = true;
    std::ostringstream oss;
    oss << "%union{\n"
        << "    deamer::AstInformation* DeamerNode;\n"
        << "    deamer::AstInformation* DeamerType;\n"
        << "    deamer::AstNode* ASTNODE;\n"
        << "}\n\n\n";
    unionDeclarationPart = oss.str();

    std::ostringstream oss2;
    oss2 << "\n%%\n\n\n";
    ruleDeclarationPart = oss2.str();

    std::ostringstream oss3;
    oss3 << "%{\n" 
         << "#include <AstNodes.h>\n"
         << "#include <Deamer/AstGen/AstInformation.h>\n"
         << "#include <Deamer/AstGen/AstNode.h>\n"
         << "#include <Deamer/AstGen/AstTree.h>\n"
         << "#include \"./" << langDef->GetLanguageName() << "Parser.h\"\n"
         << "#include <iostream>\n"
         << "#include <cstring>\n"
         << "#include <stdio.h>\n"
         << "\n"
         << "#ifndef YY_parse_NERRS\n"
         << "#define YY_parse_NERRS " << langDef->GetLanguageName() << "nerrs\n"
         << "#endif //YY_parse_NERRS\n"
         << "#ifndef YY_parse_LLOC\n"
         << "#define YY_parse_LLOC " << langDef->GetLanguageName() << "lloc\n"
         << "#endif //YY_parse_LLOC\n"
         << "\n"
         << "#define YYERROR_VERBOSE\n"
         << "\n"
         << "extern \"C\" void " << langDef->GetLanguageName() << "error(char* s);\n" 
         << "extern \"C\" int " << langDef->GetLanguageName() << "parse();\n" 
         << "extern \"C\" FILE* " << langDef->GetLanguageName() << "in;\n" 
         << "int " << langDef->GetLanguageName() << "lex();\n" 
         << "%}\n\n";
    includePart = oss3.str();
    return true;
}