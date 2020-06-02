#ifndef DEAMER_LANGUAGEGEN_NODE_H
#define DEAMER_LANGUAGEGEN_NODE_H

/*
This header describes the class implementation of Node. Which is a subclass of the Token class.
It represents an object that is the end point of rules or types.
*/

#include <string>
#include "Deamer/Deamer.h"
#include "Deamer/LanguageGen/Token.h"

using namespace Deamer;

class Node : public Token
{
    std::string Regex;
    
    public:
        Node(const std::string nodeName, const std::string regex);
};

#endif //DEAMER_LANGUAGEGEN_NODE_H