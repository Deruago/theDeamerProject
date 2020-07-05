/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -June 2020 Thimo B�hmer
 * -July 2020 Thimo B�hmer
 */

#ifndef DEAMER_LANGUAGEGEN_TOKENCONSTANTS_H
#define DEAMER_LANGUAGEGEN_TOKENCONSTANTS_H

/*
This header file is to declare the constants used by the Token class and relateable classes that use the Token class.
The constants are in enums.
*/

namespace deamer
{
    typedef enum Token_Constants_s
    {
        MAX_ALLOWED_TOKENS_IN_RULE = 64,
        MAX_ALLOWED_RULES_FOR_TYPE = 64
    } Token_Constants;
}

#endif //DEAMER_LANGUAGEGEN_TOKENCONSTANTS_H