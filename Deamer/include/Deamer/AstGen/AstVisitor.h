/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_ASTGEN_ASTVISITOR_H
#define DEAMER_ASTGEN_ASTVISITOR_H
#include "AstNode.h"

/*
  * This is the base AstVisitor. It uses 1 virtual function that accepts an AstNode.
  * This virtual function should be overriden by subclasses to integrate their own specific functionality.
 */

namespace deamer
{
	class AstVisitor
    {
    public:
        AstVisitor() = default;
        virtual void Dispatch(AstNode& astnode);
    };
}

#endif //DEAMER_ASTGEN_ASTVISITOR_H
