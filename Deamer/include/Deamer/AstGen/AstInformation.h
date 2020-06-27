#ifndef DEAMER_ASTGEN_ASTINFORMATION_H
#define DEAMER_ASTGEN_ASTINFORMATION_H

#include <string>

struct AstInformation
{
    public:
        unsigned int LineNumber;
        unsigned int CharNumber;
        std::string  ValueName;
};

#endif //DEAMER_ASTGEN_ASTINFORMATION_H