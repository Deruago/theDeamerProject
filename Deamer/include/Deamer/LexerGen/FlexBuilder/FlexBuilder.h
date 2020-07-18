/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_LEXERGEN_FLEXBUILDER_FLEXBUILDER_H
#define DEAMER_LEXERGEN_FLEXBUILDER_FLEXBUILDER_H

#include "Deamer/LexerGen/LexerBuilder.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"

namespace deamer
{
    class FlexBuilder : public LexerBuilder
    {
        private:
	        std::string declarationPart;
	        std::string regexDeclarationPart;
	        std::string tokenDeclarationPart;
	        std::string functionPart;
	    protected:
			virtual std::string NewNodeFunctionalData(Node* node) const;
        public:
            FlexBuilder();
            FlexBuilder(LanguageDefinition* langDef);
            void AddNode(Node* node) override;
            void AddIgnoreNode(Node* node) override;
            bool FinishBuild()  override;
            bool StartBuild() override;
    };
}

#endif //DEAMER_LEXERGEN_FLEXBUILDER_FLEXBUILDER_H
