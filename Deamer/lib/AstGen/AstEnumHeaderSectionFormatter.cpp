/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#include "Deamer/AstGen/AstEnumHeaderSectionFormatter.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include <sstream>
#include <fstream>

deamer::AstEnumHeaderSectionFormatter::AstEnumHeaderSectionFormatter(std::string directory, std::string language_name)
{
    directory_ = directory;
    language_name_ = language_name;
}

void deamer::AstEnumHeaderSectionFormatter::CreateAstNodeEnumFile() const
{
    AddCodeToFile("#ifndef ASTNODES_ASTENUM_H\n"
		          "#define ASTNODES_ASTENUM_H\n"
		          "\n"
		          "namespace " + language_name_ + "\n"
		          "{\n"
		          "    typedef enum AstEnum_s\n"
		          "    {\n");
}

void deamer::AstEnumHeaderSectionFormatter::AddToken(const Token& token) const
{
    AddCodeToFile("        " + token.TokenName + ",\n");
}

void deamer::AstEnumHeaderSectionFormatter::FinishAstNodeEnumFile() const
{
    AddCodeToFile("    } AstEnum_t;\n"
		          "}\n"
		          "\n"
		          "#endif //ASTNODES_ASTENUM_H\n");
}

void deamer::AstEnumHeaderSectionFormatter::AddCodeToFile(const std::string& new_code) const
{
    std::ostringstream oss0;
    oss0 << directory_ << "AstEnum.h";
    std::ofstream newEnumFile;

    newEnumFile.open(oss0.str(), std::ios_base::app);

    newEnumFile << new_code;

    newEnumFile.close();

}