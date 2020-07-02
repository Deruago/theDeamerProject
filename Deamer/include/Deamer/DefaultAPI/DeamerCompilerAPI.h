#ifndef DEAMER_DEFAULTAPI_DEAMERCOMPILEAPI_H
#define DEAMER_DEFAULTAPI_DEAMERCOMPILEAPI_H

#include "Deamer/CompilerGen/CompiledObject.h"

class DeamerCompileAPI
{
    private:
    protected:
    public:
        DeamerCompileAPI();
        ~DeamerCompileAPI();
        virtual CompiledObject* CompileText(std::string inputText) = 0;
        virtual CompiledObject* CompileFile(FILE* inputFile) = 0;
        virtual CompiledObject* CompileFile(std::string fileLocation) = 0;
};

#endif //DEAMER_DEFAULTAPI_DEAMERCOMPILEAPI_H