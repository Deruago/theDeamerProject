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

#include "Deamer/Tool/Type/DeamerDefaultApplication/AstViewer/AstViewer.h"
#include "Deamer/Template/Tool/Type/DeamerDefaultApplication/AstViewer/AstViewerTemplate.h"

deamer::tool::type::deamerdefaultapplication::AstViewer::AstViewer(reference reference_)
	: Reference(reference_)
{
}

void deamer::tool::type::deamerdefaultapplication::AstViewer::Generate(
	::deamer::file::tool::Directory& output)
{
	auto astViewerTemplate =
		templates::tool::deamerdefaultapplication::astviewer::AstViewerTemplate();

	auto languageName =
		Reference.GetDefinition<language::type::definition::property::Type::Identity>()
			.GetName()
			->value;
	astViewerTemplate.language_name_->Set(languageName);
	astViewerTemplate.parser_->Set("Bison");

	auto astViewerFile = file::tool::File("main", "cpp", astViewerTemplate.GetOutput());

	output.SetCMakeLists("add_executable(" + languageName +
						 "deamerAstViewer main.cpp)\n"
						 "target_link_libraries(" +
						 languageName +
						 "deamerAstViewer PRIVATE Deamer::External Deamer::Algorithm "
						 "deamer_reserved_" +
						 languageName + "_core_library)\n");

	output.AddFile(astViewerFile);
}
