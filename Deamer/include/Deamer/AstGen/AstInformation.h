/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -June 2020 Thimo B�hmer
 * -July 2020 Thimo B�hmer
 */

#ifndef DEAMER_ASTGEN_ASTINFORMATION_H
#define DEAMER_ASTGEN_ASTINFORMATION_H

namespace deamer
{
    typedef struct AstInformation_s
    {
        unsigned int LineNumber;
        unsigned int CharNumber;
        char ValueName[2048];
    } AstInformation;
}

#endif //DEAMER_ASTGEN_ASTINFORMATION_H