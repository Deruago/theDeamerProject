#include "Deamer/LanguageAnalyzer/LanguageVisitor/LanguageDefinitionVisitor.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Node.h"

bool deamer::LanguageDefinitionVisitor::TokenIsInVisitedVector(const Token& visited_token)
{
	for (Token* token : Tokens)
		if (token == &visited_token)
			return true;
	return false;
}

void deamer::LanguageDefinitionVisitor::dispatch(Type& visited_type)
{
	if (!TokenIsInVisitedVector(visited_type))
	{
		first_visit(visited_type);
		depth++;
		Tokens.push_back(&visited_type);
		for (Rule* rule : visited_type.Rules)
			rule->Accept(*this);
		--depth;
	}
	else
	{
		visit(visited_type);
	}
}

void deamer::LanguageDefinitionVisitor::dispatch(Node& visited_type)
{
	if (!TokenIsInVisitedVector(visited_type))
	{
		first_visit(visited_type);
		Tokens.push_back(&visited_type);
	}
	else
		visit(visited_type);
}

void deamer::LanguageDefinitionVisitor::dispatch(Rule& visited_type)
{
	first_visit(visited_type);
	for (Token* token : visited_type.Tokens)
		token->Accept(*this);
}

void deamer::LanguageDefinitionVisitor::dispatch(Token& visited_type)
{
	if (visited_type.TokenPermission.has_flag(TokenPermission_t::node))
		dispatch(static_cast<Node&>(visited_type));
	else
		dispatch(static_cast<Type&>(visited_type));
}
