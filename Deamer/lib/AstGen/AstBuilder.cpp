#include "Deamer/AstGen/AstBuilder.h"
#include <iostream>
#include <fstream>
#include <sstream>

AstBuilder::AstBuilder()
{
    AstBuilder::Directory = "";
}

void AstBuilder::FillAstSourceFile(std::ofstream* astSourceFile, std::string tokenName)
{
    *astSourceFile << "#include \"./" << tokenName << ".h\"\n"
             << "#include \"Deamer/AstGen/AstNode.h\"\n"
             << "#include \"Deamer/AstGen/AstInformation.h\"\n"
             << "#include <iostream>\n"
             << "#include <fstream>\n"
             << "#include <vector>\n"
             << '\n'
             << tokenName << "::" << tokenName << "(std::vector<AstNode*> astNodes) : AstNode::AstNode(astNodes)\n"
             << "{\n"
             << "\n"
             << "}\n"
             << "\n"
             << tokenName << "::" << tokenName << "(AstInformation* astInformation) : AstNode::AstNode(astInformation)\n"
             << "{\n"
             << "\n"
             << "}\n"
             << "\n"
             << "void " << tokenName << "::Generate()"
             << "{\n"
             << "\n"
             << "}\n";
}

void AstBuilder::FillAstHeaderFile(std::ofstream* astHeaderFile, std::string tokenName, std::string* defaultTokenName)
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
                   << "class " << tokenName << " : public AstNode\n"
                   << "{\n"
                   << "    private:\n"
                   << "    protected:\n"
                   << "    public:\n"
                   << "        const AstEnum_t AstType = AstEnum_t::" << *defaultTokenName << ";\n"
                   << "        " << tokenName << "(std::vector<AstNode*> astNodes);\n"
                   << "        " << tokenName << "(AstInformation* astInformation);\n"
                   << "        virtual void Generate() override;\n"
                   << "};\n"
                   << "\n"
                   << "#endif //ASTNODES_" << tokenNameUpper << "_H\n";
}

void AstBuilder::FillAstTreeSourceFile(std::ofstream* astSourceFile, std::string tokenName)
{
    *astSourceFile << "#include \"./" << tokenName << ".h\"\n"
             << "#include \"Deamer/AstGen/AstTree.h\"\n"
             << "#include \"Deamer/AstGen/AstNode.h\"\n"
             << "#include \"Deamer/AstGen/AstInformation.h\"\n"
             << "#include <iostream>\n"
             << "#include <fstream>\n"
             << "#include <vector>\n"
             << '\n'
             << tokenName << "::" << tokenName << "(std::vector<AstNode*> astNodes) : AstNode::AstNode(astNodes)\n"
             << "{\n"
             << "\n"
             << "}\n"
             << "\n"
             << tokenName << "::" << tokenName << "(AstInformation* astInformation) : AstNode::AstNode(astInformation)\n"
             << "{\n"
             << "\n"
             << "}\n"
             << "\n"
             << "void " << tokenName << "::Generate()"
             << "{\n"
             << "\n"
             << "}\n";
}

void AstBuilder::FillAstTreeHeaderFile(std::ofstream* astHeaderFile, std::string tokenName, std::string* defaultTokenName)
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
                   << "#include <vector>\n"
                   << "\n"
                   << "class " << tokenName << " : public AstNode, public AstTree\n"
                   << "{\n"
                   << "    private:\n"
                   << "    protected:\n"
                   << "    public:\n"
                   << "        const AstEnum_t AstType = AstEnum_t::" << *defaultTokenName << ";\n"
                   << "        " << tokenName << "(std::vector<AstNode*> astNodes);\n"
                   << "        " << tokenName << "(AstInformation* astInformation);\n"
                   << "        virtual void Generate() override;\n"
                   << "};\n"
                   << "\n"
                   << "#endif //ASTNODES_" << tokenNameUpper << "_H\n";
}

void AstBuilder::CreateAstNode(std::string TokenName)
{
    std::string DefaultTokenName = TokenName;
    std::ostringstream oss0;
    oss0 << "AstNode_" << TokenName;
    TokenName = oss0.str();

    std::ostringstream oss;
    oss << AstBuilder::Directory << TokenName << ".cpp";
    std::ofstream newAstNodeSourceFile(oss.str());

    AstBuilder::FillAstSourceFile(&newAstNodeSourceFile, TokenName);
    
    newAstNodeSourceFile.close();

    std::ostringstream oss2;
    oss2 << AstBuilder::Directory << TokenName << ".h";
    std::ofstream newAstNodeHeaderFile(oss2.str());

    AstBuilder::FillAstHeaderFile(&newAstNodeHeaderFile, TokenName, &DefaultTokenName);

    newAstNodeHeaderFile.close();
}

void AstBuilder::CreateAstTree(std::string TokenName)
{
    std::string DefaultTokenName = TokenName;
    std::ostringstream oss0;
    oss0 << "AstTree_" << TokenName;
    TokenName = oss0.str();

    std::ostringstream oss;
    oss << AstBuilder::Directory << TokenName << ".cpp";
    std::ofstream newAstTreeSourceFile(oss.str());

    AstBuilder::FillAstTreeSourceFile(&newAstTreeSourceFile, TokenName);
    
    newAstTreeSourceFile.close();

    std::ostringstream oss2;
    oss2 << AstBuilder::Directory << TokenName << ".h";
    std::ofstream newAstTreeHeaderFile(oss2.str());

    AstBuilder::FillAstTreeHeaderFile(&newAstTreeHeaderFile, TokenName, &DefaultTokenName);

    newAstTreeHeaderFile.close();
}

void AstBuilder::CreateGlobalHeaderFile()
{
    std::ostringstream oss0;
    oss0 << AstBuilder::Directory << "AstNodes.h";
    std::ofstream newGlobalHeaderFile(oss0.str());

    newGlobalHeaderFile << "#ifndef ASTNODES_ASTNODES_H\n"
                        << "#define ASTNODES_ASTNODES_H\n"
                        << "\n";
    
    newGlobalHeaderFile.close();
}

void AstBuilder::AppendAstNodeHeaderFile(std::string TokenName)
{
    std::ostringstream oss0;
    oss0 << AstBuilder::Directory << "AstNodes.h";
    std::ofstream globalHeaderFile;

    globalHeaderFile.open(oss0.str(), std::ios_base::app);

    globalHeaderFile << "#include \"" << AstBuilder::Directory << "AstNode_" << TokenName << ".h\"\n";

    globalHeaderFile.close();
}

void AstBuilder::AppendAstTreeHeaderFile(std::string TokenName)
{
    std::ostringstream oss0;
    oss0 << AstBuilder::Directory << "AstNodes.h";
    std::ofstream globalHeaderFile;

    globalHeaderFile.open(oss0.str(), std::ios_base::app);

    globalHeaderFile << "#include \"" << AstBuilder::Directory << "AstTree_" << TokenName << ".h\"\n";

    globalHeaderFile.close();
}

void AstBuilder::FinishGlobalHeaderFile()
{
    std::ostringstream oss0;
    oss0 << AstBuilder::Directory << "AstNodes.h";
    std::ofstream globalHeaderFile;

    globalHeaderFile.open(oss0.str(), std::ios_base::app);

    globalHeaderFile << "\n"
                     << "#endif //ASTNODES_ASTNODES_H\n";

    globalHeaderFile.close();
}

void AstBuilder::CreateAstNodeEnumFile()
{
    std::ostringstream oss0;
    oss0 << AstBuilder::Directory << "AstEnum.h";
    std::ofstream newEnumFile(oss0.str());

    newEnumFile << "#ifndef ASTNODES_ASTENUM_H\n"
                << "#define ASTNODES_ASTENUM_H\n"
                << "\n"
                << "typedef enum AstEnum_s\n"
                << "{\n";
    
    newEnumFile.close();
}

void AstBuilder::AppendAstNodeEnumFile(std::string TokenName)
{
    std::ostringstream oss0;
    oss0 << AstBuilder::Directory << "AstEnum.h";
    std::ofstream newEnumFile;

    newEnumFile.open(oss0.str(), std::ios_base::app);

    newEnumFile << "    " << TokenName << ",\n";

    newEnumFile.close();
}

void AstBuilder::FinishAstNodeEnumFile()
{
    std::ostringstream oss0;
    oss0 << AstBuilder::Directory << "AstEnum.h";
    std::ofstream newEnumFile;

    newEnumFile.open(oss0.str(), std::ios_base::app);

    newEnumFile << "} AstEnum_t;\n"
                << "\n"
                << "#endif //ASTNODES_ASTENUM_H\n";

    newEnumFile.close();
}
