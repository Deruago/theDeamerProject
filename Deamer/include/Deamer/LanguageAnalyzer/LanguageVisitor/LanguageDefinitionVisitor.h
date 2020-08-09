/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -August 2020 Thimo B�hmer
 */

#ifndef DEAMER_LANGUAGEANALYZER_LANGUAGEVISITOR_LANGUAGEDEFINITIONVISITOR_H
#define DEAMER_LANGUAGEANALYZER_LANGUAGEVISITOR_LANGUAGEDEFINITIONVISITOR_H
#include "Deamer/Types/Visitor.h"

namespace deamer
{
	class Type;
	class Token;
	class Rule;
	class Node;
	
	class LanguageDefinitionVisitor : Visitor
	{
	private:
		virtual void visit(Type& visited_type);
		virtual void visit(Token& visited_type);
		virtual void visit(Rule& visited_type);
		virtual void visit(Node& visited_type);
	public:
		void dispatch(Type& visited_type);
		void dispatch(Token& visited_type);
		void dispatch(Rule& visited_type);
		void dispatch(Node& visited_type);
	};
}

#endif //DEAMER_LANGUAGEANALYZER_LANGUAGEVISITOR_LANGUAGEDEFINITIONVISITOR_H