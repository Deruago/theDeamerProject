#include "Deamer/Tool/Type/DLDLConverter/Grammar/Grammar.h"

deamer::tool::type::dldlconverter::grammar::Grammar::Grammar(reference reference_)
	: Reference(reference_)
{
}

void deamer::tool::type::dldlconverter::grammar::Grammar::Generate(
	::deamer::file::tool::Output& output)
{
	auto grammarTemplate = templates::dldlconverter::grammar::GrammarTemplate();

	// In DLDL start reorders the nonterminal order.
	// Thus we do not have any check to check for Start abstractions,
	// It is local to DLDL.
	for (language::reference::LDO<language::type::definition::object::main::NonTerminal>
			 nonTerminal :
		 Reference.GetDefinition<language::type::definition::property::Type::Grammar>()
			 .NonTerminals)
	{
		grammarTemplate.productionrule_->variable_field_->Clear();

		grammarTemplate.abstraction_->Set(
			GetAbstractionText(nonTerminal->abstraction, nonTerminal->IsInlined()));
		grammarTemplate.nonterminal_->Set(nonTerminal->Name);

		for (language::reference::LDO<language::type::definition::object::main::ProductionRule>
				 productionRule : nonTerminal->ProductionRules)
		{
			auto productionRuleText = productionRule->GetText();
			if (productionRuleText.empty())
			{
				productionRuleText = "EMPTY";
			}

			grammarTemplate.productionrule_content_->Set(productionRuleText);
			grammarTemplate.productionrule_->ExpandVariableField();
		}

		grammarTemplate.nonterminal_declaration_->ExpandVariableField();
	}

	const auto grammarFile = file::tool::File("Grammar", "dldl", grammarTemplate.GetOutput());

	output.AddFileToExternal(grammarFile);
}

std::string deamer::tool::type::dldlconverter::grammar::Grammar::GetAbstractionText(
	const language::type::definition::object::main::NonTerminalAbstraction& abstraction,
	const bool& isInlined) const
{
	std::string inlineText;
	if (isInlined)
	{
		inlineText = "Inline";
	}

	switch (abstraction)
	{
	case language::type::definition::object::main::NonTerminalAbstraction::Standard: {
		if (inlineText.empty())
		{
			return "";
		}
		return inlineText + ": ";
	}
	case language::type::definition::object::main::NonTerminalAbstraction::Group: {
		if (!inlineText.empty())
		{
			inlineText += " ";
		}
		return inlineText + "Group: ";
	}
	}

	return "";
}
