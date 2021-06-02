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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_ANALYZERTYPE_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_ANALYZERTYPE_H

namespace deamer::language::type::definition::object::main::threat::analyzer
{
	/*! \enum Type
	 *
	 *  \brief The various types of threat analyzers.
	 *
	 *  \details This enum contains all threat analyzers available, so even custom ones.
	 *
	 *	\note The value of the value set in this enum is permanent, meaning you cannot move it
	 *around, this is to avoid differences in documentation and code.
	 *
	 *	This is why there are reserved spots for the Deamer core threat analyzers:
	 *	1-1024:     Reserved for Deamer Core
	 *	1025:       Separator
	 *	1026-limit: Custom or Deamer Core
	 */
	enum class Type
	{
		Unknown = 0,

		// Deamer core threat analyzers
		Deamer_Lexicon = 1,
		Deamer_Grammar = 2,
		Deamer_SymbolTable = 3,
		Deamer_Precedence = 4,
		Deamer_Associativity = 5,

		Separator = 1025,

	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_ANALYZERTYPE_H
