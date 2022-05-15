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

#ifndef DEAMER_TOOL_OOPSYNTAXRECOGNIZER_OOPSYNTAXRECOGNIZER_H
#define DEAMER_TOOL_OOPSYNTAXRECOGNIZER_OOPSYNTAXRECOGNIZER_H

#include "Deamer/Language/Reference/PropertyDefinition.h"
#include "Deamer/Tool/Type/Base.h"
#include <memory>

namespace deamer::templates::oopsyntaxrecognizer
{
	class RecognizerTemplate;
}

namespace deamer::tool::type::oopsyntaxrecognizer
{
	/*!	\class OopSyntaxRecognizer
	 *
	 *	\brief Uses the Lexicon, Grammar, and OOP Syntax LPDs to generate a Oop Concept Recognizer.
	 */
	class OopSyntaxRecognizer : public ::deamer::tool::type::Base
	{
	public:
		using reference = language::reference::PropertyDefinition<
			language::type::definition::property::Type::Lexicon,
			language::type::definition::property::Type::Grammar,
			language::type::definition::property::Type::OOPSyntax>;

	private:
		reference Reference;

	public:
		OopSyntaxRecognizer(reference reference_);

	public:
		deamer::file::tool::Output Generate() override;

	private:
		std::string GenerateRecognizer();
		void ImplementOopConceptScopes(
			std::unique_ptr<::deamer::templates::oopsyntaxrecognizer::RecognizerTemplate>&
				recognizerTemplate) const;
		void ImplementOopConceptLinks(
			std::unique_ptr<deamer::templates::oopsyntaxrecognizer::RecognizerTemplate>&
				recognizerTemplate);
	};
}

#endif // DEAMER_TOOL_OOPSYNTAXRECOGNIZER_OOPSYNTAXRECOGNIZER_H
