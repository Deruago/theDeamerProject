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

#include "Deamer/Lexer/Type/Flex/TerminalActionSection.h"

void deamer::lexer::type::flex::TerminalActionSection::AddTerminalAction(
	const TerminalAction& newTerminalAction)
{
	actions.push_back(newTerminalAction);
}

std::string deamer::lexer::type::flex::TerminalActionSection::Generate() const
{
	std::string generatedSection;

	for (const auto& action : actions)
	{
		generatedSection += action.Generate();
	}

	return generatedSection;
}
