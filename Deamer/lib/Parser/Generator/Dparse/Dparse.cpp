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
#include "Deamer/Parser/Type/Dparse/ParserDefinitionRecursiveDescent.h"
#include "Deamer/Parser/Type/Dparse/ParserHeader.h"
#include "Deamer/Parser/Type/Dparse/Print.h"
#include "Deamer/Parser/Type/Dparse/StateField.h"
#include "Deamer/Type/Exception/NotImplementedException.h"
#include <chrono>
#include <memory>

deamer::parser::generator::dparse::Dparse::Dparse(const ReferenceType reference_)
	: Base(tool::type::Tool::Dparse),
	  reference(reference_),
	  name(reference.GetDefinition<language::type::definition::property::Type::Identity>()
			   .GetName()
			   ->value)
{
}

deamer::file::tool::Output deamer::parser::generator::dparse::Dparse::ConstructLR1()
{
	std::chrono::system_clock::time_point start;
	if (reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsArgumentSet({tool::type::Tool::Dparse, "benchmark-time"}))
	{
		start = std::chrono::system_clock::now();
	}
	algorithm.set_flag(Algorithm::LR);

	auto stateField = StateField(reference);
	stateField.Compile();

	file::tool::Output output("Dparse");
	auto parserHeader = type::dparse::ParserHeader(reference);
	auto parserDefinition = type::dparse::ParserDefinition(reference, stateField, algorithm);

	output.AddFileToExternal(file::tool::File("Dparse", "cpp", parserDefinition.Generate()));
	output.AddFileToInclude(file::tool::File("Parser", "h", parserHeader.Generate()));

	output.AddCMakeListsToExternal(std::string{"set(source_files ./Dparse.cpp)\n" + name +
											   "_add_external_library(Dparse ${source_files})\n"});

	if (reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsArgumentSet({tool::type::Tool::Dparse, "print-table"}))
	{
		Print print(&stateField);
		std::cout << print.ToGraphviz() << "\n";
	}

	std::size_t shiftReduceConflicts = stateField.GetActionTable().GetShiftReduceConflictTotal();
	std::size_t reduceReduceConflicts = stateField.GetActionTable().GetReduceReduceConflictTotal();

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

	if (reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsArgumentSet({tool::type::Tool::Dparse, "benchmark-time"}))
	{
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> diff = end - start;
		std::cout << diff.count() << "s\n";
	}

	return output;
}

deamer::file::tool::Output deamer::parser::generator::dparse::Dparse::ConstructLRK()
{
	throw deamer::type::NotImplementedException();
}

deamer::file::tool::Output deamer::parser::generator::dparse::Dparse::ConstructSLR()
{
	algorithm.set_flag(Algorithm::SLR);
	return ConstructLR1();
}

deamer::file::tool::Output deamer::parser::generator::dparse::Dparse::ConstructLL1()
{
	throw deamer::type::NotImplementedException();
}

deamer::file::tool::Output deamer::parser::generator::dparse::Dparse::ConstructLLK()
{
	throw deamer::type::NotImplementedException();
}

deamer::file::tool::Output deamer::parser::generator::dparse::Dparse::ConstructGLL1()
{
	algorithm.set_flag(Algorithm::General);
	return ConstructLL1();
}

deamer::file::tool::Output deamer::parser::generator::dparse::Dparse::ConstructGLLK()
{
	algorithm.set_flag(Algorithm::General);
	return ConstructLLK();
}

deamer::file::tool::Output deamer::parser::generator::dparse::Dparse::ConstructLALR()
{
	algorithm.set_flag(Algorithm::LALR);
	return ConstructLR1();
}

deamer::file::tool::Output deamer::parser::generator::dparse::Dparse::ConstructAdaptiveLALR()
{
	algorithm.set_flag(Algorithm::Adaptive);
	return ConstructLALR();
}

deamer::file::tool::Output deamer::parser::generator::dparse::Dparse::ConstructGLR()
{
	algorithm.set_flag(Algorithm::General);
	return ConstructLR1();
}

deamer::file::tool::Output deamer::parser::generator::dparse::Dparse::ConstructGSLR()
{
	algorithm.set_flag(Algorithm::General);
	return ConstructSLR();
}

deamer::file::tool::Output deamer::parser::generator::dparse::Dparse::ConstructGLALR()
{
	algorithm.set_flag(Algorithm::General);
	return ConstructLALR();
}

deamer::file::tool::Output deamer::parser::generator::dparse::Dparse::ConstructGAdaptiveLALR()
{
	algorithm.set_flag(Algorithm::General);
	return ConstructAdaptiveLALR();
}

deamer::file::tool::Output deamer::parser::generator::dparse::Dparse::ConstructLAKLRM()
{
	throw deamer::type::NotImplementedException();
}

deamer::file::tool::Output deamer::parser::generator::dparse::Dparse::ConstructIELR()
{
	throw deamer::type::NotImplementedException();
}

deamer::file::tool::Output deamer::parser::generator::dparse::Dparse::ConstructRecursiveDescent()
{
	std::chrono::system_clock::time_point start;
	if (reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsArgumentSet({tool::type::Tool::Dparse, "benchmark-time"}))
	{
		start = std::chrono::system_clock::now();
	}

	file::tool::Output output("Dparse");
	auto parserHeader = type::dparse::ParserHeader(reference);
	auto parserDefinition = type::dparse::ParserDefinitionRecursiveDescent(reference);

	output.AddFileToExternal(file::tool::File("Dparse", "cpp", parserDefinition.Generate()));
	output.AddFileToInclude(file::tool::File("Parser", "h", parserHeader.Generate()));

	output.AddCMakeListsToExternal(std::string{"set(source_files ./Dparse.cpp)\n" + name +
											   "_add_external_library(Dparse ${source_files})\n"});

	if (reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsArgumentSet({tool::type::Tool::Dparse, "benchmark-time"}))
	{
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> diff = end - start;
		std::cout << diff.count() << "s\n";
	}

	return output;
}

deamer::file::tool::Output deamer::parser::generator::dparse::Dparse::Generate()
{
	auto hasArgument = [&](std::vector<std::vector<std::string>> listOfArgumentRequirements) {
		for (auto argumentRequirements : listOfArgumentRequirements)
		{
			bool result = true;
			for (auto argumentRequirement : argumentRequirements)
			{
				result &=
					reference
						.GetDefinition<language::type::definition::property::Type::Generation>()
						.IsArgumentSet({tool::type::Tool::Dparse, argumentRequirement});
			}

			if (result)
			{
				return true;
			}
		}

		return false;
	};

	if (hasArgument({{"general"}}))
	{
		algorithm.set_flag(Algorithm::General);
	}
	if (hasArgument({{"adaptive"}}))
	{
		algorithm.set_flag(Algorithm::Adaptive);
	}

	if (hasArgument({{"construct-lr1"}}))
	{
		return ConstructLR1();
	}
	else if (hasArgument({{"construct-lrk"}}))
	{
		return ConstructLRK();
	}
	else if (hasArgument({{"construct-glr"}}))
	{
		return ConstructGLR();
	}
	else if (hasArgument({{"construct-slr"}}))
	{
		return ConstructSLR();
	}
	else if (hasArgument({{"construct-general-slr"}, {"construct-gslr"}}))
	{
		return ConstructGSLR();
	}
	else if (hasArgument({{"construct-lalr"}}))
	{
		return ConstructLALR();
	}
	else if (hasArgument({{"construct-general-lalr"}, {"construct-glalr"}}))
	{
		return ConstructGLALR();
	}
	else if (hasArgument({{"construct-adaptive-lalr"}, {"construct-alalr"}}))
	{
		return ConstructAdaptiveLALR();
	}
	else if (hasArgument({{"construct-general-adaptive-lalr"}, {"construct-galalr"}}))
	{
		return ConstructGAdaptiveLALR();
	}
	else if (hasArgument({{"construct-laklrm"}}))
	{
		return ConstructLAKLRM();
	}
	else if (hasArgument({{"construct-general-ll1"}, {"construct-gll1"}}))
	{
		return ConstructGLL1();
	}
	else if (hasArgument({{"construct-general-llk"}, {"construct-gllk"}}))
	{
		return ConstructGLLK();
	}
	else if (hasArgument({{"construct-recursivedescent"}, {"construct-recursive-descent"}}))
	{
		return ConstructRecursiveDescent();
	}
	else if (hasArgument({{"construct-ielr"}}))
	{
		return ConstructIELR();
	}
	else
	{
		return ConstructLR1();
	}
}
