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

#include "Deamer/Types/Printer/Printer.h"
#include <iostream>

void deamer::types::Printer::Output(const std::string& text, const ColorType textColor, const ColorType backgroundColor, const TextFont font) const
{
	std::cout << "\033[" << GetAnsiFont(font) << ";" << GetAnsiBackgroundColor(backgroundColor) << ";" << GetAnsiTextColor(textColor) << "m" << text << "\033[0m";
}

std::string deamer::types::Printer::GetAnsiTextColor(const ColorType& color) const
{
	switch (color)
	{
	case ColorType::Black:
		return "30";
	case ColorType::Red:
		return "31";
	case ColorType::Green:
		return "32";
	case ColorType::Yellow:
		return "33";
	case ColorType::Blue:
		return "34";
	case ColorType::Magenta:
		return "35";
	case ColorType::Cyan:
		return "36";
	case ColorType::White:
		return "37";
	case ColorType::BrightBlack:
		return "90";
	case ColorType::BrightRed:
		return "91";
	case ColorType::BrightGreen:
		return "92";
	case ColorType::BrightYellow:
		return "93";
	case ColorType::BrightBlue:
		return "94";
	case ColorType::BrightMagenta:
		return "95";
	case ColorType::BrightCyan:
		return "96";
	case ColorType::BrightWhite:
		return "97";
	}
	return "37";
}

std::string deamer::types::Printer::GetAnsiBackgroundColor(const ColorType& color) const
{
	switch (color)
	{
	case ColorType::Black:
		return "40";
	case ColorType::Red:
		return "41";
	case ColorType::Green:
		return "42";
	case ColorType::Yellow:
		return "43";
	case ColorType::Blue:
		return "44";
	case ColorType::Magenta:
		return "45";
	case ColorType::Cyan:
		return "46";
	case ColorType::White:
		return "47";
	case ColorType::BrightBlack:
		return "100";
	case ColorType::BrightRed:
		return "101";
	case ColorType::BrightGreen:
		return "102";
	case ColorType::BrightYellow:
		return "104";
	case ColorType::BrightBlue:
		return "104";
	case ColorType::BrightMagenta:
		return "105";
	case ColorType::BrightCyan:
		return "106";
	case ColorType::BrightWhite:
		return "107";
	}
	return "47";
}

std::string deamer::types::Printer::GetAnsiFont(const TextFont& font) const
{
	switch(font)
	{
	case TextFont::Bolt:
		return "1";
	case TextFont::Italic:
		return "2";
	case TextFont::Standard:
		return "3";
	}
	return "3";
}
