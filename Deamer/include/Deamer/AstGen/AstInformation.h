#ifndef DEAMER_ASTGEN_ASTINFORMATION_H
#define DEAMER_ASTGEN_ASTINFORMATION_H

#include <string>

struct AstInformation
{
    public:
        unsigned int LineNumber;
        unsigned int CharNumber;
        std::string  ValueName;
        AstInformation(unsigned int lineNumber, unsigned int charNumber, std::string valueName);
};

#endif //DEAMER_ASTGEN_ASTINFORMATION_H