/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
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