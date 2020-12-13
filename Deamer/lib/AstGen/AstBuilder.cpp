/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -August 2020 Thimo B�hmer
 */

#include "Deamer/AstGen/AstBuilder.h"

deamer::AstBuilder::AstBuilder(const std::string& directory, const std::string& language_name)
{
    Directory = directory;
    language_name_ = language_name;
}
