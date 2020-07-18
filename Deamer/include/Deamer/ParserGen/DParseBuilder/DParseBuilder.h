/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_PARSERGEN_DPARSEBUILDER_H
#define DEAMER_PARSERGEN_DPARSEBUILDER_H

#include "Deamer/ParserGen/ParserBuilder.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"

namespace deamer
{
    class DParseBuilder : public ParserBuilder
    {
        public:
            DParseBuilder(LanguageDefinition* langDef);
            void AddNode(Node* node) override;
            void AddType(Type* type) override;
            void AddRule(Rule* rule) override;
            bool FinishBuild() override;
            bool StartBuild() override;
            
    };
}

#endif //DEAMER_PARSERGEN_DPARSEBUILDER_H