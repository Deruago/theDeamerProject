#ifndef DEAMER_COMPILERGEN_COMPILEDOBJECT_H
#define DEAMER_COMPILERGEN_COMPILEDOBJECT_H

#include "Deamer/CompilerGen/CompilerGenConstants.h"
#include <string>

namespace deamer
{
    class CompiledObject
    {
        private:
        protected:
        public:
            CompiledObject(CompiledOutputType_t compiledOutputType, std::string languageName);
            CompiledOutputType_t CompiledOutputType; // Defines the type of output
            std::string LanguageName; // Used to define which language it comes from
    };
}

#endif //DEAMER_COMPILERGEN_COMPILEDOBJECT_H