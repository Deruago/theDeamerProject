#include "Deamer/LanguageAnalyzer/LanguageVisitor/LanguageDefinitionVisitor.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Node.h"

void deamer::LanguageDefinitionVisitor::dispatch(Type& visited_type)
{
	visit(visited_type);
	for(Rule* rule : visited_type.Rules)
		rule->Accept(*this);
}

void deamer::LanguageDefinitionVisitor::dispatch(Token& visited_type)
{
	if (visited_type.TokenPermission.has_flag(TokenPermission_t::node))
		visit(static_cast<Node&>(visited_type));
	else
		visit(static_cast<Type&>(visited_type));
}

void deamer::LanguageDefinitionVisitor::dispatch(Rule& visited_type)
{
	visit(visited_type);
	for(Token* token : visited_type.Tokens)
		token->Accept(*this);
}

void deamer::LanguageDefinitionVisitor::dispatch(Node& visited_type)
{
	visit(visited_type);
}
