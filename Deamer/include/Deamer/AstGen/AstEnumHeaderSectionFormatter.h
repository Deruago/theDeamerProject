/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_ASTGEN_ASTENUMHEADERSECTIONFORMATTER_H
#define DEAMER_ASTGEN_ASTENUMHEADERSECTIONFORMATTER_H
#include <string>

/*
 Describes an AstTree. This is the top element of an AST.
 */

namespace deamer
{
	class Token;

	class AstEnumHeaderSectionFormatter
    {
    private:
        std::string directory_;
        std::string language_name_;

    public:
        AstEnumHeaderSectionFormatter(std::string directory, std::string language_name);

        void CreateAstNodeEnumFile() const;
        void AddToken(const Token& token) const;
        void FinishAstNodeEnumFile() const;
        void AddCodeToFile(const std::string& new_code) const;
    };
}

#endif //DEAMER_ASTGEN_ASTENUMHEADERSECTIONFORMATTER_H