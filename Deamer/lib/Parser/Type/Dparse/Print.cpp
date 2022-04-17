#include "Deamer/Parser/Type/Dparse/Print.h"
#include "Deamer/Language/Reference/LDO.h"
#include "Deamer/Language/Reference/ReverseLookup.h"

deamer::parser::generator::dparse::Print::Print(StateField* stateField_)
	: stateField(stateField_),
	  reference(stateField->GetReference())
{
}

std::string deamer::parser::generator::dparse::Print::ToGraphviz()
{
	std::string stateFieldText = "digraph {\n";

	for (auto state : stateField->GetStates())
	{
		auto stateText = ParseState(state);
		stateFieldText += stateText + "\n";
	}
	stateFieldText += "}\n";

	return stateFieldText;
}

std::string deamer::parser::generator::dparse::Print::ActionTable()
{
	std::string output;
	for (auto [state, action] : stateField->GetActionTable().GetTable())
	{
		output += "State: " + std::to_string(stateField->GetIndexOfState(state)) + "\n";
		for (auto [lookahead, actionElements] : action)
		{
			std::string lookaheadName = lookahead->Name;
			output += "\tLookahead: " + lookaheadName + "\n";
			for (auto actionElement : actionElements)
			{
				output += "\t\tElement: " + std::to_string(actionElement.GetTarget());
				output += " ";
				switch (actionElement.GetType())
				{
				case type::dparse::ActionType::unknown:
					output += "unknown";
					break;
				case type::dparse::ActionType::Shift:
					output += "Shift";
					break;
				case type::dparse::ActionType::Reduce:
					output += "Reduce ";
					if (stateField->GetReference()
							.GetDefinition<language::type::definition::property::Type::Grammar>()
							.ProductionRules.size() == actionElement.GetTarget())
					{
						output += stateField->GetAugmentedPR()->GetText();
					}
					else
					{
						output += stateField->GetReference()
									  .GetDefinition<
										  language::type::definition::property::Type::Grammar>()
									  .ProductionRules[actionElement.GetTarget()]
									  ->GetText();
					}
					break;
				case type::dparse::ActionType::Accept:
					output += "Accept";
					break;
				case type::dparse::ActionType::Reject:
					output += "Reject";
					break;
				}
				output += "\n";
			}
		}
	}

	return output;
}

std::string deamer::parser::generator::dparse::Print::GotoTable()
{
	std::string output;
	for (auto [state, map] : stateField->GetGotoTable().GetTable())
	{
		output += "State: " + std::to_string(stateField->GetIndexOfState(state));
		output += "\n";
		for (auto [lookahead, outState] : map)
		{
			output += "\tTransition: " + lookahead->Name + " ";
			output += std::to_string(outState);
			output += "\n";
		}
	}

	return output;
}

std::string deamer::parser::generator::dparse::Print::ParseState(State* state)
{
	bool first = true;
	std::string stateText = std::to_string((std::size_t)state);
	stateText += " [shape=record, label=\"{ State: ";
	stateText += std::to_string(stateField->GetIndexOfState(state));
	stateText += " | ";
	for (auto entry : state->GetEntries())
	{
		const auto entryText = ParseEntry(entry);
		if (first)
		{
			first = false;
		}
		else
		{
			stateText += " | ";
		}

		stateText += entryText;
	}
	stateText += " }\"]\n";

	for (auto& [transition, otherState] : state->GetTransitions())
	{
		stateText += std::to_string((std::size_t)state);
		stateText += " -> ";
		stateText += std::to_string((std::size_t)otherState);
		stateText += "[label=\"";
		if (transition->Type_ == language::type::definition::object::Type::NonTerminal)
		{
			stateText +=
				language::reference::LDO<language::type::definition::object::main::NonTerminal>(
					transition.GetRawPointer())
					->Name;
		}
		else if (transition->Type_ == language::type::definition::object::Type::Terminal)
		{
			stateText +=
				language::reference::LDO<language::type::definition::object::main::Terminal>(
					transition.GetRawPointer())
					->Name;
		}

		stateText += "\"]\n";
	}

	return stateText;
}

std::string deamer::parser::generator::dparse::Print::ParseEntry(const StateEntry& stateEntry)
{
	std::string entryText;
	const auto reverseLookup =
		language::reference::ReverseLookup<language::type::definition::object::main::NonTerminal>(
			&reference);
	if (stateEntry.GetProduction() == stateField->GetAugmentedPR())
	{
		entryText += stateField->GetAugmentedStart()->Name + " : ";
	}
	else
	{
		const auto nonTerminal = reverseLookup.Get(stateEntry.GetProduction()).GetObject();
		entryText += nonTerminal->Name + " : ";
	}

	if (stateEntry.GetProduction()->Tokens.empty())
	{
		entryText += ".";
	}
	else
	{
		bool addDot = false;
		std::size_t index = 0;
		for (language::reference::LDO<language::type::definition::object::Base, false> token :
			 stateEntry.GetProduction()->Tokens)
		{
			if (index == stateEntry.GetDotLocation())
			{
				addDot = true;
				entryText += ".";
			}
			entryText += " ";
			if (token->Type_ == language::type::definition::object::Type::NonTerminal)
			{
				entryText +=
					token.Promote<language::type::definition::object::main::NonTerminal>()->Name;
			}
			else if (token->Type_ == language::type::definition::object::Type::Terminal)
			{
				entryText +=
					token.Promote<language::type::definition::object::main::Terminal>()->Name;
			}
			index++;
		}
		if (!addDot)
		{
			entryText += ".";
		}
	}

	entryText += " ::";
	for (auto nextToken : stateEntry.NextToken())
	{
		entryText += " ";
		if (nextToken.Get() == nullptr)
		{
			entryText += "$";
		}
		else if (nextToken->Type_ == language::type::definition::object::Type::NonTerminal)
		{
			entryText +=
				nextToken.Promote<language::type::definition::object::main::NonTerminal>()->Name;
		}
		else if (nextToken->Type_ == language::type::definition::object::Type::Terminal)
		{
			entryText +=
				nextToken.Promote<language::type::definition::object::main::Terminal>()->Name;
		}
	}

	return entryText;
}
