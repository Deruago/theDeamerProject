#include <string>
#include "Deamer/LanguageGen/Token.h"
#include "Deamer/LanguageGen/Node.h"

deamer::Node::Node(const std::string nodeName, const std::string regex, const bool createAst) : deamer::Token::Token(nodeName, true, createAst)
{
    deamer::Node::Regex = regex;
}

deamer::Node::Node(const std::string nodeName, const std::string regex) : deamer::Node::Node(nodeName, regex, true)
{
}