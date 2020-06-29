#ifndef DEAMER_ASTGEN_ASTINFORMATION_H
#define DEAMER_ASTGEN_ASTINFORMATION_H

typedef struct AstInformation_s
{
    unsigned int LineNumber;
    unsigned int CharNumber;
    char ValueName[2048];
} AstInformation;

#endif //DEAMER_ASTGEN_ASTINFORMATION_H