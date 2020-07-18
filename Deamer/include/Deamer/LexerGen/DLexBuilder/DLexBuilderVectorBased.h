/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -June 2020 Thimo B�hmer
 * -July 2020 Thimo B�hmer
 */

#ifndef DEAMER_LEXERGEN_DLEXBUILDER_DLEXBUILDERVECTORBASED_H
#define DEAMER_LEXERGEN_DLEXBUILDER_DLEXBUILDERVECTORBASED_H

#include "Deamer/LanguageGen/LanguageDefinition.h"
#include "Deamer/LexerGen/DLexBuilder/DLexBuilder.h"

namespace deamer
{
    class DlexBuilderVectorBased : public DlexBuilder
    {
    public:
        DlexBuilderVectorBased(LanguageDefinition* langDef);
    };
}

#endif //DEAMER_LEXERGEN_DLEXBUILDER_DLEXBUILDERVECTORBASED_H
