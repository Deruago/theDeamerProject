/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#include "Deamer/AstGen/AstGlobalHeaderFormatter.h"
#include "Deamer/AstGen/AstNodeFormatter.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include <sstream>
#include <fstream>


deamer::AstGlobalHeaderFormatter::AstGlobalHeaderFormatter(const std::string& directory, const std::string& language_name)
{
    directory_ = directory;
    language_name_ = language_name;
}

void deamer::AstGlobalHeaderFormatter::CreateGlobalHeaderFile() const
{

    AddCodeToFile("#ifndef ASTNODES_ASTNODES_H\n"
                  "#define ASTNODES_ASTNODES_H\n"
                  "\n");
}

void deamer::AstGlobalHeaderFormatter::AddToken(const Token& token) const
{
    AddCodeToFile("#include \"./" + AstNodeFormatter().MakeClassName(&token) + ".h\"\n");
}

void deamer::AstGlobalHeaderFormatter::FinishGlobalHeaderFile() const
{
    AddCodeToFile("\n"
                  "#endif //ASTNODES_ASTNODES_H\n");
}

void deamer::AstGlobalHeaderFormatter::AddCodeToFile(const std::string& new_code) const
{
    std::ostringstream oss0;
    oss0 << directory_ << "AstNodes.h";
    std::ofstream globalHeaderFile;

    globalHeaderFile.open(oss0.str(), std::ios_base::app);

    globalHeaderFile << new_code;
	
    globalHeaderFile.close();
}