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

#include "Deamer/Parser/Generator/Dparse/Dparse.h"
#include "Deamer/File/Tool/Action/Builder.h"
#include "Deamer/Parser/Type/Dparse/ParserDefinition.h"
#include "Deamer/Parser/Type/Dparse/ParserHeader.h"
#include "Deamer/Parser/Type/Dparse/Print.h"
#include "Deamer/Parser/Type/Dparse/StateField.h"
#include <memory>

deamer::parser::generator::dparse::Dparse::Dparse(const ReferenceType reference_)
	: Base(tool::type::Tool::Dparse),
	  reference(reference_),
	  name(reference.GetDefinition<language::type::definition::property::Type::Identity>()
			   .GetName()
			   ->value)
{
}

deamer::file::tool::Output deamer::parser::generator::dparse::Dparse::Generate()
{
	auto stateField = StateField(reference);
	stateField.Compile();

	file::tool::Output output("Dparse");
	auto parserHeader = type::dparse::ParserHeader(reference);
	auto parserDefinition = type::dparse::ParserDefinition(reference, stateField);

	output.AddFileToExternal(file::tool::File("Dparse", "cpp", parserDefinition.Generate()));
	output.AddFileToInclude(file::tool::File("Parser", "h", parserHeader.Generate()));

	output.AddCMakeListsToExternal(std::string{"set(source_files ./Dparse.cpp)\n" + name +
											   "_add_external_library(Dparse ${source_files})\n"});

	std::size_t shiftReduceConflicts = 0;
	std::size_t reduceReduceConflicts = 0;

	for (auto item : stateField.GetActionTable().GetTable())
	{
		for (auto entry : item.second)
		{
			std::size_t shift = 0;
			std::size_t reduce = 0;
			for (auto action : entry.second)
			{
				if (action.GetType() == type::dparse::ActionType::Shift)
				{
					shift++;
				}
				else if (action.GetType() == type::dparse::ActionType::Reduce)
				{
					reduce++;
				}
			}
			if (shift > 0 && reduce > 0)
			{
				shiftReduceConflicts++;
			}
			if (reduce > 1)
			{
				reduceReduceConflicts++;
			}
		}
	}

	if (shiftReduceConflicts > 0)
	{
		std::cout << "Warning: Shift/Reduce conflicts: " << shiftReduceConflicts << "\n";
		std::cout << "	- Default action is shifting, might not be an issue.\n";
	}
	if (reduceReduceConflicts > 0)
	{
		std::cout << "Warning: Reduce/Reduce conflicts: " << reduceReduceConflicts << "\n";
		std::cout << "	- These issues can result in unwanted matches, default action is the first "
					 "reduce action.\n";
	}

	return output;
}
