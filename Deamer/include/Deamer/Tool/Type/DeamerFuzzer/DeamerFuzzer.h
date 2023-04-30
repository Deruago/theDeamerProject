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

#ifndef DEAMER_TOOL_DEAMERFUZZER_DEAMERFUZZER_H
#define DEAMER_TOOL_DEAMERFUZZER_DEAMERFUZZER_H

#include "Deamer/Language/Reference/LDO.h"
#include "Deamer/Language/Reference/PropertyDefinition.h"
#include "Deamer/Tool/Type/Base.h"

namespace deamer::tool::type::deamerfuzzer
{
	/*!	\class DeamerFuzzer
	 *
	 *	\brief Uses the LD to generate a fuzzer.
	 */
	class DeamerFuzzer : public ::deamer::tool::type::Base
	{
	public:
		using reference = language::reference::PropertyDefinition<
			language::type::definition::property::Type::Lexicon,
			language::type::definition::property::Type::Grammar,
			language::type::definition::property::Type::Precedence,
			language::type::definition::property::Type::Associativity>;

	private:
		reference Reference;

	public:
		DeamerFuzzer(reference reference_);

	public:
		deamer::file::tool::Output Generate() override;
	};
}

#endif // DEAMER_TOOL_DEAMERFUZZER_DEAMERFUZZER_H
