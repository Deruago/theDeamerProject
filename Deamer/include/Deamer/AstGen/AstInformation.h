#ifndef DEAMER_ASTGEN_ASTINFORMATION_H
#define DEAMER_ASTGEN_ASTINFORMATION_H

#include <string>

struct AstInformation
{
    public:
        unsigned int LineNumber;
        unsigned int CharNumber;
        const char ValueName[2048];
};

#endif //DEAMER_ASTGEN_ASTINFORMATION_H