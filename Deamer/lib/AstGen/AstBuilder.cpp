/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/AstGen/AstBuilder.h"
#include <iostream>
#include <fstream>
#include <sstream>

deamer::AstBuilder::AstBuilder()
{
    deamer::AstBuilder::Directory = "";
}

void deamer::AstBuilder::FillAstSourceFile(std::ofstream* astSourceFile, std::string tokenName, std::string* defaultTokenName, bool isNode)
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

    *astSourceFile << "#include \"./" << tokenName << ".h\"\n"
             << "#include \"Deamer/AstGen/AstNode.h\"\n"
             << "#include \"Deamer/AstGen/AstInformation.h\"\n"
             << "#include <iostream>\n"
             << "#include <fstream>\n"
             << "#include <vector>\n"
             << '\n'
             << "int " << deamer::AstBuilder::languageName << "::" << tokenName << "::" << "GetAstId" << "()\n"
             << "{\n"
             << "    " << "return (unsigned int)" << deamer::AstBuilder::languageName << "::" << tokenName << "::AstType" << ";\n"
             << "}\n"
             << "\n"
             << deamer::AstBuilder::languageName << "::" << tokenName << "::" << tokenName << "(std::vector<deamer::AstNode*> astNodes) : deamer::AstNode::AstNode(astNodes, " <<  isNodeStr << ", \"" << *defaultTokenName << "\")\n"
             << "{\n"
             << "\n"
             << "}\n"
             << "\n"
             << deamer::AstBuilder::languageName << "::" << tokenName << "::" << tokenName << "(deamer::AstInformation* astInformation) : deamer::AstNode::AstNode(astInformation, " <<  isNodeStr << ", \"" << *defaultTokenName << "\")\n"
             << "{\n"
             << "\n"
             << "}\n"
             << "\n"
             << "void " << deamer::AstBuilder::languageName << "::" << tokenName << "::Generate()"
             << "{\n"
             << "\n"
             << "}\n";
}

void deamer::AstBuilder::FillAstHeaderFile(std::ofstream* astHeaderFile, std::string tokenName, std::string* defaultTokenName)
{
    std::string tokenNameUpper;
    for(int i = 0; i < tokenName.size(); i++)
    {
        tokenNameUpper += ::toupper(tokenName[i]);
    }

    *astHeaderFile << "#ifndef ASTNODES_" << tokenNameUpper << "_H\n"
                   << "#define ASTNODES_" << tokenNameUpper << "_H\n"
                   << "\n"
                   << "#include \"Deamer/AstGen/AstNode.h\"\n"
                   << "#include \"Deamer/AstGen/AstInformation.h\"\n"
                   << "#include \"AstEnum.h\"\n"
                   << "#include <vector>\n"
                   << "\n"
                   << "namespace " << deamer::AstBuilder::languageName << "\n"
                   << "{\n"
                   << "    class " << tokenName << " : public deamer::AstNode\n"
                   << "    {\n"
                   << "        private:\n"
                   << "        protected:\n"
                   << "        public:\n"
                   << "            const " << deamer::AstBuilder::languageName << "::AstEnum_t AstType = " << deamer::AstBuilder::languageName << "::AstEnum_t::" << *defaultTokenName << ";\n"
                   << "            " << tokenName << "(std::vector<deamer::AstNode*> astNodes);\n"
                   << "            " << tokenName << "(deamer::AstInformation* astInformation);\n"
                   << "            void Generate() override;\n"
                   << "            int GetAstId() override;\n"
                   << "    };\n"
                   << "}\n"
                   << "\n"
                   << "#endif //ASTNODES_" << tokenNameUpper << "_H\n";
}

void deamer::AstBuilder::FillAstTreeSourceFile(std::ofstream* astSourceFile, std::string tokenName, std::string* defaultTokenName, bool isNode)
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

    *astSourceFile << "#include \"./" << tokenName << ".h\"\n"
             << "#include \"Deamer/AstGen/AstTree.h\"\n"
             << "#include \"Deamer/AstGen/AstNode.h\"\n"
             << "#include \"Deamer/AstGen/AstInformation.h\"\n"
             << "#include <iostream>\n"
             << "#include <fstream>\n"
             << "#include <vector>\n"
             << '\n'
             << deamer::AstBuilder::languageName << "::" << "AstTree_" << *defaultTokenName << "* " << deamer::AstBuilder::languageName << "::" << tokenName << "::currentTree;\n"
             << '\n'
             << "int " << deamer::AstBuilder::languageName << "::" << tokenName << "::" << "GetAstId" << "()\n"
             << "{\n"
             << "    " << "return (unsigned int)" << deamer::AstBuilder::languageName << "::" << tokenName << "::AstType" << ";\n"
             << "}\n"
             << "\n"
             << deamer::AstBuilder::languageName << "::" << tokenName << "::" << tokenName << "(std::vector<deamer::AstNode*> astNodes) : deamer::AstNode::AstNode(astNodes, " <<  isNodeStr << ", \"" << *defaultTokenName << "\")\n"
             << "{\n"
             << "\n"
             << "}\n"
             << "\n"
             << deamer::AstBuilder::languageName << "::" << tokenName << "::" << tokenName << "(deamer::AstInformation* astInformation) : deamer::AstNode::AstNode(astInformation, " <<  isNodeStr << ", \"" << *defaultTokenName << "\")\n"
             << "{\n"
             << "\n"
             << "}\n"
             << "\n"
             << "void " << deamer::AstBuilder::languageName << "::" << tokenName << "::SetCurrentTree(" << tokenName << "* astTreePtr)\n"
             << "{\n"
             << "    " << deamer::AstBuilder::languageName << "::" << tokenName << "::currentTree = astTreePtr;\n"
             << "}\n"
             << "\n"
             << "void " << deamer::AstBuilder::languageName << "::" << tokenName << "::Generate()\n"
             << "{\n"
             << "\n"
             << "}\n";
}

void deamer::AstBuilder::FillAstTreeHeaderFile(std::ofstream* astHeaderFile, std::string tokenName, std::string* defaultTokenName)
{
    std::string tokenNameUpper;
    for(int i = 0; i < tokenName.size(); i++)
    {
        tokenNameUpper += ::toupper(tokenName[i]);
    }

    *astHeaderFile << "#ifndef ASTNODES_" << tokenNameUpper << "_H\n"
                   << "#define ASTNODES_" << tokenNameUpper << "_H\n"
                   << "\n"
                   << "#include \"Deamer/AstGen/AstTree.h\"\n"
                   << "#include \"Deamer/AstGen/AstNode.h\"\n"
                   << "#include \"Deamer/AstGen/AstInformation.h\"\n"
                   << "#include \"AstEnum.h\"\n"
                   << "#include <string>\n"
                   << "#include <vector>\n"
                   << "\n"
                   << "namespace " << deamer::AstBuilder::languageName << "\n"
                   << "{\n"
                   << "    class " << tokenName << " : public deamer::AstNode, public deamer::AstTree\n"
                   << "    {\n"
                   << "        private:\n"
                   << "        protected:\n"
                   << "        public:\n"
                   << "            static " << tokenName << "* currentTree;\n"
                   << "            const " << deamer::AstBuilder::languageName << "::" << "AstEnum_t AstType = " << deamer::AstBuilder::languageName << "::" << "AstEnum_t::" << *defaultTokenName << ";\n"
                   << "            " << tokenName << "(std::vector<deamer::AstNode*> astNodes);\n"
                   << "            " << tokenName << "(deamer::AstInformation* astInformation);\n"
                   << "            void Generate() override;\n"
                   << "            int GetAstId() override;\n"
                   << "            void SetCurrentTree(" << tokenName << "* astTreePtr);\n"
                   << "    };\n"
                   << "}\n"
                   << "\n"
                   << "#endif //ASTNODES_" << tokenNameUpper << "_H\n";
}

void deamer::AstBuilder::CreateAstNode(std::string TokenName, bool isNode)
{
    std::string DefaultTokenName = TokenName;
    std::ostringstream oss0;
    oss0 << "AstNode_" << TokenName;
    TokenName = oss0.str();

    std::ostringstream oss;
    oss << deamer::AstBuilder::Directory << TokenName << ".cpp";
    std::ofstream newAstNodeSourceFile(oss.str());

    deamer::AstBuilder::FillAstSourceFile(&newAstNodeSourceFile, TokenName, &DefaultTokenName, isNode);
    
    newAstNodeSourceFile.close();

    std::ostringstream oss2;
    oss2 << deamer::AstBuilder::Directory << TokenName << ".h";
    std::ofstream newAstNodeHeaderFile(oss2.str());

    deamer::AstBuilder::FillAstHeaderFile(&newAstNodeHeaderFile, TokenName, &DefaultTokenName);

    newAstNodeHeaderFile.close();
}

void deamer::AstBuilder::CreateAstTree(std::string TokenName, bool isNode)
{
    std::string DefaultTokenName = TokenName;
    std::ostringstream oss0;
    oss0 << "AstTree_" << TokenName;
    TokenName = oss0.str();

    std::ostringstream oss;
    oss << deamer::AstBuilder::Directory << TokenName << ".cpp";
    std::ofstream newAstTreeSourceFile(oss.str());

    deamer::AstBuilder::FillAstTreeSourceFile(&newAstTreeSourceFile, TokenName, &DefaultTokenName, isNode);
    
    newAstTreeSourceFile.close();

    std::ostringstream oss2;
    oss2 << deamer::AstBuilder::Directory << TokenName << ".h";
    std::ofstream newAstTreeHeaderFile(oss2.str());

    deamer::AstBuilder::FillAstTreeHeaderFile(&newAstTreeHeaderFile, TokenName, &DefaultTokenName);

    newAstTreeHeaderFile.close();
}

void deamer::AstBuilder::CreateGlobalHeaderFile()
{
    std::ostringstream oss0;
    oss0 << deamer::AstBuilder::Directory << "AstNodes.h";
    std::ofstream newGlobalHeaderFile(oss0.str());

    newGlobalHeaderFile << "#ifndef ASTNODES_ASTNODES_H\n"
                        << "#define ASTNODES_ASTNODES_H\n"
                        << "\n";
    
    newGlobalHeaderFile.close();
}

void deamer::AstBuilder::AppendAstNodeHeaderFile(std::string TokenName)
{
    std::ostringstream oss0;
    oss0 << deamer::AstBuilder::Directory << "AstNodes.h";
    std::ofstream globalHeaderFile;

    globalHeaderFile.open(oss0.str(), std::ios_base::app);

    globalHeaderFile << "#include \"" << "./" << "AstNode_" << TokenName << ".h\"\n";

    globalHeaderFile.close();
}

void deamer::AstBuilder::AppendAstTreeHeaderFile(std::string TokenName)
{
    std::ostringstream oss0;
    oss0 << deamer::AstBuilder::Directory << "AstNodes.h";
    std::ofstream globalHeaderFile;

    globalHeaderFile.open(oss0.str(), std::ios_base::app);

    globalHeaderFile << "#include \"" << "./" << "AstTree_" << TokenName << ".h\"\n";

    globalHeaderFile.close();
}

void deamer::AstBuilder::FinishGlobalHeaderFile()
{
    std::ostringstream oss0;
    oss0 << deamer::AstBuilder::Directory << "AstNodes.h";
    std::ofstream globalHeaderFile;

    globalHeaderFile.open(oss0.str(), std::ios_base::app);

    globalHeaderFile << "\n"
                     << "#endif //ASTNODES_ASTNODES_H\n";

    globalHeaderFile.close();
}

void deamer::AstBuilder::CreateAstNodeEnumFile()
{
    std::ostringstream oss0;
    oss0 << deamer::AstBuilder::Directory << "AstEnum.h";
    std::ofstream newEnumFile(oss0.str());

    newEnumFile << "#ifndef ASTNODES_ASTENUM_H\n"
                << "#define ASTNODES_ASTENUM_H\n"
                << "\n"
                << "namespace " << deamer::AstBuilder::languageName << "\n"
                << "{\n"
                << "    typedef enum AstEnum_s\n"
                << "    {\n";
    
    newEnumFile.close();
}

void deamer::AstBuilder::AppendAstNodeEnumFile(std::string TokenName)
{
    std::ostringstream oss0;
    oss0 << deamer::AstBuilder::Directory << "AstEnum.h";
    std::ofstream newEnumFile;

    newEnumFile.open(oss0.str(), std::ios_base::app);

    newEnumFile << "        " << TokenName << ",\n";

    newEnumFile.close();
}

void deamer::AstBuilder::FinishAstNodeEnumFile()
{
    std::ostringstream oss0;
    oss0 << deamer::AstBuilder::Directory << "AstEnum.h";
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
    deamer::AstBuilder::languageName = languageName;
}