/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_LANGUAGEGEN_UNGROUPABLERULEEXCEPTION_H
#define DEAMER_LANGUAGEGEN_UNGROUPABLERULEEXCEPTION_H
#include <exception>

namespace deamer
{
	struct UngroupableRuleException : public std::exception
    {
        const char* what() const throw()
        {
            return "Tried to make a grouped rule from an ungroupable rule";
        }
    };
}

#endif //DEAMER_LANGUAGEGEN_UNGROUPABLERULEEXCEPTION_H