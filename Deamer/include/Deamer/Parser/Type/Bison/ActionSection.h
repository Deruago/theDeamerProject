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

#ifndef DEAMER_PARSER_TYPE_BISON_ACTIONSECTION_H
#define DEAMER_PARSER_TYPE_BISON_ACTIONSECTION_H

#include "Deamer/File/Tool/Data.h"
#include "Deamer/Parser/Generator/Bison/Bison.h"

namespace deamer::parser::type::bison
{
	class ActionSection : public file::tool::Data
	{
	private:
		const generator::bison::Bison::ReferenceType reference;
		const std::string name;

	public:
		ActionSection(const generator::bison::Bison::ReferenceType reference_);
		virtual ~ActionSection() override = default;

	public:
		std::string Generate() const override;

	private:
		std::string LanguageError() const;
		std::string LanguageParser() const;
		std::string DebugMain() const;
	};
}

#endif // DEAMER_PARSER_TYPE_BISON_ACTIONSECTION_H
