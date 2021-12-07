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

#include "Deamer/Tool/Type/DeamerDefaultApplication/DeamerDefaultApplication.h"
#include "Deamer/Language/Reference/ReverseLookup.h"
#include "Deamer/Tool/Type/DeamerDefaultApplication/AstViewer/AstViewer.h"
#include "Deamer/Tool/Type/DeamerDefaultApplication/TokenViewer/TokenViewer.h"

deamer::tool::type::deamerdefaultapplication::DeamerDefaultApplication::DeamerDefaultApplication(
	reference reference_)
	: Base(::deamer::tool::type::Tool::DeamerDefaultApplication),
	  Reference(reference_)
{
}

deamer::file::tool::Output
deamer::tool::type::deamerdefaultapplication::DeamerDefaultApplication::Generate()
{
	const auto language_name =
		Reference.GetDefinition<language::type::definition::property::Type::Identity>().name->value;

	file::tool::Output output("DeamerDefaultApplication");

	auto deamerDefaultApplicationDirectory = file::tool::Directory("Deamer");
	auto tokenViewerDirectory = file::tool::Directory("TokenViewer");
	auto astViewerDirectory = file::tool::Directory("AstViewer");
	auto defaultCompilerDirectory = file::tool::Directory("Compiler");

	TokenViewer(Reference).Generate(tokenViewerDirectory);
	AstViewer(Reference).Generate(astViewerDirectory);

	deamerDefaultApplicationDirectory.AddDirectory(tokenViewerDirectory);
	deamerDefaultApplicationDirectory.AddDirectory(astViewerDirectory);
	deamerDefaultApplicationDirectory.AddDirectory(defaultCompilerDirectory);

	output.AddDirectoryToSources(deamerDefaultApplicationDirectory);

	return output;
}
