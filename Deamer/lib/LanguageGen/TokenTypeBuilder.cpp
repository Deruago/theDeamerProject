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

#include "Deamer/LanguageGen/TokenTypeBuilder.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"

void deamer::TokenTypeBuilder::BuildTokenTypeForNode()
{
	tokenType.set_flag(TokenType_t::none);
}

void deamer::TokenTypeBuilder::BuildTokenTypeForType()
{
	tokenType.set_flag(TokenType_t::standard);
}

void deamer::TokenTypeBuilder::SetTokenTypeStart()
{
	tokenType.set_flag(TokenType_t::start);
}

void deamer::TokenTypeBuilder::SetTokenTypeGrouped()
{
	tokenType.set_flag(TokenType_t::grouped);
}

void deamer::TokenTypeBuilder::SetTokenTypeVector()
{
	tokenType.set_flag(TokenType_t::vector);
}

BitwiseEnum<deamer::TokenType_t> deamer::TokenTypeBuilder::GetTokenType() const
{
	return tokenType;
}
