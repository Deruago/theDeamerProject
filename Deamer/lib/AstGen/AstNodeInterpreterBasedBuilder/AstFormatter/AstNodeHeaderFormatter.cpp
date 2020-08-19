/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -August 2020 Thimo B�hmer
 */

#include "Deamer/AstGen/AstNodeInterpreterBasedBuilder/AstFormatter/AstNodeHeaderFormatter.h"

deamer::AstNodeHeaderFormatter::AstNodeHeaderFormatter(Token* token, std::string language_name) : AstFileFormatter::AstFileFormatter(token, language_name)
{
}

std::string deamer::AstNodeHeaderFormatter::MakeAstFile() const
{
}
