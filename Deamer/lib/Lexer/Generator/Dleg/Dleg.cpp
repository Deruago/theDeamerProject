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

#include "Deamer/Lexer/Generator/Dleg/Dleg.h"
#include "Deamer/Dregx/Regex.h"
#include "Deamer/File/Tool/Action/Builder.h"
#include "Deamer/Template/Lexer/Dleg/LexerHeader/LexerHeaderTemplate.h"
#include "Deamer/Template/Lexer/Dleg/LexerSourceTemplate.h"
#include <algorithm>
#include <array>
#include <chrono>
#include <utility>
#include <vector>

using namespace deamer::language::type::definition::property;

deamer::lexer::generator::dleg::Dleg::Dleg(ReferenceType reference_)
	: Base(tool::type::Tool::Dleg),
	  reference(reference_),
	  name(reference.GetDefinition<Type::Identity>().GetName()->value)
{
}

deamer::file::tool::Output deamer::lexer::generator::dleg::Dleg::Generate()
{
	std::chrono::system_clock::time_point start;
	if (reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsArgumentSet({tool::type::Tool::Dleg, "benchmark-time"}))
	{
		start = std::chrono::system_clock::now();
	}

	const auto Identity = reference.GetDefinition<Type::Identity>();
	const auto Lexicon = reference.GetDefinition<Type::Lexicon>();
	file::tool::Output output("Dleg");

	const auto lexerSource = file::tool::File("Dleg", "cpp", ConvertTransitionTableToCode(),
											  file::tool::GenerationLevel::Always_regenerate);
	auto lexerHeaderTemplate = templates::dleg::LexerHeaderTemplate();
	lexerHeaderTemplate.language_name_->Set(name);
	const auto lexerHeader = file::tool::File("Lexer", "h", lexerHeaderTemplate.GetOutput(),
											  file::tool::GenerationLevel::Always_regenerate);

	output.AddCMakeListsToExternal({ExternalCmake()});

	output.AddFileToExternal(lexerSource);
	output.AddFileToInclude(lexerHeader);

	if (reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsArgumentSet({tool::type::Tool::Dleg, "benchmark-time"}))
	{
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> diff = end - start;
		std::cout << diff.count() << "s\n";
	}

	return output;
}

std::string deamer::lexer::generator::dleg::Dleg::ConvertTransitionTableToCode()
{
	// The lex logic is as follows:
	// There is a transition table
	// Whenever we come into a sink, we output a Terminal if the previous state was accepting.
	// If the previous state was not accepting, throw an error or unknown token.
	auto dlegLexerTemplate = ::deamer::templates::dleg::LexerSourceTemplate();
	dlegLexerTemplate.language_name_->Set(name);
	auto transitions = ConstructAsciiTransitionTable();
	dlegLexerTemplate.state_count_->Set(std::to_string(transitions.size()));

	for (std::size_t i = 0; i < transitions.size(); i++)
	{
		dlegLexerTemplate.state_transition_entry_->variable_field_->Clear();
		const auto& currentStateEntry = transitions[i];
		const language::type::definition::object::main::Terminal* terminal =
			GetStrongestFlavor(std::get<2>(currentStateEntry));
		std::string flavor = "";
		if (terminal != nullptr)
		{
			flavor = terminal->Name;
		}

		const bool accepting = std::get<1>(currentStateEntry);
		bool allPointingToCurrentState = true;
		dlegLexerTemplate.state_index_->Set(std::to_string(i));
		for (std::size_t j = 0; j < std::get<0>(currentStateEntry).size(); j++)
		{
			const auto& outState = std::get<0>(currentStateEntry)[j];
			dlegLexerTemplate.out_state_->Set(std::to_string(outState));
			if (outState != i && outState != (transitions.size() - 1))
			{
				allPointingToCurrentState = false;
			}
			const char j_char = j;
			std::string j_string;
			j_string += j_char;
			dlegLexerTemplate.state_char_->Set(j_string);
			dlegLexerTemplate.state_transition_entry_->ExpandVariableField();
		}

		dlegLexerTemplate.state_name_entry_->Set(flavor);

		if (accepting)
		{
			dlegLexerTemplate.state_enumeration_->Set(dlegLexerTemplate.state_type_accept_);
		}
		else if (!accepting && allPointingToCurrentState)
		{
			dlegLexerTemplate.state_enumeration_->Set(dlegLexerTemplate.state_type_reject_);
		}
		else
		{
			dlegLexerTemplate.state_enumeration_->Set(dlegLexerTemplate.state_type_empty_);
		}

		if (terminal == nullptr)
		{
			dlegLexerTemplate.state_skip_value_->Set(dlegLexerTemplate.state_skip_default_);
			dlegLexerTemplate.state_id_entry_->Set(
				std::to_string(reference.GetDefinition<Type::Lexicon>().Terminals.size()));
		}
		else
		{
			switch (terminal->Special)
			{
			case language::type::definition::object::main::SpecialType::Standard:
				dlegLexerTemplate.state_skip_value_->Set(dlegLexerTemplate.state_skip_default_);
				break;
			case language::type::definition::object::main::SpecialType::Delete:
				dlegLexerTemplate.state_skip_value_->Set(dlegLexerTemplate.state_skip_delete_);
				break;
			case language::type::definition::object::main::SpecialType::Ignore:
				dlegLexerTemplate.state_skip_value_->Set(dlegLexerTemplate.state_skip_ignore_);
				break;
			case language::type::definition::object::main::SpecialType::NoValue:
				dlegLexerTemplate.state_skip_value_->Set(dlegLexerTemplate.state_skip_ignore_);
				break;
			case language::type::definition::object::main::SpecialType::Crash:
				// unsupported
				dlegLexerTemplate.state_skip_value_->Set(dlegLexerTemplate.state_skip_default_);
				break;
			}

			auto GetTerminalId = [&]() {
				// Gets index of terminal and converts it to string
				auto& terminals = reference.GetDefinition<Type::Lexicon>().Terminals;
				const auto iter = std::find(std::cbegin(terminals), std::cend(terminals), terminal);
				return std::to_string(iter - std::cbegin(terminals) +
									  1); // 0 == unknown thus offset 1
			};

			// ID logic
			dlegLexerTemplate.state_id_entry_->Set(GetTerminalId());
		}

		dlegLexerTemplate.state_name_->ExpandVariableField();
		dlegLexerTemplate.state_skip_->ExpandVariableField();
		dlegLexerTemplate.state_id_->ExpandVariableField();
		dlegLexerTemplate.state_type_->ExpandVariableField();
		dlegLexerTemplate.state_transition_->ExpandVariableField();
	}
	return dlegLexerTemplate.GetOutput();
}

std::vector<std::tuple<std::array<std::size_t, 256>, bool, std::set<std::string>>>
deamer::lexer::generator::dleg::Dleg::ConstructAsciiTransitionTable()
{
	const auto Lexicon = reference.GetDefinition<Type::Lexicon>();

	std::unique_ptr<deamer::dregx::Regex> lexer(nullptr);
	for (auto* terminal : Lexicon.Terminals)
	{
		if (lexer == nullptr)
		{
			lexer = std::make_unique<deamer::dregx::Regex>(terminal->Regex, terminal->Name);
		}
		else
		{
			// The Terminal Name is unique, thus it is used as identification flavor
			auto regex = deamer::dregx::Regex(terminal->Regex, terminal->Name);
			lexer->Or(regex);
		}
	}
	auto statemachine = lexer->GetStatemachine();
	statemachine->Minimize();
	const auto transitionTable = statemachine->ToTransitionTable();

	// There are 2 sinks:
	// Dregx Sink
	// Dleg Sink -> All transitions not covered by Dregx which lead to nothing go to Dleg Sink
	std::vector<std::tuple<std::array<std::size_t, 256>, bool, std::set<std::string>>>
		dlegTransitionTable(transitionTable.table.size() + 1);

	// ASCII Range (256)
	std::array<std::size_t, 256> defaultEntry{};
	for (std::size_t i = 0; i < 256; i++)
	{
		defaultEntry[i] = dlegTransitionTable.size() - 1; // Last State;
	}
	for (auto& i : dlegTransitionTable)
	{
		i = {defaultEntry, false, {}};
	}

	for (std::size_t state_index = 0; state_index < transitionTable.table.size(); state_index++)
	{
		auto currentEntry = transitionTable.table[state_index];

		for (auto [transition, state] : currentEntry)
		{
			const int alphabetIndex = static_cast<unsigned char>(transition[0]);
			std::get<0>(dlegTransitionTable[state_index])[alphabetIndex] = state;
		}
	}

	for (auto i = 0; i < transitionTable.table.size(); i++)
	{
		const auto currentAccept = transitionTable.acceptingState[i];
		const auto currentFlavor = transitionTable.flavorState[i];
		std::get<1>(dlegTransitionTable[i]) = currentAccept;
		std::get<2>(dlegTransitionTable[i]) = currentFlavor;
	}

	return dlegTransitionTable;
}

std::string deamer::lexer::generator::dleg::Dleg::ExternalCmake()
{
	return "set(source_files ./Dleg.cpp)\n" + name +
		   "_add_external_library(Dleg ${source_files})\n";
}

deamer::language::type::definition::object::main::Terminal*
deamer::lexer::generator::dleg::Dleg::GetStrongestFlavor(std::set<std::string> flavors)
{
	if (flavors.empty())
	{
		return nullptr;
	}

	for (auto terminal : reference.GetDefinition<Type::Lexicon>().Terminals)
	{
		if (flavors.find(terminal->Name) != flavors.end())
		{
			return terminal;
		}
	}

	throw std::logic_error("Dleg has encountered an Internal Error when parsing terminal flavors.");
}
