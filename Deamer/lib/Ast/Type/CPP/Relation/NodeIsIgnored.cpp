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

#include "Deamer/Ast/Type/CPP/Relation/NodeIsIgnored.h"
#include "Deamer/Template/Ast/Type/CPP/Relation/NodeIsIgnored/NodeIsIgnoredTemplate.h"

deamer::ast::type::cpp::NodeIsIgnored::NodeIsIgnored(ReferenceType reference_)
	: reference(reference_),
	  languageName(reference_.GetDefinition<language::type::definition::property::Type::Identity>()
					   .GetName()
					   ->value)
{
	nodeIsDeletedTemplate = new ::deamer::templates::ast::type::cpp::NodeIsIgnoredTemplate();
}

deamer::ast::type::cpp::NodeIsIgnored::~NodeIsIgnored()
{
	delete nodeIsDeletedTemplate;
}

deamer::file::tool::File deamer::ast::type::cpp::NodeIsIgnored::Generate() const
{
	deamer::file::tool::File nodeIsTerminal("NodeIsIgnored", "h");

	nodeIsDeletedTemplate->language_name_->Set(languageName);

	for (const auto* const terminal :
		 reference.GetDefinition<language::type::definition::property::Type::Lexicon>().Terminals)
	{
		nodeIsDeletedTemplate->node_name_->Set(terminal->Name);
		if (terminal->Special == language::type::definition::object::main::SpecialType::Ignore)
		{
			nodeIsDeletedTemplate->is_deleted_->Set("true");
		}
		else
		{
			nodeIsDeletedTemplate->is_deleted_->Set("false");
		}

		nodeIsDeletedTemplate->node_conversion_->ExpandVariableField();
	}

	nodeIsTerminal.SetFileContent(nodeIsDeletedTemplate->GetOutput());

	return nodeIsTerminal;
}
