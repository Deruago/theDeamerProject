#ifndef DEAMER_LEXERGEN_FLEXBUILDER_H
#define DEAMER_LEXERGEN_FLEXBUILDER_H

#include "Deamer/LexerGen/LexerBuilder.h"

class FlexBuilder : public LexerBuilder
{
    private:
    std::string declarationPart;
    std::string regexDeclarationPart;
    std::string tokenDeclarationPart;
    std::string functionPart;
    std::string NewNodeFunctionalData(Node* node);
    public:
        FlexBuilder();
        void AddNode(Node* node) override;
        bool FinishBuild()  override;
        bool StartBuild() override;
};

#endif //DEAMER_LEXERGEN_FLEXBUILDER_H