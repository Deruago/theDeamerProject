/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_PARSERGEN_BISONBUILDER_H
#define DEAMER_PARSERGEN_BISONBUILDER_H

#include "Deamer/ParserGen/ParserBuilder.h"
#include "Deamer/ParserGen/BisonBuilder/BisonRuleSectionFormatter.h"
#include <string>

namespace deamer
{
	class Node;
	class Type;
	class Rule;
	class LanguageDefinition;
	
	class BisonBuilder : public ParserBuilder
	{
		BisonRuleSectionFormatter ruleFormatter = BisonRuleSectionFormatter("");
		std::string tokenDeclarationPart;
		std::string typeDeclarationPart;
		Type* firstType;
		bool IsTypeFirstType(Type* type) const;
	public:
		BisonBuilder(const LanguageDefinition* langDef);
		~BisonBuilder() = default;
		void AddNode(Node* node) override;
		void AddType(Type* type) override;
		void AddRule(Rule* rule) override;
		bool FinishBuild() override;
		bool StartBuild() override;
	};
}

#endif //DEAMER_PARSERGEN_BISONBUILDER_H