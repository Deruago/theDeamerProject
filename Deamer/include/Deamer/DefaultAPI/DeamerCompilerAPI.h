/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_DEFAULTAPI_DEAMERCOMPILEAPI_H
#define DEAMER_DEFAULTAPI_DEAMERCOMPILEAPI_H

#include "Deamer/CompilerGen/CompiledObject.h"

namespace deamer
{
    class DeamerCompilerAPI
    {
        private:
        protected:
        public:
            DeamerCompilerAPI();
            ~DeamerCompilerAPI();
            virtual CompiledObject* CompileText(std::string inputText) = 0;
            virtual CompiledObject* CompileFile(FILE* inputFile) = 0;
            virtual CompiledObject* CompileFile(std::string fileLocation) = 0;
    };
}

#endif //DEAMER_DEFAULTAPI_DEAMERCOMPILEAPI_H