/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#include "Deamer/AstGen/AstBuilder.h"
#include "Deamer/FileBuilder/Types/FileClassSection.h"
#include <utility>

deamer::AstBuilder::AstBuilder(const std::string& directory, const std::string& language_name)
{
    Directory = directory;
    language_name_ = language_name;
	
    _AstNode = new FileClassSection("AstNode");
    type_void = new FileClassSection("void");
    type_int = new FileClassSection("int");
    _AstNode->AddPublicMember("Generate", {}, type_void, true);
    _AstNode->AddPublicMember("GetAstId", {}, type_int, true);
}
