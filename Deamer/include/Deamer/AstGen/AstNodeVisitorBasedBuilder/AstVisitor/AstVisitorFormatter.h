/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_ASTGEN_ASTNODEVISITORBASEDBUILDER_ASTVISITOR_ASTVISITORFORMATTER_H
#define DEAMER_ASTGEN_ASTNODEVISITORBASEDBUILDER_ASTVISITOR_ASTVISITORFORMATTER_H
#include <string>

namespace deamer
{
	namespace AstVisitorBuilder
	{
		class AstVisitorFormatter
		{
		public:
			AstVisitorFormatter() = default;
			void WriteOutputToFile(const std::string& file_path_location, const std::string& file_content) const;
		};
	}
}

#endif //DEAMER_ASTGEN_ASTNODEVISITORBASEDBUILDER_ASTVISITOR_ASTVISITORFORMATTER_H