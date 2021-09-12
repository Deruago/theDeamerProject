#include "Deamer/Tool/Type/SyntaxHighlighter/UDL/UDL.h"
#include "Deamer/Template/Tool/Type/SyntaxHighlighter/UDL/UDLSyntaxHighlighterTemplate.h"
#include "Deamer/Language/Reference/ReverseLookup.h"
#include "Deamer/Language/Type/Definition/Object/Main/Colorization/TerminalColor.h"

deamer::tool::type::syntaxhighlighter::udl::UDL::UDL(reference reference_)
	: syntaxhighlighter::Base(Tool::SyntaxHighlighter_UDL),
	  Reference(reference_)
{
}

deamer::file::tool::Output deamer::tool::type::syntaxhighlighter::udl::UDL::Generate()
{
	const auto language_name =
		Reference.GetDefinition<language::type::definition::property::Type::Identity>().name;

	file::tool::Output output("SyntaxHighlighter_UDL");

	const auto colorization =
		Reference.GetDefinition<language::type::definition::property::Type::Colorization>();

	const auto colorGroups = colorization.ColorGroups;

	auto udlFormat = ::deamer::templates::tool::type::syntaxhighligher::UDLSyntaxHighlighterTemplate();
	udlFormat.language_name_->Set(language_name->value);
	udlFormat.language_extension_->Set(language_name->value);

	std::uint8_t counter = 0;

	for (auto i = 0; i < colorGroups.size() && i < 8; i++)
	{
		counter += 1;

		const auto* const currentColorGroup = colorGroups[i];
		const auto reverseLookupTerminalColors = ::deamer::language::reference::ReverseLookup<
			::deamer::language::type::definition::object::main::TerminalColor>(&Reference);
		const auto resultTerminalColors = reverseLookupTerminalColors.Get(currentColorGroup);
		
		if(resultTerminalColors.IsEmpty())
		{
			continue;
		}

		for (const auto& terminalColor : resultTerminalColors.GetObjects())
		{
			const auto& regex = terminalColor->terminal->Regex;
			if (regex.find_first_of("[") != regex.npos && regex.find_first_of("]") != regex.npos)
			{
				continue; // is it most likely a regex, regex are not supported in UDL.
			}

			switch (counter)
			{
			case 1:
				udlFormat.keywords_1_->Add(regex + " ");
				break;
			case 2:
				udlFormat.keywords_2_->Add(regex + " ");
				break;
			case 3:
				udlFormat.keywords_3_->Add(regex + " ");
				break;
			case 4:
				udlFormat.keywords_4_->Add(regex + " ");
				break;
			case 5:
				udlFormat.keywords_5_->Add(regex + " ");
				break;
			case 6:
				udlFormat.keywords_6_->Add(regex + " ");
				break;
			case 7:
				udlFormat.keywords_7_->Add(regex + " ");
				break;
			case 8:
				udlFormat.keywords_8_->Add(regex + " ");
				break;
			}
		}
	}

	const file::tool::File udlSyntaxHighlighter(language_name->value, "xml", udlFormat.GetOutput());
	output.AddFileToExternal(udlSyntaxHighlighter);
	return output;
}