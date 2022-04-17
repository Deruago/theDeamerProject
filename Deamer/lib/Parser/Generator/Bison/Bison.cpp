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

#include "Deamer/Parser/Generator/Bison/Bison.h"
#include "Deamer/File/Tool/Action/Builder.h"
#include "Deamer/Parser/Type/Bison/ParserDefinition.h"
#include "Deamer/Parser/Type/Bison/ParserHeader.h"
#include <memory>

deamer::parser::generator::bison::Bison::Bison(const ReferenceType reference_)
	: Base(tool::type::Tool::Bison),
	  reference(reference_),
	  name(reference.GetDefinition<language::type::definition::property::Type::Identity>()
			   .GetName()
			   ->value)
{
}

deamer::file::tool::Output deamer::parser::generator::bison::Bison::Generate()
{
	file::tool::Output output("Bison");
	auto parserHeader = type::bison::ParserHeader(reference);
	auto parserDefinition = type::bison::ParserDefinition(reference);

	const std::string fileName = name + "_parser";
	const file::tool::File bisonFile(fileName, "y", parserDefinition.Generate());
	const file::tool::File bisonParser("Parser", "h", parserHeader.Generate());

	output.AddFileToExternal(bisonFile);
	output.AddFileToInclude(bisonParser);
	output.AddActionToExternal(externalAction());
	output.AddCMakeListsToExternal({externalCMakeLists(), dependenciesCMakeLists()});

	return output;
}

std::unique_ptr<deamer::file::tool::action::Action>
deamer::parser::generator::bison::Bison::externalAction()
{
	auto builder = file::tool::action::Builder();

	builder
		.PlatformSpecificCommand(
			{{file::tool::OSType::os_linux, "bison -p" + name + " -d ./" + name + "_parser.y"}})
		.MoveFile("./" + name + "_parser.tab.c", "./" + name + "_parser.tab.cpp");

	return builder.GetAction();
}

std::string deamer::parser::generator::bison::Bison::externalCMakeLists()
{
	return "set(source_files ./" + name + "_parser.tab.cpp)\n" + name +
		   "_add_external_library(Bison ${source_files})\n";
}

std::string deamer::parser::generator::bison::Bison::dependenciesCMakeLists()
{
	return "";
}
