/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/AstGen/AstBuilder.h"
//#include "Deamer/FileBuilder/HFileBuilder/HFClassBuilder.h"
//#include "Deamer/FileBuilder/Types/FileNamespaceSection.h"
#include "Deamer/LanguageGen/Token.h"
#include "Deamer/LanguageGen/Type.h"
#include "Deamer/LanguageGen/Rule.h"
#include <sstream>
#include <fstream>

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
    std::string isNodeStr;
    if(isNode)
    {
        isNodeStr = "true";
    }
    else
    {
        isNodeStr = "false";
    }

    const std::string tokenName = token->TokenName;
    *astSourceFile << "#include \"./AstNode_" << tokenName << ".h\"\n"
             << "#include <Deamer/AstGen/AstNode.h>\n"
             << "#include <Deamer/AstGen/AstInformation.h>\n"
			 << MakeAstNodeHeaderIncludes(token)
			 << "#include <iostream>\n"
             << "#include <fstream>\n"
             << "#include <vector>\n"
             << '\n'
		     << languageName << "::" << "AstNode_" << tokenName << "::" << "AstNode_" << tokenName << "(bool isNode, std::string astNodeName)" << MakeCtorImplementationsForAstSpecificCtor(token) << "\n"
			 << "{\n"
			 << "}\n"
			 << "\n"
             << "int " << languageName << "::AstNode_" << tokenName << "::" << "GetAstId" << "()\n"
             << "{\n"
             << "    " << "return (unsigned int)" << languageName << "::AstNode_" << tokenName << "::AstType" << ";\n"
             << "}\n"
             << "\n"
             << languageName << "::" << "AstNode_" << tokenName << "::" << "AstNode_" << tokenName << "(std::vector<deamer::AstNode*> astNodes)" << MakeCtorImplementationsForAstNodes(token)
             << "{\n"
             << "}\n"
             << "\n"
             << languageName << "::" << "AstNode_" << tokenName << "::" << "AstNode_" << tokenName << "(deamer::AstInformation* astInformation)" << MakeCtorImplementationsForAstInformation(token)
             << "{\n"
             << "}\n"
             << "\n"
		     << MakeRuleConstructorsForAstNode(token)
             << "void " << languageName << "::AstNode_" << tokenName << "::Generate()"
             << "{\n"
             << "\n"
             << "}\n";
}

deamer::FileClassSection* deamer::AstBuilder::GetAstNodeFileBuilderClass() const
{
    return _AstNode;
}

void deamer::AstBuilder::FillAstHeaderFile(std::ofstream* astHeaderFile, Token* token, std::string* defaultTokenName) const
{
    /*const auto namespace_language = new FileNamespaceSection(languageName);
    const auto hcb = new HFClassBuilder({ "ASTNODES" }, tokenName, namespace_language, { GetAstNodeFileBuilderClass() });
    hcb->AddInclude("Deamer/AstGen/AstNode");
    hcb->AddInclude("Deamer/AstGen/AstInformation");
    hcb->AddInclude("AstEnum");
    hcb->AddInclude("vector", true);

    *astHeaderFile << hcb->GetDefinition();
    delete hcb;
    delete namespace_language;
	*/
//*
    std::string tokenName = token->TokenName;
    std::string tokenNameUpper;
    for (char i : tokenName)
    {
        tokenNameUpper += toupper(i);
    }
    *astHeaderFile << "#ifndef ASTNODES_" << tokenNameUpper << "_H\n"
                   << "#define ASTNODES_" << tokenNameUpper << "_H\n"
                   << "\n"
                   << "#include <Deamer/AstGen/AstNode.h>\n"
                   << "#include <Deamer/AstGen/AstInformation.h>\n"
                   << MakeAstNodeBaseHeaderIncludes(token)
                   << "#include \"AstEnum.h\"\n"
                   << "#include <vector>\n"
                   << "\n"
                   << "namespace " << languageName << "\n"
                   << "{\n"
				   << MakeAstNodeForwardDeclarations(token)
                   << "    class AstNode_" << tokenName << MakeSubclassesOfToken(token)
                   << "    {\n"
                   << "        private:\n"
                   << "        protected:\n"
                   << "        public:\n"
				   << MakeCtorFields(token)
                   << "            const " << languageName << "::AstEnum_t AstType = " << languageName << "::AstEnum_t::" << *defaultTokenName << ";\n"
				   << "            AstNode_" << tokenName << "(bool isNode, std::string astNodeName);\n"
                   << "            AstNode_" << tokenName << "(std::vector<deamer::AstNode*> astNodes);\n"
                   << "            AstNode_" << tokenName << "(deamer::AstInformation* astInformation);\n"
                   << MakeAstNodeConstructorPrototypes(token)
                   << "            void Generate() override;\n"
                   << "            int GetAstId() override;\n"
                   << "    };\n"
                   << "}\n"
                   << "\n"
                   << "#endif //ASTNODES_" << tokenNameUpper << "_H\n";
                  //*/
}

std::string deamer::AstBuilder::MakeRuleConstructorsForAstNode(Token* token) const
{
    std::string isNodeStr;
    if (token->TokenPermission.has_flag(TokenPermission_t::node))
        isNodeStr = "true";
    else
        isNodeStr = "false";
    std::string ctors;
    if (!token->TokenPermission.has_flag(TokenPermission_t::node))
    {
        Type* tmpType = static_cast<Type*>(token);
        for (Rule* rule : tmpType->Rules)
        {
            if (rule->RuleType.is_flag_not_set(RuleType_t::empty))
            {
                ctors += languageName + "::AstNode_" + token->TokenName + "::AstNode_" + rule->MakeConstructorPrototype(token) + MakeCtorImplementationsForAstSpecificCtor(token);
                ctors += "\n";
				ctors += rule->MakeConstructor(token) + "\n";
            }
        }
    }
	return ctors;
}

std::string deamer::AstBuilder::MakeRuleConstructorsForAstTree(Token* token) const
{
    std::string isNodeStr;
    if (token->TokenPermission.has_flag(TokenPermission_t::node))
        isNodeStr = "true";
    else
        isNodeStr = "false";
    std::string ctors;
	if (!token->TokenPermission.has_flag(TokenPermission_t::node))
	{
	    Type* tmpType = static_cast<Type*>(token);
	    for (Rule* rule : tmpType->Rules)
	    {
	        if (rule->RuleType.is_flag_not_set(RuleType_t::empty))
	        {
                ctors += languageName + "::AstTree_" + token->TokenName + "::AstTree_" + rule->MakeConstructorPrototype(token) + MakeCtorImplementationsForAstSpecificCtor(token);
				ctors += "\n";
			    ctors += rule->MakeConstructor(token) + "\n";    
	        }
	    }
	}
    return ctors;
}

std::string deamer::AstBuilder::MakeCtorImplementationsForAstInformation(Token* token) const
{
    std::string CtorImplementation;
	
    std::string isNodeStr;
    if (token->TokenPermission.has_flag(TokenPermission_t::node))
        isNodeStr = "true";
    else
        isNodeStr = "false";

	if (token->BaseTokens.empty())
	{
        return " : deamer::AstNode::AstNode(astInformation, " + isNodeStr + ", \"" + token->TokenName + "\")\n";
	}
	
    unsigned i = 0;
    for (Token* base_type : token->BaseTokens)
    {
    	if (i == 0)
	        CtorImplementation += " : AstNode_" + base_type->TokenName + "(astInformation)\n";
        else
            CtorImplementation += ", AstNode_" + base_type->TokenName + "(astInformation)\n";
        i++;
    }
	
    return CtorImplementation;
}

std::string deamer::AstBuilder::MakeCtorImplementationsForAstNodes(Token* token) const
{
    std::string CtorImplementation;

    std::string isNodeStr;
    if (token->TokenPermission.has_flag(TokenPermission_t::node))
        isNodeStr = "true";
    else
        isNodeStr = "false";

    if (token->BaseTokens.empty())
    {
        return " : deamer::AstNode::AstNode(astNodes, " + isNodeStr + ", \"" + token->TokenName + "\")\n";
    }

    unsigned i = 0;
    for (Token* base_type : token->BaseTokens)
    {
        if (i == 0)
            CtorImplementation += " : AstNode_" + base_type->TokenName + "(astNodes)\n";
        else
            CtorImplementation += ", AstNode_" + base_type->TokenName + "(astNodes)\n";
        i++;
    }

    return CtorImplementation;
}

std::string deamer::AstBuilder::MakeCtorImplementationsForAstSpecificCtor(Token* token) const
{
    std::string CtorImplementation;

    std::string isNodeStr;
    if (token->TokenPermission.has_flag(TokenPermission_t::node))
        isNodeStr = "true";
    else
        isNodeStr = "false";

    if (token->BaseTokens.empty())
    {
        return " : deamer::AstNode::AstNode(" + isNodeStr + ", \"" + token->TokenName + "\")\n";
    }

    unsigned i = 0;
    for (Token* base_type : token->BaseTokens)
    {
        if (i == 0)
            CtorImplementation += " : AstNode_" + base_type->TokenName + "(" + isNodeStr + ", \"" + token->TokenName + "\")\n";
        else
            CtorImplementation += ", AstNode_" + base_type->TokenName + "(" + isNodeStr + ", \"" + token->TokenName + "\")\n";
        i++;
    }

	return CtorImplementation;
}

void deamer::AstBuilder::FillAstTreeSourceFile(std::ofstream* astSourceFile, Token* token, std::string* defaultTokenName, bool isNode) const
{
    std::string isNodeStr;
    if(isNode)
    {
        isNodeStr = "true";
    }
    else
    {
        isNodeStr = "false";
    }

    const std::string tokenName = token->TokenName;
    *astSourceFile << "#include \"./AstTree_" << tokenName << ".h\"\n"
        << "#include \"Deamer/AstGen/AstTree.h\"\n"
        << "#include \"Deamer/AstGen/AstNode.h\"\n"
        << "#include \"Deamer/AstGen/AstInformation.h\"\n"
        << MakeAstNodeHeaderIncludes(token)
        << "#include <iostream>\n"
        << "#include <fstream>\n"
        << "#include <vector>\n"
        << '\n'
        << languageName << "::" << "AstTree_" << tokenName << "* " << languageName << "::AstTree_" << tokenName << "::currentTree;\n"
        << '\n'
        << "int " << languageName << "::AstTree_" << tokenName << "::" << "GetAstId" << "()\n"
        << "{\n"
        << "    " << "return (unsigned int)" << languageName << "::AstTree_" << tokenName << "::AstType" << ";\n"
        << "}\n"
        << "\n"
		<< languageName << "::" << "AstTree_" << tokenName << "::" << "AstTree_" << tokenName << "(bool isNode, std::string astNodeName)" << MakeCtorImplementationsForAstSpecificCtor(token) << "\n"
        << "{\n"
        << "}\n"
		<< "\n"
        << languageName << "::" << "AstTree_" << tokenName << "::" << "AstTree_" << tokenName << "(std::vector<deamer::AstNode*> astNodes)" << MakeCtorImplementationsForAstNodes(token)
        << "{\n"
        << "}\n"
        << "\n"
        << languageName << "::" << "AstTree_" << tokenName << "::" << "AstTree_" << tokenName << "(deamer::AstInformation* astInformation)" << MakeCtorImplementationsForAstInformation(token)
	    << "{\n"
	    << "}\n"
	    << "\n"
		<< MakeRuleConstructorsForAstTree(token)
	    << "void " << languageName << "::AstTree_" << tokenName << "::SetCurrentTree(AstTree_" << tokenName << "* astTreePtr)\n"
	    << "{\n"
	    << "    " << languageName << "::AstTree_" << tokenName << "::currentTree = astTreePtr;\n"
	    << "}\n"
	    << "\n"
	    << "void " << languageName << "::AstTree_" << tokenName << "::Generate()\n"
	    << "{\n"
	    << "\n"
	    << "}\n";
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
        for(Rule* rule : tmpType->Rules)
            if (rule->RuleType.is_flag_not_set(RuleType_t::empty))
	            ctors += "            AstNode_" + rule->MakeConstructorPrototype(token) + ";\n";
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

std::string deamer::AstBuilder::MakeAstNodeBaseHeaderIncludes(Token* token) const
{
    std::string tmpHeaderIncludes;
    	for (Token* base_token : token->BaseTokens)
            tmpHeaderIncludes += "#include \"AstNode_" + base_token->TokenName + ".h\"\n";
    return tmpHeaderIncludes;
}

std::string deamer::AstBuilder::MakeAstNodeHeaderIncludes(Token* token) const
{
    std::string tmpHeaderIncludes;
    if (!token->TokenPermission.has_flag(TokenPermission_t::node))
    {
        Type* tmpType = static_cast<Type*>(token);
        const std::vector<Token*> unique_tokens = tmpType->GetVectorOfUniqueTokensDefiningThisType();
        for (Token* token_unique : unique_tokens)
            if (token_unique != token)
	            tmpHeaderIncludes += "#include \"AstNode_" + token_unique->TokenName + ".h\"\n";
    }
    return tmpHeaderIncludes;
}

std::string deamer::AstBuilder::MakeAstNodeForwardDeclarations(Token* token) const
{
    std::string tmpHeaderIncludes;
    if (!token->TokenPermission.has_flag(TokenPermission_t::node))
    {
        Type* tmpType = static_cast<Type*>(token);
        const std::vector<Token*> unique_tokens = tmpType->GetVectorOfUniqueTokensDefiningThisType();
        for (Token* token_unique : unique_tokens)
            if (token_unique != token)
                tmpHeaderIncludes += "    class AstNode_" + token_unique->TokenName + ";\n";
    }
    return tmpHeaderIncludes;
}

std::string deamer::AstBuilder::MakeCtorFields(Token* token) const
{
    std::string tmpCtorFields;
	if (!token->TokenPermission.has_flag(TokenPermission_t::node))
	{
        Type* tmpType = static_cast<Type*>(token);
        const std::vector<Token*> unique_tokens = tmpType->GetVectorOfUniqueTokensDefiningThisType();
        for (Token* unique_token : unique_tokens)
            if (unique_token != token)
                tmpCtorFields += "            " + unique_token->MakeTypeAsClassField() + ";\n";
	}
    return tmpCtorFields;
}

std::string deamer::AstBuilder::MakeAstTreeConstructorPrototypes(Token* token) const
{
    std::string ctors;
    if (!token->TokenPermission.has_flag(TokenPermission_t::node))
    {
        Type* tmpType = static_cast<Type*>(token);
        for (Rule* rule : tmpType->Rules)
            if (rule->RuleType.is_flag_not_set(RuleType_t::empty))
	            ctors += "            AstTree_" + rule->MakeConstructorPrototype(token) + ";\n";
    }
    return ctors;
}

void deamer::AstBuilder::FillAstTreeHeaderFile(std::ofstream* astHeaderFile, Token* token, std::string* defaultTokenName) const
{
    const std::string tokenName = token->TokenName;
    std::string tokenNameUpper;
    for (char i : tokenName)
    {
        tokenNameUpper += toupper(i);
    }

    *astHeaderFile << "#ifndef ASTNODES_" << tokenNameUpper << "_H\n"
                   << "#define ASTNODES_" << tokenNameUpper << "_H\n"
                   << "\n"
                   << "#include \"Deamer/AstGen/AstTree.h\"\n"
                   << "#include \"Deamer/AstGen/AstNode.h\"\n"
                   << MakeAstNodeBaseHeaderIncludes(token)
                   << "#include \"Deamer/AstGen/AstInformation.h\"\n"
                   << "#include \"AstEnum.h\"\n"
                   << "#include <string>\n"
                   << "#include <vector>\n"
                   << "\n"
                   << "namespace " << languageName << "\n"
                   << "{\n"
			       << MakeAstNodeForwardDeclarations(token)
                   << "    class AstTree_" << tokenName << MakeSubclassesForAstTree(token)
                   << "    {\n"
				   << "        private:\n"
                   << "        protected:\n"
                   << "        public:\n"
				   << MakeCtorFields(token)
                   << "            static AstTree_" << tokenName << "* currentTree;\n"
			       << "            const " << languageName << "::" << "AstEnum_t AstType = " << languageName << "::" << "AstEnum_t::" << *defaultTokenName << ";\n"
			       << "            AstTree_" << tokenName << "(bool isNode, std::string astNodeName);\n"
                   << "            AstTree_" << tokenName << "(std::vector<deamer::AstNode*> astNodes);\n"
                   << "            AstTree_" << tokenName << "(deamer::AstInformation* astInformation);\n"
				   << MakeAstTreeConstructorPrototypes(token)
                   << "            void Generate() override;\n"
                   << "            int GetAstId() override;\n"
                   << "            void SetCurrentTree(AstTree_" << tokenName << "* astTreePtr);\n"
                   << "    };\n"
                   << "}\n"
                   << "\n"
                   << "#endif //ASTNODES_" << tokenNameUpper << "_H\n";
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
