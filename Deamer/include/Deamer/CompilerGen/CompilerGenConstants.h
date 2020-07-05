/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_COMPILERGEN_COMPILERGENCONSTANT_H
#define DEAMER_COMPILERGEN_COMPILERGENCONSTANT_H



namespace deamer
{
    typedef enum CompiledOutputType_s
    {
        Instructional, // Instructional code is actual code that can be ran without a VM
        Behavioural, // Behavioural code is comparable with intepretered code using a VM
    } CompiledOutputType_t;
}

#endif //DEAMER_COMPILERGEN_COMPILERGENCONSTANT_H