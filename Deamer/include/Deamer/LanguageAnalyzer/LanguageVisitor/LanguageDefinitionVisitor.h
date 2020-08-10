/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
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
		virtual void visit(Type& visited_type) = 0;
		virtual void visit(Rule& visited_type) = 0;
		virtual void visit(Node& visited_type) = 0;
		virtual void last_visit(Type& type) = 0;
		virtual void last_visit(Node& node) = 0;
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