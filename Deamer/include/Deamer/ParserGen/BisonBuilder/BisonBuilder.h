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
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include <string>

namespace deamer
{
    class BisonBuilder : public ParserBuilder
    {
        std::string includePart;
        std::string tokenDeclarationPart;
        std::string typeDeclarationPart;
        std::string unionDeclarationPart;
        std::string ruleDeclarationPart;
        Type* curType;
        Type* firstType;
        bool IsFirstType;
        unsigned int curRuleSizeOfType;
        unsigned int currentRulesBuilt;
        void WriteRule(Rule* rule, std::ostringstream* oss) const;
        std::string CombineParserPartsIntoOnePart(std::ostringstream& ParserFunctions) const;
        void MakeParserErrorFunction(std::ostringstream& ParserFunctions) const;
        void MakeParserDestructor(std::ostringstream& extendedFunctionPart) const;
        void MakeParserConstructor(std::ostringstream& extendedFunctionPart) const;
        void MakeParseFileLocationFunction(std::ostringstream& extendedFunctionPart) const;
        void MakeParseFileFunction(std::ostringstream& extendedFunctionPart) const;
        void MakeParseTextFunction(std::ostringstream& extendedFunctionPart) const;
        virtual void WriteRuleModificationPart(Rule* rule, std::ostringstream* oss) const;
        bool CurrentTokenIsNode(deamer::Token* CurrentToken) const;
        bool CurrentTokenHasAnAstNode(deamer::Token* CurrentToken) const;
        bool CurrentTypeIsTheFirstType() const;
        void MakeArgumentReferenceVariable(std::ostringstream* oss, int& j) const;
        void MakeArgument(std::string LanguageName, std::ostringstream* oss, int& j, deamer::Token* CurrentToken) const;
        void AddFirstArgument(std::string LanguageName, deamer::Rule* rule, std::ostringstream* oss, int& j) const;
        void MakeNewAstNode(const std::string LanguageName, std::ostringstream* oss, int ArgumentCount,
                            deamer::Token* CurrentToken) const;
        void AddRestOfAllArguments(std::string LanguageName, deamer::Rule* rule, std::ostringstream* oss, int j) const;
        void MakeAstTree(std::string LanguageName, std::ostringstream* oss) const;
        void MakeAstNode(std::string LanguageName, std::ostringstream* oss) const;
        void MakeOutputCodeForAstTree(std::ostringstream* oss) const;
        void MakeRuleExecutionPart(std::string LanguageName, deamer::Rule* rule, std::ostringstream* oss) const;
        void MakeOutputCodeWhenNodeIsStartType(std::ostringstream* oss) const;
        void FormatTypeRulePart(deamer::Rule* rule, std::ostringstream* oss, std::string LanguageName) const;
        std::string MakeUnion() const;
        std::string MakeBeginningRuleDeclaration() const;
        std::string MakeInclude() const;
        public:
            BisonBuilder(LanguageDefinition* langDef);
            void AddNode(Node* node) override;
            void AddType(Type* type) override;
	        void AddCorrectNotationForNewRule(std::ostringstream& oss) const;
	        std::string FormatRule(deamer::Rule* rule) const;
	        void MakeRule(deamer::Rule* rule);
	        void AddRule(Rule* rule) override;
	        bool FinishBuild() override;
	        bool StartBuild() override;
    };
}

#endif //DEAMER_PARSERGEN_BISONBUILDER_H