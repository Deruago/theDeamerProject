#include "Deamer/ParserGen/BisonBuilder.h"
#include <sstream>
#include <fstream>
#include <ostream>

BisonBuilder::BisonBuilder()
{

}

BisonBuilder::BisonBuilder(LanguageDefinition* langDef) : BisonBuilder::BisonBuilder()
{
    BisonBuilder::langDef = langDef;
}

void BisonBuilder::AddNode(Node* node)
{
    std::ostringstream oss;
    oss << "%token " << node->TokenName << '\n';
    BisonBuilder::tokenDeclarationPart += oss.str();

    std::ostringstream oss2;
    oss2 << "%type <DeamerNode> " << node->TokenName << '\n';
    BisonBuilder::typeDeclarationPart += oss2.str();
}

void BisonBuilder::AddType(Type* type)
{
    std::ostringstream oss;
    oss << "%type <ASTNODE> " << type->TokenName << '\n';
    BisonBuilder::typeDeclarationPart += oss.str();

    std::ostringstream oss2;
    if (!BisonBuilder::IsFirstType)
    {
        oss2 << ";\n\n";
    }
    else
    {
        BisonBuilder::firstType = type;
    }
    

    BisonBuilder::IsFirstType = false;

    oss2 << type->TokenName << ":\n";
    BisonBuilder::curRuleSizeOfType = type->Rules.size();
    BisonBuilder::currentRulesBuilt = 0;
    BisonBuilder::ruleDeclarationPart += oss2.str();
    BisonBuilder::curType = type;
}

void BisonBuilder::AddRule(Rule* rule)
{
    std::ostringstream oss;
    oss << "    "; 
    
    if (BisonBuilder::currentRulesBuilt >= 1)
    {
        oss << "| ";
    }
    else
    {
        oss << "  ";
    }
    

    BisonBuilder::WriteRule(rule, &oss);
    BisonBuilder::WriteRuleModificationPart(rule, &oss);
    
    oss << '\n';
    BisonBuilder::ruleDeclarationPart += oss.str();

    BisonBuilder::currentRulesBuilt += 1;
}

/*
void BisonBuilder::WriteRuleModificationPart(Rule* rule, std::ostringstream* oss)
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

void BisonBuilder::WriteRuleModificationPart(Rule* rule, std::ostringstream* oss)
{
    *oss << "{\n";
    if (BisonBuilder::curType == BisonBuilder::firstType)
    {
        *oss << "      AstTree_" << BisonBuilder::curType->TokenName << "* ASTTREE_" << BisonBuilder::curType->TokenName << " = new AstTree_" << BisonBuilder::curType->TokenName << "({";
    }
    else
    {
        *oss << "      $$ = new AstNode_" << BisonBuilder::curType->TokenName << "({";
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
                *oss << "new AstNode_" << rule->Tokens[j]->TokenName << "($" << j + 1 << ")";
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
            *oss << "new AstNode_" << rule->Tokens[i]->TokenName << "($" << i + 1 << ")";
        }
        else
        {
            *oss << "$" << i + 1;
        }
    }
    *oss << "});\n";
    if (BisonBuilder::curType == BisonBuilder::firstType)
    {
        *oss << "      ASTTREE_" << BisonBuilder::curType->TokenName << "->SetCurrentTree(ASTTREE_" << BisonBuilder::curType->TokenName << ");\n";
    }
    *oss << "    }";
}

void BisonBuilder::WriteRule(Rule* rule, std::ostringstream* oss)
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

bool BisonBuilder::FinishBuild()
{
    std::ostringstream extendedFunctionPart;
    extendedFunctionPart << "void " << BisonBuilder::langDef->GetLanguageName() << "error(char *s)\n" << "{\n" << "    printf(\"Syntax error on line %s\\n\", s);\n" << "}\n\n";
    extendedFunctionPart << "AstNode* " << BisonBuilder::langDef->GetLanguageName() << "Parser::ParseText(std::string inputText)\n"
                         << "{\n"
                         << "    FILE* tmpFile = fmemopen((void*)inputText.c_str(), inputText.size(), \"r\");\n"
                         << "    if (tmpFile == nullptr)\n"
                         << "    {\n"
                         << "        return nullptr;\n"
                         << "    }\n"
                         << "    " << BisonBuilder::langDef->GetLanguageName() << "in = tmpFile;\n"
                         << "    " << BisonBuilder::langDef->GetLanguageName() << "parse();\n"
                         << "    return AstTree_" << BisonBuilder::firstType->TokenName << "::currentTree;\n"
                         << "}\n\n";
    extendedFunctionPart << "AstNode* " << BisonBuilder::langDef->GetLanguageName() << "Parser::ParseFile(FILE* inputFile)\n"
                         << "{\n"
                         << "    if (inputFile == nullptr)\n"
                         << "    {\n"
                         << "        return nullptr;\n"
                         << "    }\n"
                         << "    " << BisonBuilder::langDef->GetLanguageName() << "in = inputFile;\n"
                         << "    " << BisonBuilder::langDef->GetLanguageName() << "parse();\n"
                         << "    return AstTree_" << BisonBuilder::firstType->TokenName << "::currentTree;\n"
                         << "}\n\n";
    extendedFunctionPart << "AstNode* " << BisonBuilder::langDef->GetLanguageName() << "Parser::ParseFile(std::string fileLocation)\n"
                         << "{\n"
                         << "    FILE* inputFile = fopen(fileLocation.c_str(), \"r\");;\n"
                         << "    if (inputFile == nullptr)\n"
                         << "    {\n"
                         << "        return nullptr;\n"
                         << "    }\n"
                         << "    " << BisonBuilder::langDef->GetLanguageName() << "in = inputFile;\n"
                         << "    " << BisonBuilder::langDef->GetLanguageName() << "parse();\n"
                         << "    return AstTree_" << BisonBuilder::firstType->TokenName << "::currentTree;\n"
                         << "}\n\n";

    std::ostringstream oss;
    oss << BisonBuilder::includePart << BisonBuilder::tokenDeclarationPart <<  '\n' << BisonBuilder::typeDeclarationPart << '\n' << BisonBuilder::unionDeclarationPart << BisonBuilder::ruleDeclarationPart << ";\n\n\n%%\n\n\n" << extendedFunctionPart.str();
    BisonBuilder::Output = oss.str();
    return true;
}

bool BisonBuilder::StartBuild()
{
    BisonBuilder::IsFirstType = true;
    std::ostringstream oss;
    oss << "%union{\n"
        << "    AstInformation* DeamerNode;\n"
        << "    AstInformation* DeamerType;\n"
        << "    AstNode* ASTNODE;\n"
        << "}\n\n\n";
    BisonBuilder::unionDeclarationPart = oss.str();

    std::ostringstream oss2;
    oss2 << "\n%%\n\n\n";
    BisonBuilder::ruleDeclarationPart = oss2.str();

    std::ostringstream oss3;
    oss3 << "%{\n" 
         << "#include <AstNodes.h>\n"
         << "#include <Deamer/AstGen/AstInformation.h>\n"
         << "#include <Deamer/AstGen/AstNode.h>\n"
         << "#include <Deamer/AstGen/AstTree.h>\n"
         << "#include \"./" << BisonBuilder::langDef->GetLanguageName() << "Parser.h\"\n"
         << "#include <iostream>\n"
         << "#include <cstring>\n"
         << "#include <stdio.h>\n"
         << "#define YYERROR_VERBOSE\n" 
         << "extern \"C\" void " << BisonBuilder::langDef->GetLanguageName() << "error(char* s);\n" 
         << "extern \"C\" int " << BisonBuilder::langDef->GetLanguageName() << "parse();\n" 
         << "extern \"C\" FILE* " << BisonBuilder::langDef->GetLanguageName() << "in;\n" 
         << "int " << BisonBuilder::langDef->GetLanguageName() << "lex();\n" 
         << "%}\n\n";
    BisonBuilder::includePart = oss3.str();
    return true;
}