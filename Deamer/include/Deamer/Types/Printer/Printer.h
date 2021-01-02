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

#ifndef DEAMER_TYPES_PRINTER_PRINTER_H
#define DEAMER_TYPES_PRINTER_PRINTER_H

#include <string>

#include "Deamer/Types/Printer/ColorType.h"
#include "Deamer/Types/Printer/TextFont.h"

namespace deamer { namespace types {

	class Printer
	{
	protected:
		std::string GetAnsiTextColor(const ColorType& color) const;
		std::string GetAnsiBackgroundColor(const ColorType& color) const;
		std::string GetAnsiFont(const TextFont& font) const;
		void Output(const std::string& text, const ColorType textColor = ColorType::White, const ColorType backgroundColor = ColorType::Black, const TextFont font = TextFont::Standard) const;
	public:
		Printer() = default;
		virtual ~Printer() = default;
	};
}}

#endif //DEAMER_TYPES_PRINTER_PRINTER_H