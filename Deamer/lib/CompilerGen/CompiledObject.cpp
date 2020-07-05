/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/CompilerGen/CompiledObject.h"

deamer::CompiledObject::CompiledObject(CompiledOutputType_t compiledOutputType, std::string languageName)
{
    deamer::CompiledObject::CompiledOutputType = compiledOutputType;
    deamer::CompiledObject::LanguageName = languageName;
}