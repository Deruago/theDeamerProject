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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_LEXICON_SPECIALTYPE_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_LEXICON_SPECIALTYPE_H

namespace deamer::language::type::definition::object::main
{
	/*!	\enum SpecialType
	 *
	 *	\brief Enumerates all special variants of Terminals, that are available.
	 */
	enum class SpecialType
	{
		// A normal terminal
		Standard = 0,

		// Used to specify, if we should remove this terminal,
		// from the Terminal sequence.
		Delete = 1,

		// Used to specify that its value should be ignored.
		// And discard the terminal, after production rule deduction
		Ignore = 2,

		// Used to specify that its value should be ignored (has no value).
		NoValue = 4,

		// When encountering this terminal, crash the program
		Crash = 8,
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_LEXICON_SPECIALTYPE_H
