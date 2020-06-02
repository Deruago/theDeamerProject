#include <string>
#include "Deamer/LanguageGen/Token.h"
#include "Deamer/LanguageGen/Node.h"


Node::Node(const std::string nodeName, const std::string regex) : Token::Token(nodeName, true)
{
    Node::Regex = regex;
}