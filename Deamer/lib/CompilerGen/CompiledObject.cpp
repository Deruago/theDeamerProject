#include "Deamer/CompilerGen/CompiledObject.h"

CompiledObject::CompiledObject(CompiledOutputType_t compiledOutputType, std::string languageName)
{
    CompiledObject::CompiledOutputType = compiledOutputType;
    CompiledObject::LanguageName = languageName;
}