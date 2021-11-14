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

#ifndef DEAMER_FILE_COMPILER_OUTPUT_H
#define DEAMER_FILE_COMPILER_OUTPUT_H

#include "Deamer/File/Tool/Output.h"
#include "Deamer/Language/Reference/PropertyDefinition.h"
#include <optional>
#include <vector>

namespace deamer::file::compiler
{
	/*!	\class Output
	 *
	 *	\brief This class is used to combine language outputs and compiler outputs together.
	 *
	 *	\details One can use this to assemble multi compilers. And to generate the multi compiler.
	 */
	class Output
	{
	public:
		using ReferenceType = language::reference::PropertyDefinition<>;

	private:
		std::vector<deamer::file::tool::Output> LanguageOut;
		std::vector<deamer::file::compiler::Output> CompilersOut;

		std::optional<const Output*> parent;

		const ReferenceType reference;

	public:
		Output(const ReferenceType reference_);
		~Output() = default;

		Output(const Output& rhs);
		Output(const Output&& rhs) noexcept;

	public:
		void AddLanguageToolOutput(const deamer::file::tool::Output& newLanguageOutput);
		void
		AddLanguageToolOutput(const std::vector<deamer::file::tool::Output>& newLanguageOutputs);
		void AddCompilerOutput(const deamer::file::compiler::Output& newCompilerOutput);

		std::vector<deamer::file::tool::Output> GetLanguageOutputs() const;
		std::vector<deamer::file::compiler::Output> GetCompilerOutputs() const;
		ReferenceType GetLanguageReference() const;
		std::optional<const Output*> GetParent() const;

	private:
		void ReconstructParentPointers(deamer::file::compiler::Output* output);
	};
}

#endif // DEAMER_FILE_COMPILER_OUTPUT_H
