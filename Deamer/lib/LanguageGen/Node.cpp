#include <string>
#include "Deamer/LanguageGen/Token.h"
#include "Deamer/LanguageGen/Node.h"

Node::Node(const std::string nodeName, const std::string regex, const bool createAst) : Token::Token(nodeName, true, createAst)
{
    Node::Regex = regex;
}

Node::Node(const std::string nodeName, const std::string regex) : Node::Node(nodeName, regex, true)
{
}