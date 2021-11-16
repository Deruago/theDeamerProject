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

deamer::file::compiler::Output::Output(const ReferenceType reference_)
	: parent(std::nullopt),
	  reference(reference_)
{
}

deamer::file::compiler::Output::Output(const Output& rhs)
	: LanguageOut(rhs.LanguageOut),
	  CompilersOut(rhs.CompilersOut),
	  parent(rhs.parent),
	  reference(rhs.reference)
{
	ReconstructParentPointers(this);
}

deamer::file::compiler::Output::Output(const Output&& rhs) noexcept
	: LanguageOut(rhs.LanguageOut),
	  CompilersOut(rhs.CompilersOut),
	  parent(rhs.parent),
	  reference(rhs.reference)
{
	ReconstructParentPointers(this);
}

void deamer::file::compiler::Output::AddLanguageToolOutput(
	const deamer::file::tool::Output& newLanguageOutput)
{
	LanguageOut.push_back(newLanguageOutput);
}

void deamer::file::compiler::Output::AddLanguageToolOutput(
	const std::vector<deamer::file::tool::Output>& newLanguageOutputs)
{
	for (const auto& newLanguageOutput : newLanguageOutputs)
	{
		AddLanguageToolOutput(newLanguageOutput);
	}
}

void deamer::file::compiler::Output::AddCompilerOutput(
	const deamer::file::compiler::Output& newCompilerOutput)
{
	auto compilerOutput = newCompilerOutput;
	compilerOutput.parent = this;
	CompilersOut.push_back(compilerOutput);
	ReconstructParentPointers(this);
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

std::optional<const deamer::file::compiler::Output*>
deamer::file::compiler::Output::GetParent() const
{
	return parent;
}

void deamer::file::compiler::Output::ReconstructParentPointers(
	deamer::file::compiler::Output* output)
{
	for (auto& compilerOutput : output->CompilersOut)
	{
		compilerOutput.parent = output;
		ReconstructParentPointers(&compilerOutput);
	}
}
