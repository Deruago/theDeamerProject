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

#ifndef DEAMER_LANGUAGEANALYZER_LANGUAGEVISITOR_LANGUAGEDEFINITIONVISITOR_H
#define DEAMER_LANGUAGEANALYZER_LANGUAGEVISITOR_LANGUAGEDEFINITIONVISITOR_H

#include "Deamer/Types/Visitable.h"
#include "Deamer/Types/Visitor.h"
#include <vector>

namespace deamer
{
	class Type;
	class Token;
	class Rule;
	class Node;	
	
	class LanguageDefinitionVisitor : Visitor
	{
	private:
		virtual void first_visit(Type& visited_type) = 0;
		virtual void first_visit(Rule& visited_type) = 0;
		virtual void first_visit(Node& visited_type) = 0;
		virtual void visit(Type& type) = 0;
		virtual void visit(Node& node) = 0;
	protected:
		std::vector<Token*> Tokens;
		bool TokenIsInVisitedVector(const Token& visited_token);
	public:
		unsigned depth = 0;
		void dispatch(Type& visited_type);
		void dispatch(Token& visited_type);
		void dispatch(Rule& visited_type);
		void dispatch(Node& visited_type);
	};
}

#endif //DEAMER_LANGUAGEANALYZER_LANGUAGEVISITOR_LANGUAGEDEFINITIONVISITOR_H