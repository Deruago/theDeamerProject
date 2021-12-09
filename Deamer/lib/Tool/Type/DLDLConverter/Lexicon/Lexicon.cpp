#include "Deamer/Tool/Type/DLDLConverter/Lexicon/Lexicon.h"

deamer::tool::type::dldlconverter::lexicon::Lexicon::Lexicon(reference reference_)
	: Reference(reference_)
{
}

void deamer::tool::type::dldlconverter::lexicon::Lexicon::Generate(
	::deamer::file::tool::Output& output)
{
	auto lexiconTemplate = templates::dldlconverter::lexicon::LexiconTemplate();

	for (auto* terminal :
		 Reference.GetDefinition<language::type::definition::property::Type::Lexicon>().Terminals)
	{
		lexiconTemplate.abstraction_->Set(GetAbstractionText(terminal->Special));
		lexiconTemplate.name_->Set(terminal->Name);
		lexiconTemplate.regex_->Set(terminal->Regex);
		lexiconTemplate.terminal_declaration_->ExpandVariableField();
	}

	const auto lexiconFile = file::tool::File("Lexicon", "dldl", lexiconTemplate.GetOutput());

	output.AddFileToExternal(lexiconFile);
}

std::string deamer::tool::type::dldlconverter::lexicon::Lexicon::GetAbstractionText(
	const language::type::definition::object::main::SpecialType& special) const
{
	switch (special)
	{
	case language::type::definition::object::main::SpecialType::Standard:
		return "Terminal";
	case language::type::definition::object::main::SpecialType::Delete:
		return "Delete";
	case language::type::definition::object::main::SpecialType::Ignore:
		return "Ignore";
	case language::type::definition::object::main::SpecialType::NoValue:
		return "NoValue";
	case language::type::definition::object::main::SpecialType::Crash:
		return "Crash";
	}

	return "Terminal";
}
