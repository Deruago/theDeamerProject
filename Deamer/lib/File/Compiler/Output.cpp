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

#include "Deamer/File/Compiler/Output.h"

deamer::file::compiler::Output::Output(const ReferenceType reference_) : reference(reference_)
{
}

void deamer::file::compiler::Output::AddLanguageToolOutput(
	const deamer::file::tool::Output& newLanguageOutput)
{
	LanguageOut.push_back(newLanguageOutput);
}

void deamer::file::compiler::Output::AddCompilerOutput(
	const deamer::file::compiler::Output& newCompilerOutput)
{
	CompilersOut.push_back(newCompilerOutput);
}

std::vector<deamer::file::tool::Output> deamer::file::compiler::Output::GetLanguageOutputs() const
{
	return LanguageOut;
}

std::vector<deamer::file::compiler::Output>
deamer::file::compiler::Output::GetCompilerOutputs() const
{
	return CompilersOut;
}

deamer::file::compiler::Output::ReferenceType
deamer::file::compiler::Output::GetLanguageReference() const
{
	return reference;
}
