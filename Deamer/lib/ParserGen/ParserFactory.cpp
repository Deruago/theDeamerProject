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

#include "Deamer/ParserGen/ParserFactory.h"
#include "Deamer/ParserGen/ParserBuilder.h"
#include "Deamer/ParserGen/BisonBuilder/BisonBuilder.h"
#include "Deamer/ParserGen/DParseBuilder/DParseBuilder.h"

deamer::ParserBuilder* deamer::ParserFactory::MakeParser(ParserType_t ParserType_t, const LanguageDefinition* langDef) const
{
    switch(ParserType_t)
    {
        case ParserType_t::dparse:
            return new DParseBuilder(langDef);
        case ParserType_t::bison:
            return new BisonBuilder(langDef);
    }
    return nullptr;
}