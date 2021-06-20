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

#ifndef DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_STANDARD_MAIN_COLORIZATION_H
#define DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_STANDARD_MAIN_COLORIZATION_H

#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/Terminal.h"
#include "Deamer/Language/Analyzer/Main/Lexicon/Terminal.h"
#include "Deamer/Language/Generator/Definition/Property/Standard/Base.h"
#include "Deamer/Language/Reference/PropertyDefinition.h"
#include "Deamer/Language/Type/Definition/Object/Main/Colorization/ColorCombination.h"
#include "Deamer/Language/Type/Definition/Object/Main/Colorization/ColorGroup.h"
#include "Deamer/Language/Type/Definition/Object/Main/Colorization/ColorTheme.h"
#include "Deamer/Language/Type/Definition/Object/Main/Colorization/TerminalColor.h"
#include "Deamer/Language/Type/Definition/Object/Main/Colorization/TerminalPatternColor.h"
#include "Deamer/Language/Type/Definition/Property/Main/Colorization.h"
#include <regex>

namespace deamer::language::generator::definition::property::standard
{
	template<typename LanguageDefinitionType>
	class Colorization
		: public Base<LanguageDefinitionType, type::definition::property::main::Colorization,
					  type::definition::property::main::Lexicon,
					  type::definition::property::main::Grammar>
	{
	private:
		/*!	\property colorSymbolsEqual
		 *
		 *	\brief If set to true, all symbols such as: '(', ')', '{', '}', etc
		 *	will get the same color.
		 */
		bool colorSymbolsEqual = false;

		/*!	\property colorGroupsIndependently
		 *
		 *	\brief This will color is group uniquely.
		 *
		 *	\details The default algorithm will find the minimum colors.
		 *	This approach gives thus not a wide range of colors. Identifying groups using unique
		 *	colors, adds more colors.
		 */
		bool colorGroupsIndependently = false;

		constexpr static std::size_t equalSymbolMatchesColorGroup = 1025; // reserved for symbol matches

		struct DeducedTerminalColor
		{
			std::size_t colorId = 0;
			std::set<DeducedTerminalColor*> connections;
			language::reference::LDO<language::type::definition::object::main::Terminal> terminal;

			DeducedTerminalColor(
				language::reference::LDO<language::type::definition::object::main::Terminal>
					terminal_)
				: terminal(terminal_)
			{
			}

			void AddConnection(DeducedTerminalColor* connection)
			{
				if (connection == this)
				{
					return;
				}

				connections.insert(connection);
				connection->connections.insert(this);
			}

			std::set<std::size_t> GetLimitations() const
			{
				std::set<std::size_t> limitations;
				for (DeducedTerminalColor* terminalColor : connections)
				{
					if (!terminalColor->IsColorSet())
					{
						continue;
					}

					limitations.insert(terminalColor->colorId);
				}

				return limitations;
			}

			/*! \fn GetPossibleColor
			 *
			 *	\brief Finds the most suitable minimal color id.
			 *
			 *	\details Given the limitations in order, we check for the first unused spot.
			 *	This spot is a valid minimal color.
			 */
			std::size_t GetPossibleColor() const
			{
				std::set<std::size_t> limitations = GetLimitations();
				size_t minimalColorId = 1;

				for (const auto& colorLimitation : limitations)
				{
					if (colorLimitation != minimalColorId)
					{
						return minimalColorId;
					}

					minimalColorId += 1;
				}

				return minimalColorId;
			}

			bool IsColorSet() const
			{
				return colorId != 0;
			}

			/*!	\fn DetermineColor
			 *
			 *	\brief This will find the minimal coloring for the various terminals.
			 */
			std::size_t DetermineColor()
			{
				if (!IsColorSet()) // color is not set
				{
					const auto possibleColor = GetPossibleColor();
					colorId = possibleColor;

					for (DeducedTerminalColor* connection : connections)
					{
						connection->DetermineColor();
					}
				}

				return colorId;
			}
		};

		std::map<reference::LDO<type::definition::object::main::Terminal>, DeducedTerminalColor*>
			deducedColors;

		std::size_t maxColorId = 0;

		std::vector<type::definition::object::main::ColorGroup*> colorGroups;
		std::vector<type::definition::object::main::TerminalColor*> terminalColors;

	public:
		Colorization(LanguageDefinitionType* language_, bool colorSymbolsEqual_ = false)
			: standard::Base<LanguageDefinitionType, type::definition::property::main::Colorization,
							 type::definition::property::main::Lexicon,
							 type::definition::property::main::Grammar>(language_),
			  colorSymbolsEqual(colorSymbolsEqual_)
		{
		}
		~Colorization() override = default;

		void GenerateObjects() override
		{
			auto tmpLD = this->GetLanguageReference().GetTemporaryLanguageDefinition();
			const reference::PropertyDefinition<type::definition::property::Type::Lexicon,
												type::definition::property::Type::Grammar>
				tmp_reference(tmpLD.get());

			for (auto* const terminal :
				 tmp_reference.GetDefinition<type::definition::property::Type::Lexicon>().Terminals)
			{
				if (terminal->Special == type::definition::object::main::SpecialType::Crash ||
					terminal->Special == type::definition::object::main::SpecialType::Delete)
				{
					continue;
				}

				deducedColors[terminal] = new DeducedTerminalColor(terminal);
			}

			EqualizeSymbolColors();
			
			for (auto [terminal, deducedColor] : deducedColors)
			{
				analyzer::main::Terminal terminalAnalyzer(&tmp_reference, terminal);

				std::set<reference::LDO<type::definition::object::main::Terminal>> neighbors;
				terminalAnalyzer.GetAllPossibleNeighbouringTerminals(neighbors);

				for (const auto& neighbor : neighbors)
				{
					deducedColor->AddConnection(deducedColors.at(neighbor));
				}
			}

			for (auto& [terminal, deducedColor] : deducedColors)
			{
				deducedColor->DetermineColor();
				if (deducedColor->colorId > maxColorId)
				{
					maxColorId = deducedColor->colorId;
				}
			}

			for (std::size_t i = 1; i <= maxColorId; i++)
			{
				auto* const newColorGroup = new type::definition::object::main::ColorGroup(i);
				colorGroups.push_back(newColorGroup);
				this->AddObject(newColorGroup);
			}

			for (auto& [terminal, deducedColor] : deducedColors)
			{
				::deamer::language::type::definition::object::main::TerminalColor*
					newTerminalColor =
						new ::deamer::language::type::definition::object::main::TerminalColor(
					terminal.GetRawPointer(), colorGroups[deducedColor->colorId - 1]);
				terminalColors.push_back(newTerminalColor);
				this->AddObject(newTerminalColor);
			}

			AddThemes();

			for (auto [terminal, deducedColor] : deducedColors)
			{
				delete deducedColor;
			}
		}

		/*!	\fn Generate
		 *
		 *	\brief Generates the default colorization LPD for a given language.
		 *
		 *	\details The Colorization LPD uses a special algorithm which makes reasonable
		 *	syntax-highlighters.
		 */
		void GenerateDefinition() override
		{
			auto colorGroups =
				Base<LanguageDefinitionType, type::definition::property::main::Colorization,
					 type::definition::property::main::Lexicon,
					 type::definition::property::main::Grammar>::
					template GetObjects<type::definition::object::Type::ColorGroup>();
			auto colorCombinations =
				Base<LanguageDefinitionType, type::definition::property::main::Colorization,
					 type::definition::property::main::Lexicon,
					 type::definition::property::main::Grammar>::
					template GetObjects<type::definition::object::Type::ColorCombination>();
			auto colorThemes =
				Base<LanguageDefinitionType, type::definition::property::main::Colorization,
					 type::definition::property::main::Lexicon,
					 type::definition::property::main::Grammar>::
					template GetObjects<type::definition::object::Type::ColorTheme>();
			auto terminalColors =
				Base<LanguageDefinitionType, type::definition::property::main::Colorization,
					 type::definition::property::main::Lexicon,
					 type::definition::property::main::Grammar>::
					template GetObjects<type::definition::object::Type::TerminalColor>();
			auto terminalPatternColors =
				Base<LanguageDefinitionType, type::definition::property::main::Colorization,
					 type::definition::property::main::Lexicon,
					 type::definition::property::main::Grammar>::
					template GetObjects<type::definition::object::Type::TerminalPatternColor>();

			this->generatedDefinition = new type::definition::property::main::Colorization(
				colorGroups, colorCombinations, colorThemes, terminalColors, terminalPatternColors);
		}

	private:
		/*!	\fn EqualizeSymbolColors
		 *
		 *	\brief If colorSymbolsEqual is true, this function will equalize all symbols.
		 *
		 *	\details Equalizing holds that it will give the symbols the highest color-id
		 *	among the varies symbols. This ensures less prominent colors are given.
		 */
		void EqualizeSymbolColors()
		{
			if (!colorSymbolsEqual)
			{
				return;
			}

			for (auto& [terminal, deducedColor] : deducedColors)
			{
				if (DoesRegexOnlyMatchSpecificSymbol(terminal->Regex))
				{
					deducedColor->colorId = equalSymbolMatchesColorGroup;
				}
			}
		}

		bool DoesRegexOnlyMatchSpecificSymbol(const std::string& regex)
		{
			std::regex regex_compiled(regex);
			// these symbols are commonly refered as symbols. If the regex
			// matches one such symbol we can assume the regex is a symbol
			// But to know for sure we require user explicity.
			constexpr static auto symbols = {
				"{",  "}",	"[",  "]",	";",  ":",	 "*",	 "**", "^",	 "&",  "&&",
				"\"", "'",	"|",  "||", "(",  ")",	 ",",	 ".",  "<",	 "<=", "=<",
				">",  ">=", "=>", "=",	"==", "===", "====", "?",  "?!", "!?", "!",
				"$",  "#",	"@",  "+",	"++", "-",	 "--",	 "-=", "+=", "*=", "/="};
			for (const auto* symbol : symbols)
			{
				if (std::regex_match(symbol, regex_compiled))
				{
					return true;
				}
			}

			return false;
		}

		/*!	\fn GetAvailableColorGroup
		* 
		*	\brief This will return the first available colorgroup
		* 
		*	\detail The first available colorgroup can be calculated via "1 + colorgroups.size()".
		* 
		*	\warning Returns raw pointer. Will leak if not explicitly deleted.
		*/
		[[nodiscard]] type::definition::object::main::ColorGroup* GetAvailableColorGroup()
		{
			return new type::definition::object::main::ColorGroup(GetAvailableColorGroupID());
		}

		/*!	\fn GetAvailableColorGroupID
		 *
		 *	\brief This will return the first available colorgroup id
		 *
		 *	\detail The first available colorgroup can be calculated via "1 + colorgroups.size()".
		 */
		[[nodiscard]] std::size_t GetAvailableColorGroupID()
		{
			const std::size_t currentGroup = 1 + colorGroups.size();
			return currentGroup;
		}

		/*!	\fn AddThemes
		 *
		 *	\brief When called takes the current colorgroups and apply varies themes.
		 */
		void AddThemes()
		{
		}
	};
}

#endif // DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_STANDARD_MAIN_COLORIZATION_H
