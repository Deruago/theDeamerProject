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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_TYPE_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_TYPE_H

namespace deamer::language::type::definition::object
{
	/*! \enum Type
	 *
	 *  \brief This enum lists all the different language definition object types.
	 *
	 *	\note You may not depend on the value of some enumeration.
	 *	However, 0 is reserved for unknown enumerations.
	 */
	enum class Type
	{
		Unknown = 0,
		Base,

		// Associativity
		AssociativityType,
		ObjectAssociativity,



		// AstOptimization



		// AstTranslation



		// Colorization
		Color,
		ColorCombination,
		ColorGroup,
		ColorTheme,
		TerminalColor,
		TerminalPatternColor,



		// Documentation



		// Formatting



		// Generation
		Generate,
		GenerateArgument,
		Integrate,
		OSTarget,



		// Grammar
		NonTerminal,
		NonTerminalAbstraction,
		ProductionRule,



		// Identity
		Name,



		// Lexicon
		SpecialType,
		Terminal,



		// OOPSyntax
		OopConceptLink,
		OopConceptMember,
		OopConceptMemberType,
		OopEncapsulation,
		OopLink,
		OopSyntaxScope,



		// Precedence
		ObjectPrecedence,



		// Semantic



		// Threat
		Threat,



	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_TYPE_H
