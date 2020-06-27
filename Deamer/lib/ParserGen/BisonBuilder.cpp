#include "Deamer/ParserGen/BisonBuilder.h"
#include <sstream>
#include <fstream>
#include <ostream>

BisonBuilder::BisonBuilder()
{

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
    oss << "%type <DeamerType> " << type->TokenName << '\n';
    BisonBuilder::typeDeclarationPart += oss.str();

    std::ostringstream oss2;
    if (!BisonBuilder::IsFirstType)
    {
        oss2 << ";\n\n";
    }

    BisonBuilder::IsFirstType = false;

    oss2 << type->TokenName << ":\n";
    BisonBuilder::curRuleSizeOfType = type->Rules.size();
    BisonBuilder::currentRulesBuilt = 0;
    BisonBuilder::ruleDeclarationPart += oss2.str();
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

void BisonBuilder::WriteRuleModificationPart(Rule* rule, std::ostringstream* oss)
{
    *oss << "{\n";
    for(int i = 0; i < rule->Tokens.size(); i++)
    {
        if (!rule->Tokens[i]->IsNode)
        {
            continue;
        }

        *oss << "        std::cout << $" << i + 1 << ";\n";
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
    extendedFunctionPart << "void yyerror(char *s)\n" << "{\n" << "    printf(\"Syntax error on line %s\\n\", s);\n" << "}\n";

    std::ostringstream oss;
    oss << BisonBuilder::includePart << BisonBuilder::tokenDeclarationPart <<  '\n' << BisonBuilder::typeDeclarationPart << '\n' << BisonBuilder::unionDeclarationPart << BisonBuilder::ruleDeclarationPart << ";\n\n\n%%\n\n\n" << extendedFunctionPart.str();
    BisonBuilder::Output = oss.str();
    return true;
}

bool BisonBuilder::StartBuild()
{
    BisonBuilder::IsFirstType = true;
    std::ostringstream oss;
    oss << "%union{\n" << "    char DeamerNode[1024];\n" << "    char DeamerType[2048];\n" << "}\n\n\n";
    BisonBuilder::unionDeclarationPart = oss.str();

    std::ostringstream oss2;
    oss2 << "\n%%\n\n\n";
    BisonBuilder::ruleDeclarationPart = oss2.str();

    std::ostringstream oss3;
    oss3 << "%{\n" << "#include <iostream>\n" << "#include <cstring>\n" << "#define YYERROR_VERBOSE\n" << "extern \"C\" void yyerror(char* s);\n" << "extern \"C\" int yyparse();\n" << "extern \"C\" FILE* yyin;\n" << "int yylex();\n" << "%}\n\n";
    BisonBuilder::includePart = oss3.str();
    return true;
}