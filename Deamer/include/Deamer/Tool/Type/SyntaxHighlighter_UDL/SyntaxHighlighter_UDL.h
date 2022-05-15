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

#ifndef DEAMER_TOOL_TYPE_SYNTAXHIGHLIGHTERUDL_SYNTAXHIGHLIGHTERUDL_H
#define DEAMER_TOOL_TYPE_SYNTAXHIGHLIGHTERUDL_SYNTAXHIGHLIGHTERUDL_H

#include "Deamer/Language/Reference/LDO.h"
#include "Deamer/Language/Reference/PropertyDefinition.h"
#include "Deamer/Language/Reference/ReverseLookup.h"
#include "Deamer/Tool/Type/Base.h"

namespace deamer::tool::type::syntaxhighlighter_udl
{
	/*! \class UDL
	 *
	 *	\brief Creates a syntax highlighter in UDL.
	 *
	 *	\details UDL is used by editors such as notepad++
	 *
	 *	\note As UDL doesn't support regex, every terminal containing some regex is rejected.
	 *	It also doesn't support patterns.
	 *
	 */
	class SyntaxHighlighter_UDL : ::deamer::tool::type::Base
	{
	private:
		using reference = language::reference::PropertyDefinition<
			language::type::definition::property::Type::Lexicon,
			language::type::definition::property::Type::Grammar,
			language::type::definition::property::Type::Colorization>;

	private:
		reference Reference;

	public:
		SyntaxHighlighter_UDL(reference reference_);

		deamer::file::tool::Output Generate() override;
	};
}

#endif // DEAMER_TOOL_TYPE_SYNTAXHIGHLIGHTERUDL_SYNTAXHIGHLIGHTERUDL_H
