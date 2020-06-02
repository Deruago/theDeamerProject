#ifndef DEAMER_PARSERGEN_PARSERBUILDER_H
#define DEAMER_PARSERGEN_PARSERBUILDER_H

#include <vector>
#include "Deamer/LanguageGen/Node.h"
#include "Deamer/LanguageGen/Type.h"
#include "Deamer/LanguageGen/Rule.h"

class ParserBuilder
{
    ParserType_t parserType;
    std::vector<Node*> Nodes;
    std::vector<Type*> Types;
    std::vector<Rule*> Rules;
    public:
        ParserBuilder();
        ParserBuilder(ParserType_t parserTarget);
};

#endif //DEAMER_PARSERGEN_PARSERBUILDER_H