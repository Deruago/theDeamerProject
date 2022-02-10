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

#include "Deamer/Language/Type/Definition/Property/Main/Generation.h"

deamer::language::type::definition::property::main::Generation::Generation(std::vector<object::main::OSTarget*> osTarget_, 
			std::vector<object::main::Generate*> generateStatements_, 
			std::vector<object::main::GenerateArgument*> generateArguments_, 
			std::vector<object::main::Integrate*> integrateStatements_)
	: Definition(Type::Generation),
	osTarget(osTarget_),
	generateStatements(generateStatements_),
	generateArguments(generateArguments_),
	integrateStatements(integrateStatements_)
{
	references.Add(osTarget);
	references.Add(generateStatements);
	references.Add(generateArguments);
	references.Add(integrateStatements);

}

bool deamer::language::type::definition::property::main::Generation::IsIntegrationSet(const object::main::Integrate& integrate) const
{
	for (const auto* integrateStatement : integrateStatements)
	{
		if (*integrateStatement == integrate)
		{
			return true;
		}
	}

	return false;
}

bool deamer::language::type::definition::property::main::Generation::IsArgumentSet(const object::main::GenerateArgument& generateArgument) const
{
	for (const auto* argument : generateArguments)
	{
		if (*argument == generateArgument)
		{
			return true;
		}
	}
	return false;
}

deamer::file::tool::OSType deamer::language::type::definition::property::main::Generation::GetOSTarget() const
{
	if (osTarget.empty())
	{
		return deamer::file::tool::os_used;
	}

	return osTarget[0]->os;
}


