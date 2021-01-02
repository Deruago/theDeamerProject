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

#include "Deamer/ParserGen/BisonBuilder/BisonParserFormatter.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include <string>
#include <sstream>


deamer::BisonParserFormatter::BisonParserFormatter(const std::string& lang_name, const std::string& firstType,
                                                   const std::string& token_declaration_part,
                                                   const std::string& type_declaration_part,
                                                   const std::string& rule_declaration_part,
                                                   const LanguageDefinition* language_definition) : language_definition_(language_definition)
{
	language_name_ = lang_name;
	first_type_name_ = firstType;
	include_part_ = MakeInclude();
	union_declaration_part_ = MakeUnion();
	part_between_union_and_rule_sections_ = MakeSeperationPartBetweenUnionAndRuleParts();
	AddTokenDeclarationPart(token_declaration_part);
	AddTypeDeclarationPart(type_declaration_part);
	AddRuleDeclarationPart(rule_declaration_part);
}

std::string deamer::BisonParserFormatter::MakeParserFile(std::ostringstream& ParserFunctions) const
{
	MakeParserErrorFunction(ParserFunctions);
	MakeParseTextFunction(ParserFunctions);
	MakeParseFileFunction(ParserFunctions);
	MakeParseFileLocationFunction(ParserFunctions);
	MakeParserConstructor(ParserFunctions);
	MakeParserDestructor(ParserFunctions);

	return CombineParserPartsIntoOnePart(ParserFunctions);
}

void deamer::BisonParserFormatter::MakeParserErrorFunction(std::ostringstream& ParserFunctions) const
{
	ParserFunctions << "void " << language_name_ << "error(char *s)\n"
		<< "{\n"
		<< "    printf(\"Syntax error on line %s\\n\", s);\n"
		<< "}\n\n";
}

void deamer::BisonParserFormatter::MakeParseTextFunction(std::ostringstream& extendedFunctionPart) const
{
	extendedFunctionPart << "deamer::AstNode* " << language_name_ << "::" << language_name_ << "Parser::ParseText(std::string inputText)\n"
		<< "{\n"
		<< "    FILE* tmpFile = fmemopen((void*)inputText.c_str(), inputText.size(), \"r\");\n"
		<< "    if (tmpFile == nullptr)\n"
		<< "    {\n"
		<< "        return nullptr;\n"
		<< "    }\n"
		<< "    " << language_name_ << "in = tmpFile;\n"
		<< "    " << language_name_ << "parse();\n"
		<< "    return AstTree_" << first_type_name_ << "::currentTree;\n"
		<< "}\n\n";
}

void deamer::BisonParserFormatter::MakeParseFileFunction(std::ostringstream& extendedFunctionPart) const
{
	extendedFunctionPart << "deamer::AstNode* " << language_name_ << "::" << language_name_ << "Parser::ParseFile(FILE* inputFile)\n"
		<< "{\n"
		<< "    if (inputFile == nullptr)\n"
		<< "    {\n"
		<< "        return nullptr;\n"
		<< "    }\n"
		<< "    " << language_name_ << "in = inputFile;\n"
		<< "    " << language_name_ << "parse();\n"
		<< "    return AstTree_" << first_type_name_ << "::currentTree;\n"
		<< "}\n\n";
}

void deamer::BisonParserFormatter::MakeParseFileLocationFunction(std::ostringstream& extendedFunctionPart) const
{
	extendedFunctionPart << "deamer::AstNode* " << language_name_ << "::" << language_name_ << "Parser::ParseFile(std::string fileLocation)\n"
		<< "{\n"
		<< "    FILE* inputFile = fopen(fileLocation.c_str(), \"r\");;\n"
		<< "    if (inputFile == nullptr)\n"
		<< "    {\n"
		<< "        return nullptr;\n"
		<< "    }\n"
		<< "    " << language_name_ << "in = inputFile;\n"
		<< "    " << language_name_ << "parse();\n"
		<< "    return AstTree_" << first_type_name_ << "::currentTree;\n"
		<< "}\n\n";
}

void deamer::BisonParserFormatter::MakeParserConstructor(std::ostringstream& extendedFunctionPart) const
{
	extendedFunctionPart << language_name_ << "::" << language_name_ << "Parser::" << language_name_ << "Parser()\n"
		<< "{\n"
		<< "}\n\n";
}

void deamer::BisonParserFormatter::MakeParserDestructor(std::ostringstream& extendedFunctionPart) const
{
	extendedFunctionPart << language_name_ << "::" << language_name_ << "Parser::~" << language_name_ << "Parser()\n"
		<< "{\n"
		<< "}\n\n";
}

std::string deamer::BisonParserFormatter::MakeUnion() const
{
	std::ostringstream oss;
	oss << "%union{\n"
		<< "    deamer::AstInformation* DeamerNode;\n"
		<< "    deamer::AstInformation* DeamerType;\n"
		<< "    deamer::AstNode* ASTNODE;\n"
		<< MakeUnionAstNodes()
		<< "}\n\n\n";
	return oss.str();
}

std::string deamer::BisonParserFormatter::MakeUnionAstNodes() const
{
	std::string union_ast_nodes;
	for(Type* type : language_definition_->GetTypes())
	{
		if (type->TokenPermission.has_flag(TokenPermission_t::ignore))
			continue;
		union_ast_nodes += "    ";
		if (type->TokenType.has_flag(TokenType_t::vector))
			if (type->TokenType.has_flag(TokenType_t::start))
				union_ast_nodes += language_name_ + "::AstTree_" + type->TokenName + "* " + language_name_ + "_" + type->TokenName;
			else
				union_ast_nodes += "std::vector<" + language_name_ + "::AstNode_" + type->TokenName + "*>* " + language_name_ + "_" + type->TokenName;
		else
			if (type->TokenType.has_flag(TokenType_t::start))
				union_ast_nodes += language_name_ + "::AstTree_" + type->TokenName + "* " + language_name_ + "_" + type->TokenName;
			else
				union_ast_nodes += language_name_ + "::AstNode_" + type->TokenName + "* " + language_name_ + "_" + type->TokenName;
		union_ast_nodes += ";\n";
	}
	
	for(Node* node : language_definition_->GetNodes())
	{
		if (node->TokenPermission.has_flag(TokenPermission_t::ignore))
			continue;
		union_ast_nodes += "    ";
		if (node->TokenType.has_flag(TokenType_t::vector))
			union_ast_nodes += "std::vector<" + language_name_ + "::AstNode_" + node->TokenName + "*>* " + language_name_ + "_" + node->TokenName;
		else
			union_ast_nodes += language_name_ + "::AstNode_" + node->TokenName + "* " + language_name_ + "_" + node->TokenName;
		union_ast_nodes += ";\n";
	}

	return union_ast_nodes;
}

std::string deamer::BisonParserFormatter::MakeInclude() const
{
	std::ostringstream oss;
	oss << "%{\n"
		<< "#include <AstNodes.h>\n"
		<< "#include <Deamer/AstGen/AstInformation.h>\n"
		<< "#include <Deamer/AstGen/AstNode.h>\n"
		<< "#include <Deamer/AstGen/AstTree.h>\n"
		<< "#include \"./" << language_name_ << "Parser.h\"\n"
		<< "#include <vector>\n"
		<< "#include <iostream>\n"
		<< "#include <cstring>\n"
		<< "#include <stdio.h>\n"
		<< "\n"
		<< "#ifndef YY_parse_NERRS\n"
		<< "#define YY_parse_NERRS " << language_name_ << "nerrs\n"
		<< "#endif //YY_parse_NERRS\n"
		<< "#ifndef YY_parse_LLOC\n"
		<< "#define YY_parse_LLOC " << language_name_ << "lloc\n"
		<< "#endif //YY_parse_LLOC\n"
		<< "\n"
		<< "#define YYERROR_VERBOSE\n"
		<< "\n"
		<< "extern \"C\" void " << language_name_ << "error(char* s);\n"
		<< "extern \"C\" int " << language_name_ << "parse();\n"
		<< "extern \"C\" FILE* " << language_name_ << "in;\n"
		<< "int " << language_name_ << "lex();\n"
		<< "%}\n\n";
	return oss.str();
}

std::string deamer::BisonParserFormatter::MakeSeperationPartBetweenUnionAndRuleParts() const
{
	std::ostringstream oss;
	oss << "\n%%\n\n\n";
	return oss.str();
}

std::string deamer::BisonParserFormatter::CombineParserPartsIntoOnePart(std::ostringstream& ParserFunctions) const
{
	std::ostringstream oss;
	oss << include_part_ << token_declaration_part_ << '\n' << type_declaration_part_ << '\n' << union_declaration_part_ << part_between_union_and_rule_sections_ <<  rule_declaration_part_ << "\n\n\n%%\n\n\n" << ParserFunctions.str();
	return oss.str();
}

void deamer::BisonParserFormatter::AddTokenDeclarationPart(const std::string& token_declaration_part)
{
	token_declaration_part_ = token_declaration_part;
}

void deamer::BisonParserFormatter::AddTypeDeclarationPart(const std::string& type_declaration_part)
{
	type_declaration_part_ = type_declaration_part;
}

void deamer::BisonParserFormatter::AddRuleDeclarationPart(const std::string& rule_declaration_part)
{
	rule_declaration_part_ = rule_declaration_part;
}