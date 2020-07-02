#ifndef DEAMER_COMPILERGEN_COMPILERGENCONSTANT_H
#define DEAMER_COMPILERGEN_COMPILERGENCONSTANT_H

typedef enum CompiledOutputType_s
{
    Instructional, // Instructional code is actual code that can be ran without a VM
    Behavioural, // Behavioural code is comparable with intepretered code using a VM
} CompiledOutputType_t;

#endif //DEAMER_COMPILERGEN_COMPILERGENCONSTANT_H