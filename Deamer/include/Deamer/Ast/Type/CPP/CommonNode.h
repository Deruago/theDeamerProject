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

#ifndef DEAMER_AST_TYPE_CPP_COMMONNODE_H
#define DEAMER_AST_TYPE_CPP_COMMONNODE_H

#include "Deamer/File/Tool/File.h"
#include "Deamer/Language/Reference/LDO.h"
#include "Deamer/Language/Reference/PropertyDefinition.h"

namespace deamer::ast::type::cpp
{
	/*!	\class CommonNode
	 *
	 *	\brief Generates an AST/CST common node file.
	 *	This file contains the template specialization for the given node.
	 */
	class CommonNode
	{
	private:
		using ReferenceType = language::reference::PropertyDefinition<
			language::type::definition::property::Type::Lexicon,
			language::type::definition::property::Type::Grammar>;

		ReferenceType reference;

		language::reference::LDO<language::type::definition::object::main::NonTerminal> nonTerminal;

		std::string languageName;

	public:
		CommonNode(ReferenceType reference_,
				   language::reference::LDO<language::type::definition::object::main::NonTerminal>
					   nonTerminal_);
		~CommonNode() = default;

	public:
		deamer::file::tool::File Generate() const;
	};
}

#endif // DEAMER_AST_TYPE_CPP_COMMONNODE_H
