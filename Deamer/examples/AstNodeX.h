#ifndef ASTNODES_ASTNODEX_H
#define ASTNODES_ASTNODEX_H

#include "Deamer/AstGen/AstNode.h"

class AstNodeX : AstNode
{
    private:
    protected:
    public:
        AstNodeX(std::vector<AstNode*> astNodes);
        AstNodeX(AstInformation* astInformation);
        virtual void Generate() override;
};

#endif //ASTNODES_ASTNODEX_H