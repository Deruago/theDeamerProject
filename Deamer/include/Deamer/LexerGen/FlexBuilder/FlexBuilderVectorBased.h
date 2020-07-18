/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -June 2020 Thimo B�hmer
 * -July 2020 Thimo B�hmer
 */

#ifndef DEAMER_LEXERGEN_FLEXBUILDER_FLEXBUILDERVECTORBASED_H
#define DEAMER_LEXERGEN_FLEXBUILDER_FLEXBUILDERVECTORBASED_H

#include "Deamer/LanguageGen/LanguageDefinition.h"
#include "Deamer/LexerGen/FlexBuilder/FlexBuilder.h"

namespace deamer
{
    class FlexBuilderVectorBased : public FlexBuilder
    {
	    protected:
		    //std::string NewNodeFunctionalData(Node* node) const override;
    public:
        FlexBuilderVectorBased(LanguageDefinition* langDef);
    };
}

#endif //DEAMER_LEXERGEN_FLEXBUILDER_FLEXBUILDERVECTORBASED_H
