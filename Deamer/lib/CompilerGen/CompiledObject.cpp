#include "Deamer/CompilerGen/CompiledObject.h"

deamer::CompiledObject::CompiledObject(CompiledOutputType_t compiledOutputType, std::string languageName)
{
    deamer::CompiledObject::CompiledOutputType = compiledOutputType;
    deamer::CompiledObject::LanguageName = languageName;
}