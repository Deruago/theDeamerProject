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

#include "Deamer/Tool/Type/DeamerDefaultApplication/TokenViewer/TokenViewer.h"
#include "Deamer/Template/Tool/Type/DeamerDefaultApplication/TokenViewer/TokenViewerTemplate.h"

deamer::tool::type::deamerdefaultapplication::TokenViewer::TokenViewer(reference reference_)
	: Reference(reference_)
{
}

void deamer::tool::type::deamerdefaultapplication::TokenViewer::Generate(
	::deamer::file::tool::Directory& output)
{
	auto tokenViewerTemplate =
		templates::tool::deamerdefaultapplication::tokenviewer::TokenViewerTemplate();

	auto languageName =
		Reference.GetDefinition<language::type::definition::property::Type::Identity>()
			.GetName()
			->value;
	tokenViewerTemplate.language_name_->Set(languageName);
	if (Reference.GetDefinition<language::type::definition::property::Type::Generation>().IsToolSet(
			Tool::Bison))
	{
		tokenViewerTemplate.parser_->Set("Bison");
	}
	else if (Reference.GetDefinition<language::type::definition::property::Type::Generation>()
				 .IsToolSet(Tool::Dparse))
	{
		tokenViewerTemplate.parser_->Set("Dparse");
	}
	else
	{
		const auto tmp = file::tool::File("main", "cpp", "");
		output.AddFile(tmp);
		return;
	}

	if (Reference.GetDefinition<language::type::definition::property::Type::Generation>().IsToolSet(
			Tool::Flex))
	{
		tokenViewerTemplate.lexer_->Set("Flex");
	}
	else if (Reference.GetDefinition<language::type::definition::property::Type::Generation>()
				 .IsToolSet(Tool::Dleg))
	{
		tokenViewerTemplate.lexer_->Set("Dleg");
	}
	else
	{
		const auto tmp = file::tool::File("main", "cpp", "");
		output.AddFile(tmp);
		return;
	}

	auto tokenViewerFile = file::tool::File("main", "cpp", tokenViewerTemplate.GetOutput());

	output.SetCMakeLists("add_executable(" + languageName +
						 "deamerTokenViewer main.cpp)\n"
						 "target_link_libraries(" +
						 languageName +
						 "deamerTokenViewer  PRIVATE Deamer::External Deamer::Algorithm "
						 "deamer_reserved_" +
						 languageName + "_core_library)\n ");
	output.AddFile(tokenViewerFile);
}
