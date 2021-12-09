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
		Reference.GetDefinition<language::type::definition::property::Type::Identity>().name->value;
	tokenViewerTemplate.language_name_->Set(languageName);
	tokenViewerTemplate.lexer_->Set("Flex");

	auto tokenViewerFile = file::tool::File("main", "cpp", tokenViewerTemplate.GetOutput());

	output.SetCMakeLists(
		"# Auto-generated, do not changed this code\n"
		"# Part of: DeamerDefaultApplication tool\n"
		"# More information: https://github.com/Deruago/theDeamerProject\n"
		"\n"
		"add_executable(" +
		languageName +
		"deamerTokenViewer main.cpp)\n"
		"target_link_libraries(" +
		languageName + "deamerTokenViewer " + languageName + "_static_library)\n");
	output.AddFile(tokenViewerFile);
}
