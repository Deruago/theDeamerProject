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

#ifndef DEAMER_TOOL_TYPE_DLDLCONVERTER_LEXICON_LEXICON_H
#define DEAMER_TOOL_TYPE_DLDLCONVERTER_LEXICON_LEXICON_H

#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/Terminal.h"
#include "Deamer/Template/Tool/Type/DLDLConverter/Lexicon/LexiconTemplate.h"
#include "Deamer/Tool/Type/DLDLConverter/DLDLConverter.h"

namespace deamer::tool::type::dldlconverter::lexicon
{
	class Lexicon
	{
		using reference = DLDLConverter::reference;

	private:
		reference Reference;

	public:
		Lexicon(reference reference_);

	public:
		void Generate(::deamer::file::tool::Output& output);

	private:
		std::string GetAbstractionText(
			const language::type::definition::object::main::SpecialType& special) const;
	};
}

#endif // DEAMER_TOOL_TYPE_DLDLCONVERTER_LEXICON_LEXICON_H
