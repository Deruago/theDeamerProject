/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -June 2020 Thimo B�hmer
 * -July 2020 Thimo B�hmer
 */

#ifndef DEAMER_LANGUAGEGEN_NODE_H
#define DEAMER_LANGUAGEGEN_NODE_H

/*
This header describes the class implementation of Node. Which is a subclass of the Token class.
It represents an object that is the end point of rules or types.
*/

#include "Deamer/LanguageGen/Token.h"
#include <string>

namespace deamer
{
    class Node : public Token
    {
        
        public:
            std::string Regex;
            //Node(const std::string& nodeName, const std::string& regex);
            //Node(const std::string& nodeName, const std::string& regex, const bool createAst);
            Node(const std::string& typeName, const std::string& regex, const BitwiseEnum<TokenType_t> tokenType,
                const BitwiseEnum<TokenPermission_t> tokenPermission);
    };
}

#endif //DEAMER_LANGUAGEGEN_NODE_H