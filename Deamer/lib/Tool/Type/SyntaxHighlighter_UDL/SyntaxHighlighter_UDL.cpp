#include "Deamer/Tool/Type/SyntaxHighlighter_UDL/SyntaxHighlighter_UDL.h"
#include "Deamer/Language/Reference/ReverseLookup.h"
#include "Deamer/Language/Type/Definition/Object/Main/Colorization/TerminalColor.h"
#include "Deamer/Template/Tool/Type/SyntaxHighlighter/UDL/UDLSyntaxHighlighterTemplate.h"
#include <Deamer/Dregx/Fuzzer.h>

deamer::tool::type::syntaxhighlighter_udl::SyntaxHighlighter_UDL::SyntaxHighlighter_UDL(
	reference reference_)
	: Base(deamer::tool::type::Tool::SyntaxHighlighter_UDL),
	  Reference(reference_)
{
}

deamer::file::tool::Output
deamer::tool::type::syntaxhighlighter_udl::SyntaxHighlighter_UDL::Generate()
{
	const auto language_name =
		Reference.GetDefinition<language::type::definition::property::Type::Identity>().GetName();

	file::tool::Output output("SyntaxHighlighter_UDL");

	const auto colorization =
		Reference.GetDefinition<language::type::definition::property::Type::Colorization>();

	const auto colorGroups = colorization.ColorGroups;

	auto udlFormat =
		::deamer::templates::tool::type::syntaxhighligher::UDLSyntaxHighlighterTemplate();
	udlFormat.language_name_->Set(language_name->value);
	udlFormat.language_extension_->Set(language_name->value);
	udlFormat.keywords_1_->Variable_Field_Separator()->Set("");
	udlFormat.keywords_2_->Variable_Field_Separator()->Set("");
	udlFormat.keywords_3_->Variable_Field_Separator()->Set("");
	udlFormat.keywords_4_->Variable_Field_Separator()->Set("");
	udlFormat.keywords_5_->Variable_Field_Separator()->Set("");
	udlFormat.keywords_6_->Variable_Field_Separator()->Set("");
	udlFormat.keywords_7_->Variable_Field_Separator()->Set("");
	udlFormat.keywords_8_->Variable_Field_Separator()->Set("");

	std::uint8_t counter = 0;

	for (auto i = 0; i < colorGroups.size() && i < 8; i++)
	{
		counter += 1;

		const auto* const currentColorGroup = colorGroups[i];
		const auto reverseLookupTerminalColors = ::deamer::language::reference::ReverseLookup<
			::deamer::language::type::definition::object::main::TerminalColor>(&Reference);
		const auto resultTerminalColors = reverseLookupTerminalColors.Get(currentColorGroup);

		if (resultTerminalColors.IsEmpty())
		{
			continue;
		}

		bool allAreInfinite = true;
		for (const auto& terminalColor : resultTerminalColors.GetObjects())
		{
			dregx::Fuzzer fuzzer(terminalColor->terminal->Regex);
			if (!fuzzer.IsRegexFinite())
			{
				// Infinite regexes are not supported.
				continue;
			}
			allAreInfinite = false;

			auto variants = fuzzer.GetAllFiniteMatches();
			for (auto variant : variants)
			{
				udlFormat.keyword_->Set(variant);

				switch (counter)
				{
				case 1:
					udlFormat.keywords_1_->ExpandVariableField();
					break;
				case 2:
					udlFormat.keywords_2_->ExpandVariableField();
					break;
				case 3:
					udlFormat.keywords_3_->ExpandVariableField();
					break;
				case 4:
					udlFormat.keywords_4_->ExpandVariableField();
					break;
				case 5:
					udlFormat.keywords_5_->ExpandVariableField();
					break;
				case 6:
					udlFormat.keywords_6_->ExpandVariableField();
					break;
				case 7:
					udlFormat.keywords_7_->ExpandVariableField();
					break;
				case 8:
					udlFormat.keywords_8_->ExpandVariableField();
					break;
				default:
					break;
				}
			}

			if (allAreInfinite)
			{
				// Otherwise the first list of keywords is empty
				counter -= 1;
			}
		}
	}

	const file::tool::File udlSyntaxHighlighter(language_name->value, "xml", udlFormat.GetOutput());
	output.AddFileToExternal(udlSyntaxHighlighter);
	return output;
}
