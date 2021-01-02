/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
 /*
  * Part of the DeamerProject.
  * For more information go to: https://github.com/Deruago/theDeamerProject
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
