/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
/*
 * Part of the DeamerProject.
 * For more information go to: https://github.com/Deruago/theDeamerProject
 */

#ifndef DEAMER_PARSER_TYPE_DPARSE_PARSERDEFINITIONRECURSIVEDESCENT_H
#define DEAMER_PARSER_TYPE_DPARSE_PARSERDEFINITIONRECURSIVEDESCENT_H

#include "Deamer/File/Tool/Data.h"
#include "Deamer/Language/Analyzer/Analyzer.h"
#include "Deamer/Parser/Generator/Dparse/Dparse.h"

namespace deamer::parser::type::dparse
{
	class ParserDefinitionRecursiveDescent : public file::tool::Data
	{
	public:
		// By default the parser will lookahead 4 terminals
		// However, with adaptive RD, it is possible to let the generator
		// Decide on lookahead, possibly further improving the efficiency
		// And parsing capabilities.
		static constexpr std::size_t fixedLookAhead = 4;

	private:
		const generator::dparse::Dparse::ReferenceType reference;
		const std::string name;

	public:
		ParserDefinitionRecursiveDescent(const generator::dparse::Dparse::ReferenceType reference_);
		virtual ~ParserDefinitionRecursiveDescent() override = default;

	public:
		std::string Generate() const override;
	};
}

#endif // DEAMER_PARSER_TYPE_DPARSE_PARSERDEFINITIONRECURSIVEDESCENT_H
