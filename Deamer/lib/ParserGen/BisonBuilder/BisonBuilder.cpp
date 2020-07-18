/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -June 2020 Thimo Bohmer
 * -July 2020 Thimo Bohmer
 */

#include "Deamer/ParserGen/BisonBuilder/BisonBuilder.h"
#include <sstream>
#include <ostream>

deamer::BisonBuilder::BisonBuilder(LanguageDefinition* langDef)
{
	BisonBuilder::langDef = langDef;
	curType = nullptr;
	firstType = nullptr;
	IsFirstType = false;
	curRuleSizeOfType = 0;
	currentRulesBuilt = 0;
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
	MakeRule(rule);
	currentRulesBuilt++;
}


void deamer::BisonBuilder::MakeRule(deamer::Rule* rule)
{
	ruleDeclarationPart += FormatRule(rule);
}

std::string deamer::BisonBuilder::FormatRule(deamer::Rule* rule) const
{
	std::ostringstream oss;
	oss << "    ";

	AddCorrectNotationForNewRule(oss);

	WriteRule(rule, &oss);
	WriteRuleModificationPart(rule, &oss);

	oss << '\n';
	return oss.str();
}

void deamer::BisonBuilder::AddCorrectNotationForNewRule(std::ostringstream& oss) const
{
	if (currentRulesBuilt >= 1)
	{
		oss << "| ";
	}
	else
	{
		oss << "  ";
	}
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
	const std::string LanguageName = langDef->GetLanguageName();
	FormatTypeRulePart(rule, oss, LanguageName);
}

bool deamer::BisonBuilder::CurrentTokenIsNode(deamer::Token* CurrentToken) const
{
	return CurrentToken->IsNode;
}

bool deamer::BisonBuilder::CurrentTokenHasAnAstNode(deamer::Token* CurrentToken) const
{
	return CurrentToken->CreateAst;
}

bool deamer::BisonBuilder::CurrentTypeIsTheFirstType() const
{
	return curType == firstType;
}

void deamer::BisonBuilder::MakeArgumentReferenceVariable(std::ostringstream* oss, int& j) const
{
	*oss << "$" << j + 1;
}

void deamer::BisonBuilder::MakeArgument(const std::string LanguageName, std::ostringstream* oss, int& j, deamer::Token* CurrentToken) const
{
	if (CurrentTokenIsNode(CurrentToken))
	{
		MakeNewAstNode(LanguageName, oss, j, CurrentToken);
	}
	else
	{
		MakeArgumentReferenceVariable(oss, j);
	}
}

void deamer::BisonBuilder::AddFirstArgument(const std::string LanguageName, deamer::Rule* rule, std::ostringstream* oss, int& j) const
{
	j = 0;
	bool createdFirstParam = false;
	while (j < rule->Tokens.size() && !createdFirstParam)
	{
		Token* CurrentToken = rule->Tokens[j];
		if (CurrentTokenHasAnAstNode(CurrentToken))
		{
			MakeArgument(LanguageName, oss, j, CurrentToken);
			createdFirstParam = true;
		}
		j++;
	}
}

void deamer::BisonBuilder::MakeNewAstNode(const std::string LanguageName, std::ostringstream* oss, int ArgumentCount, deamer::Token* CurrentToken) const
{
	*oss << "new " << LanguageName << "::" << "AstNode_" << CurrentToken->TokenName << "($" << ArgumentCount + 1 << ")";
}

void deamer::BisonBuilder::AddRestOfAllArguments(const std::string LanguageName, deamer::Rule* rule, std::ostringstream* oss, int j) const
{
	for (int i = j; i < rule->Tokens.size(); i++)
	{
		Token* CurrentToken = rule->Tokens[i];
		if (!CurrentTokenHasAnAstNode(CurrentToken))
		{
			continue;
		}

		*oss << ", ";
		MakeArgument(LanguageName, oss, i, CurrentToken);
	}
}

void deamer::BisonBuilder::MakeRuleExecutionPart(const std::string LanguageName, deamer::Rule* rule, std::ostringstream* oss) const
{
	if (CurrentTypeIsTheFirstType())
	{
		MakeAstTree(LanguageName, oss);
	}
	else
	{
		MakeAstNode(LanguageName, oss);
	}

	//This makes sure we dont create random ',' when nothing can be added.
	int j;
	AddFirstArgument(LanguageName, rule, oss, j);
	AddRestOfAllArguments(LanguageName, rule, oss, j);
	*oss << "});\n";
}

void deamer::BisonBuilder::MakeAstTree(const std::string LanguageName, std::ostringstream* oss) const
{
	*oss << "      " << LanguageName << "::" << "AstTree_" << curType->TokenName << "* ASTTREE_" << curType->TokenName << " = new " << LanguageName << "::" << "AstTree_" << curType->TokenName << "({";
}

void deamer::BisonBuilder::MakeAstNode(const std::string LanguageName, std::ostringstream* oss) const
{
	*oss << "      $$ = new " << LanguageName << "::" << "AstNode_" << curType->TokenName << "({";
}

void deamer::BisonBuilder::MakeOutputCodeWhenNodeIsStartType(std::ostringstream* oss) const
{
	if (CurrentTypeIsTheFirstType())
	{
		MakeOutputCodeForAstTree(oss);
	}
}

void deamer::BisonBuilder::MakeOutputCodeForAstTree(std::ostringstream* oss) const
{
	*oss << "      ASTTREE_" << curType->TokenName << "->SetCurrentTree(ASTTREE_" << curType->TokenName << ");\n";
}

void deamer::BisonBuilder::FormatTypeRulePart(deamer::Rule* rule, std::ostringstream* oss, const std::string LanguageName) const
{
	*oss << "{\n";
	MakeRuleExecutionPart(LanguageName, rule, oss);
	MakeOutputCodeWhenNodeIsStartType(oss);
	*oss << "    }";
}

void deamer::BisonBuilder::WriteRule(Rule* rule, std::ostringstream* oss) const
{
	for (int i = 0; i < rule->Tokens.size(); i++)
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
	std::ostringstream ParserFunctions;

	MakeParserErrorFunction(ParserFunctions);
	MakeParseTextFunction(ParserFunctions);
	MakeParseFileFunction(ParserFunctions);
	MakeParseFileLocationFunction(ParserFunctions);
	MakeParserConstructor(ParserFunctions);
	MakeParserDestructor(ParserFunctions);

	Output = CombineParserPartsIntoOnePart(ParserFunctions);
	return true;
}

void deamer::BisonBuilder::MakeParserErrorFunction(std::ostringstream& ParserFunctions) const
{
	ParserFunctions << "void " << langDef->GetLanguageName() << "error(char *s)\n"
		<< "{\n"
		<< "    printf(\"Syntax error on line %s\\n\", s);\n"
		<< "}\n\n";
}

void deamer::BisonBuilder::MakeParseTextFunction(std::ostringstream& extendedFunctionPart) const
{
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
}

void deamer::BisonBuilder::MakeParseFileFunction(std::ostringstream& extendedFunctionPart) const
{
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
}

void deamer::BisonBuilder::MakeParseFileLocationFunction(std::ostringstream& extendedFunctionPart) const
{
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
}

void deamer::BisonBuilder::MakeParserConstructor(std::ostringstream& extendedFunctionPart) const
{
	extendedFunctionPart << langDef->GetLanguageName() << "::" << langDef->GetLanguageName() << "Parser::" << langDef->GetLanguageName() << "Parser()\n"
		<< "{\n"
		<< "}\n\n";
}

void deamer::BisonBuilder::MakeParserDestructor(std::ostringstream& extendedFunctionPart) const
{
	extendedFunctionPart << langDef->GetLanguageName() << "::" << langDef->GetLanguageName() << "Parser::~" << langDef->GetLanguageName() << "Parser()\n"
		<< "{\n"
		<< "}\n\n";
}

std::string deamer::BisonBuilder::CombineParserPartsIntoOnePart(std::ostringstream& ParserFunctions) const
{
	std::ostringstream oss;
	oss << includePart << tokenDeclarationPart << '\n' << typeDeclarationPart << '\n' << unionDeclarationPart << ruleDeclarationPart << ";\n\n\n%%\n\n\n" << ParserFunctions.str();
	return oss.str();
}

bool deamer::BisonBuilder::StartBuild()
{
	IsFirstType = true;

	unionDeclarationPart = MakeUnion();
	ruleDeclarationPart = MakeBeginningRuleDeclaration();
	includePart = MakeInclude();

	return true;
}

std::string deamer::BisonBuilder::MakeUnion() const
{
	std::ostringstream oss;
	oss << "%union{\n"
		<< "    deamer::AstInformation* DeamerNode;\n"
		<< "    deamer::AstInformation* DeamerType;\n"
		<< "    deamer::AstNode* ASTNODE;\n"
		<< "}\n\n\n";
	return oss.str();
}

std::string deamer::BisonBuilder::MakeBeginningRuleDeclaration() const
{
	std::ostringstream oss;
	oss << "\n%%\n\n\n";
	return oss.str();
}

std::string deamer::BisonBuilder::MakeInclude() const
{
	std::ostringstream oss;
	oss << "%{\n"
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
	return oss.str();
}