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

#ifndef DEAMER_ASTGEN_ASTNODE_H
#define DEAMER_ASTGEN_ASTNODE_H

/*
Defines an Abstract class for AstNodes. This will be used for creating new AstNodes and making sure
those Nodes has the neccessary details.
Each AstNode has an initialized AstInformation variable.
*/

#include "Deamer/AstGen/AstInformation.h"
#include <string>
#include <vector>


namespace deamer
{
    class AstNode
    {
        private:
            std::string CreateIndent(int indent);
        protected:
            std::vector<AstNode*> AstNodes;
            AstInformation* AstInfo = nullptr;
            std::string AstNodeName;
            bool IsNode;

            AstNode(bool isNode, std::string astNodeName);
            AstNode(std::vector<AstNode*> astNodes, bool isNode, std::string astNodeName); // Is used to initliase a basic AST node.
            AstNode(AstInformation* astInformation, bool isNode, std::string astNodeName); // Is used to initiliase AstEndPoints. (Only endpoints may use this constructor)
        public:
            //virtual void Generate() = 0; // This generates the source code.
            virtual unsigned int GetAstId() = 0;
            void PrintNode(int indent);
            void PrintDirectChildren(int indent);
            void PrintAllChildren();
            std::string GetValue() const;
    };
}

#endif //DEAMER_ASTGEN_ASTNODE_H
