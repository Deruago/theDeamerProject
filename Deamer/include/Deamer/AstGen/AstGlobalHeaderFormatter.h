/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -August 2020 Thimo B�hmer
 */

#ifndef DEAMER_ASTGEN_ASTGLOBALHEADERFORMATTER_H
#define DEAMER_ASTGEN_ASTGLOBALHEADERFORMATTER_H
#include <string>

/*
 Describes an AstTree. This is the top element of an AST.
 */

namespace deamer
{
	class Token;

	class AstGlobalHeaderFormatter
    {
    private:
        std::string directory_;
        std::string language_name_;
    	
    public:
        AstGlobalHeaderFormatter(const std::string& directory, const std::string& language_name);

    	void CreateGlobalHeaderFile() const;
        void AddToken(const Token& token) const;
        void FinishGlobalHeaderFile() const;
        void AddCodeToFile(const std::string& new_code) const;
    };
}

#endif //DEAMER_ASTGEN_ASTGLOBALHEADERFORMATTER_H