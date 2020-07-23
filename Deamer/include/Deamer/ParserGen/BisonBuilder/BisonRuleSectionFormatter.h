/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -July 2020 Thimo Bohmer
 */

#ifndef DEAMER_PARSERGEN_BISONBUILDER_BISONRULEFORMATTER_H
#define DEAMER_PARSERGEN_BISONBUILDER_BISONRULEFORMATTER_H
#include <string>

namespace deamer
{
	class Token;
	class Rule;
	class Type;

	class BisonRuleSectionFormatter
	{
	private:
		std::string language_name_;
		std::string ruleDeclarationPart;
		Type* currentType;
		unsigned int curRuleSizeOfType;
		unsigned int CurrentLineNumber;
		Type* firstType;

		bool CurTypeIsFirstType() const;
	public:
		BisonRuleSectionFormatter(const std::string& lang_name);
		void CurrentType();
		void AddType(Type*& type);
		void ResetTypeInformation(Type*& type);
		std::string GetFormattedRuleSection() const;
		void AddRule(Rule* rule);
		void AddFirstType(Type*& type);
		void MakeType(deamer::Type*& type);
		void EndLastType();
		//std::string AddGroupedRule();
	};
}

#endif //DEAMER_PARSERGEN_BISONBUILDER_BISONRULEFORMATTER_H