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

#ifndef DEAMER_PARSER_TYPE_BISON_PRECEDENCESCTION_H
#define DEAMER_PARSER_TYPE_BISON_PRECEDENCESCTION_H

#include "Deamer/File/Tool/Data.h"
#include "Deamer/Language/Reference/LDO.h"
#include "Deamer/Parser/Generator/Bison/Bison.h"

namespace deamer::parser::type::bison
{
	class PrecedenceSection : public file::tool::Data
	{
	private:
		const generator::bison::Bison::ReferenceType reference;
		std::vector<std::pair<
			int, language::reference::LDO<language::type::definition::object::main::Terminal>>>
			terminals;

	public:
		PrecedenceSection(const generator::bison::Bison::ReferenceType reference_);
		virtual ~PrecedenceSection() override = default;

		void AddTerminal(
			language::reference::LDO<language::type::definition::object::main::Terminal> terminal);

	public:
		std::string Generate() const override;
	};
}
#endif // DEAMER_PARSER_TYPE_BISON_PRECEDENCESCTION_H
