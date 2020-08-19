/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/AstGen/AstNodeInterpreterBasedBuilder/AstBuilder.h"
//#include "Deamer/FileBuilder/HFileBuilder/HFClassBuilder.h"
//#include "Deamer/FileBuilder/Types/FileNamespaceSection.h"
#include "Deamer/FileBuilder/Types/FileClassSection.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"
#include "Deamer/AstGen/AstNodeDataStructures/AstFileType.h"
#include <sstream>
#include <fstream>

#include "Deamer/AstGen/AstNodeFormatter.h"

deamer::AstBuilder::AstBuilder()
{
    Directory = "";
    _AstNode = new FileClassSection("AstNode");
    type_void = new FileClassSection("void");
    type_int = new FileClassSection("int");
    _AstNode->AddPublicMember("Generate", {}, type_void, true);
    _AstNode->AddPublicMember("GetAstId", {}, type_int, true);
}

void deamer::AstBuilder::FillAstSourceFile(std::ofstream* astSourceFile, Token* token, std::string* defaultTokenName, bool isNode) const
{
    auto formatter = AstNodeFormatter(languageName);
    formatter.MakeAstNode(token, AstFileType::source);
    *astSourceFile << formatter.output;
}

deamer::FileClassSection* deamer::AstBuilder::GetAstNodeFileBuilderClass() const
{
    return _AstNode;
}

void deamer::AstBuilder::FillAstHeaderFile(std::ofstream* astHeaderFile, Token* token, std::string* defaultTokenName) const
{
    auto formatter = AstNodeFormatter(languageName);
    formatter.MakeAstNode(token, AstFileType::header);
    *astHeaderFile << formatter.output;
}

void deamer::AstBuilder::FillAstTreeSourceFile(std::ofstream* astSourceFile, Token* token, std::string* defaultTokenName, bool isNode) const
{
    auto formatter = AstNodeFormatter(languageName);
    formatter.MakeAstNode(token, AstFileType::source);
    *astSourceFile << formatter.output;
}

void deamer::AstBuilder::FillAstTreeHeaderFile(std::ofstream* astHeaderFile, Token* token, std::string* defaultTokenName) const
{
    auto formatter = AstNodeFormatter(languageName);
    formatter.MakeAstNode(token, AstFileType::header);
    *astHeaderFile << formatter.output;
}

std::string deamer::AstBuilder::MakeSubclassesForAstTree(Token* token) const
{
	std::string subclass_string = " : public deamer::AstNode, public deamer::AstTree";

	for(Token* base_token : token->BaseTokens)
        subclass_string += ", public " + languageName + "::AstNode_" + base_token->TokenName;

    return subclass_string + "\n";
}

std::string deamer::AstBuilder::MakeAstNodeConstructorPrototypes(Token* token) const
{
    std::string ctors;
	if (!token->TokenPermission.has_flag(TokenPermission_t::node))
	{
        Type* tmpType = static_cast<Type*>(token);
      //  for(Rule* rule : tmpType->Rules)
            //if (rule->RuleType.is_flag_not_set(RuleType_t::empty))
	       //     ctors += "            AstNode_" + rule->MakeConstructorPrototype(token) + ";\n";
	}
	return ctors;
}

std::string deamer::AstBuilder::MakeSubclassesOfToken(Token* token) const
{
    std::string subclass_string;
	if (token->BaseTokens.empty())
		subclass_string =  " : public deamer::AstNode";
	else
	{
        unsigned i = 0;
		for(Token* base_token : token->BaseTokens)
		{
			if (i == 0)
			{
			    subclass_string += " : public AstNode_" + base_token->TokenName;
			}
			else
			{
				subclass_string += ", public AstNode_" + base_token->TokenName;
			}
            i++;
		}
	}
	return subclass_string + "\n";
}

std::string deamer::AstBuilder::MakeCtorFields(Token* token) const
{
    std::string tmpCtorFields;
	if (!token->TokenPermission.has_flag(TokenPermission_t::node))
	{
        Type* tmpType = static_cast<Type*>(token);
        //const std::vector<Token*> unique_tokens = tmpType->GetVectorOfUniqueTokensDefiningThisType();
        //for (Token* unique_token : unique_tokens)
        //    if (unique_token != token)
         //       tmpCtorFields += "            " + unique_token->MakeTypeAsClassField() + ";\n";
	}
    return tmpCtorFields;
}

std::string deamer::AstBuilder::MakeAstTreeConstructorPrototypes(Token* token) const
{
    std::string ctors;
    if (!token->TokenPermission.has_flag(TokenPermission_t::node))
    {
        Type* tmpType = static_cast<Type*>(token);
     //   for (Rule* rule : tmpType->Rules)
     //       if (rule->RuleType.is_flag_not_set(RuleType_t::empty))
	         //   ctors += "            AstTree_" + rule->MakeConstructorPrototype(token) + ";\n";
    }
    return ctors;
}

void deamer::AstBuilder::CreateAstNode(Token* token, bool isNode)
{
    std::string TokenName = token->TokenName;
    std::string DefaultTokenName = TokenName;
    std::ostringstream oss0;
    oss0 << "AstNode_" << TokenName;
    TokenName = oss0.str();

    std::ostringstream oss;
    oss << Directory << TokenName << ".cpp";
    std::ofstream newAstNodeSourceFile(oss.str());

    FillAstSourceFile(&newAstNodeSourceFile, token, &DefaultTokenName, isNode);
    
    newAstNodeSourceFile.close();

    std::ostringstream oss2;
    oss2 << Directory << TokenName << ".h";
    std::ofstream newAstNodeHeaderFile(oss2.str());

    FillAstHeaderFile(&newAstNodeHeaderFile, token, &DefaultTokenName);

    newAstNodeHeaderFile.close();
}

void deamer::AstBuilder::CreateAstTree(Token* token, bool isNode) const
{
    std::string TokenName = token->TokenName;
    std::string DefaultTokenName = TokenName;
    std::ostringstream oss0;
    oss0 << "AstTree_" << TokenName;
    TokenName = oss0.str();

    std::ostringstream oss;
    oss << Directory << TokenName << ".cpp";
    std::ofstream newAstTreeSourceFile(oss.str());

    FillAstTreeSourceFile(&newAstTreeSourceFile, token, &DefaultTokenName, isNode);
    
    newAstTreeSourceFile.close();

    std::ostringstream oss2;
    oss2 << Directory << TokenName << ".h";
    std::ofstream newAstTreeHeaderFile(oss2.str());

    FillAstTreeHeaderFile(&newAstTreeHeaderFile, token, &DefaultTokenName);

    newAstTreeHeaderFile.close();
}

void deamer::AstBuilder::CreateGlobalHeaderFile() const
{
    std::ostringstream oss0;
    oss0 << Directory << "AstNodes.h";
    std::ofstream newGlobalHeaderFile(oss0.str());

    newGlobalHeaderFile << "#ifndef ASTNODES_ASTNODES_H\n"
                        << "#define ASTNODES_ASTNODES_H\n"
                        << "\n";
    
    newGlobalHeaderFile.close();
}

void deamer::AstBuilder::AppendAstNodeHeaderFile(std::string TokenName) const
{
    std::ostringstream oss0;
    oss0 << Directory << "AstNodes.h";
    std::ofstream globalHeaderFile;

    globalHeaderFile.open(oss0.str(), std::ios_base::app);

    globalHeaderFile << "#include \"" << "./" << "AstNode_" << TokenName << ".h\"\n";

    globalHeaderFile.close();
}

void deamer::AstBuilder::AppendAstTreeHeaderFile(std::string TokenName) const
{
    std::ostringstream oss0;
    oss0 << Directory << "AstNodes.h";
    std::ofstream globalHeaderFile;

    globalHeaderFile.open(oss0.str(), std::ios_base::app);

    globalHeaderFile << "#include \"" << "./" << "AstTree_" << TokenName << ".h\"\n";

    globalHeaderFile.close();
}

void deamer::AstBuilder::FinishGlobalHeaderFile() const
{
    std::ostringstream oss0;
    oss0 << Directory << "AstNodes.h";
    std::ofstream globalHeaderFile;

    globalHeaderFile.open(oss0.str(), std::ios_base::app);

    globalHeaderFile << "\n"
                     << "#endif //ASTNODES_ASTNODES_H\n";

    globalHeaderFile.close();
}

void deamer::AstBuilder::CreateAstNodeEnumFile() const
{
    std::ostringstream oss0;
    oss0 << Directory << "AstEnum.h";
    std::ofstream newEnumFile(oss0.str());

    newEnumFile << "#ifndef ASTNODES_ASTENUM_H\n"
                << "#define ASTNODES_ASTENUM_H\n"
                << "\n"
                << "namespace " << languageName << "\n"
                << "{\n"
                << "    typedef enum AstEnum_s\n"
                << "    {\n";
    
    newEnumFile.close();
}

void deamer::AstBuilder::AppendAstNodeEnumFile(std::string TokenName) const
{
    std::ostringstream oss0;
    oss0 << Directory << "AstEnum.h";
    std::ofstream newEnumFile;

    newEnumFile.open(oss0.str(), std::ios_base::app);

    newEnumFile << "        " << TokenName << ",\n";

    newEnumFile.close();
}

void deamer::AstBuilder::FinishAstNodeEnumFile() const
{
    std::ostringstream oss0;
    oss0 << Directory << "AstEnum.h";
    std::ofstream newEnumFile;

    newEnumFile.open(oss0.str(), std::ios_base::app);

    newEnumFile << "    } AstEnum_t;\n"
                << "}\n"
                << "\n"
                << "#endif //ASTNODES_ASTENUM_H\n";

    newEnumFile.close();
}

void deamer::AstBuilder::SetLanguageName(std::string languageName)
{
    AstBuilder::languageName = languageName;
}
