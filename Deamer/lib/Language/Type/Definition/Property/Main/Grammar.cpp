#include "Deamer/Language/Type/Definition/Property/Main/Grammar.h"

deamer::language::type::definition::property::main::Grammar::Grammar(
	std::vector<object::main::NonTerminal*> nonTerminals_, std::vector<object::main::ProductionRule*> productionRules_)
		:	Definition(Type::Grammar),
			NonTerminals(std::move(nonTerminals_)),
			ProductionRules(std::move(productionRules_))
{
}
