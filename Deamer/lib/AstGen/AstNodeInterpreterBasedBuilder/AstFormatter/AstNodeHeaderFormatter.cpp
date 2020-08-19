/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#include "Deamer/AstGen/AstNodeInterpreterBasedBuilder/AstFormatter/AstNodeHeaderFormatter.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/TypeAnalyzer.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include <utility>

std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::MakeStringAllCaps(std::string cs) const
{
	std::string name_upper;
	for(char i : cs)
	{
		name_upper += toupper(i);
	}
	return name_upper;
}

deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::AstNodeHeaderFormatter(Token* token, std::string language_name) : AstFileFormatter::AstFileFormatter(token, language_name)
{
}

std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::MakeAstFile() const
{
	return MakeHeaderGuardBegin() +
		   MakeIncludeSectionHeaderAstDependencies() +
		   "\n" +
		   MakeIncludeSectionHeaderSystemDependencies() +
		   MakeSystemIncludeHeader("Deamer/AstGen/AstContext") +
		   MakeSystemNamespace(
			   MakeForwardDeclarationSectionHeaderSystemDependencies() +
			   MakeSystemForwardDeclaration("AstContext")
		   ) +
		   MakeHeaderNamespace(
			   MakeHeaderClassDefinition()
		   ) +
     	   MakeHeaderGuardEnd();
}

std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::MakeHeaderGuardMacro() const
{
	return "ASTNODES_" + MakeStringAllCaps(MakeClassName(token_)) + "_H";
}

std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::MakeHeaderGuardBegin() const
{
	return "#ifndef " + MakeHeaderGuardMacro() + "\n" + "#define " + MakeHeaderGuardMacro() + "\n";
}

std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::MakeHeaderGuardEnd() const
{
	return "#endif //" + MakeHeaderGuardMacro() + "\n";
}

std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::MakeHeaderNamespace(const std::string& cs) const
{
	return "namespace " + language_name_ + " {\n" + cs + "}\n";
}

std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::MakeHeaderClassDefinition() const
{
	return  "\n" +
			MakeForwardDeclarationSectionHeaderAstDependencies() +
	        "class " + MakeClassName() + MakeClassSubclass() + "\n" +
			"{\n" +
			MakeHeaderPrivateSection() +
			MakeHeaderProtectedSection() +
			MakeHeaderPublicSection() +
			"};\n";
}

std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::MakeHeaderPrivateSection() const
{
	return "private:\n";
}

std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::MakeHeaderProtectedSection() const
{
	return "protected:\n";
}

std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::MakeHeaderPublicSection() const
{
	return "public:\n" +
			MakeSystemRequiredFields() +
			MakeCurrentTreeHeaderDeclaration() + 
			'\n' +
			MakeSpecificConstructorFields() +
			'\n' +
			MakeHeaderAstIdPrototype() +
			MakeHeaderGeneralPrototype() +
			MakeHeaderBasePrototype() +
			MakeHeaderAstInformationPrototype() +
			'\n' +
			MakeHeaderSpecificConstructorPrototypes() +
			'\n' +
			MakeHeaderSystemPrototypes() +
			'\n' +
			MakeSetCurrentTreeHeaderDeclaration();
}

std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::MakeClassSubclass() const
{
	if (token_->BaseTokens.empty())
		return  " : public deamer::AstNode";

	std::string base_classes;
	unsigned base_classes_inherited = 0;
	for (auto base_token : token_->BaseTokens)
	{
		if (base_classes_inherited == 0)
			base_classes += " : ";
		else
			base_classes += ", ";
		
		base_classes += InheritFromBaseClassInClassDefinition(base_token);

		base_classes_inherited++;
	}

	return base_classes;
}

std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::InheritFromBaseClassInClassDefinition(Token* token) const
{
	return "public " + MakeClassName(token);
}


std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::MakeHeaderSpecificConstructorPrototypes() const
{
	std::string constructors;
	if (!token_->TokenPermission.has_flag(TokenPermission_t::node))
	{
		Type* tmpType = static_cast<Type*>(token_);
		for (Rule* rule : tmpType->Rules)
		{
			if (rule->RuleType.is_flag_not_set(RuleType_t::empty))
				constructors += MakeHeaderPrototype(MakeSpecificConstructorPrototype(rule));
		}
	}
	return constructors;
}

std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::MakeHeaderPrototype(const std::string& prototype) const
{
	return MakeIndentation(1) + prototype + ";\n";
}

std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::MakeSystemRequiredFields() const
{
	return MakeHeaderField(language_name_  + "::AstEnum_t AstType = " + language_name_  + "::AstEnum_t::" + token_->TokenName);
}

std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::MakeSpecificConstructorFields() const
{
	std::string specific_constructor_fields;
	if (!token_->TokenPermission.has_flag(TokenPermission_t::node))
	{
		std::vector<TokenAppearance> token_appearances = TypeAnalyzer(*static_cast<Type*>(token_)).GetVectorOfMinimalAmountOfTokensUsedDefiningThisType();
		for(TokenAppearance token_appearance : token_appearances)
		{
			specific_constructor_fields += MakeFieldsFromTokenAppearance(token_appearance);
		}
	}
	return specific_constructor_fields;
}

std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::MakeFieldsFromTokenAppearance(
	const TokenAppearance& token_appearance) const
{
	std::string fields;
	for(unsigned i = 1; i <= token_appearance.token_count; i++)
		fields += MakeHeaderField(MakeClassFieldType(token_appearance) + "* " + MakeClassFieldName(token_appearance, i));
	
	return fields;
}

std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::MakeClassFieldName(const deamer::TokenAppearance& token_appearance,
	unsigned i) const
{
	return token_appearance.token->TokenName + std::to_string(i) + "_";
}

std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::MakeClassFieldType(const TokenAppearance& token_appearance) const
{
	if (token_appearance.token->TokenType.has_flag(TokenType_t::vector))
		return "std::vector<" + MakeClassName(token_appearance.token) + "*>";
	else
		return MakeClassName(token_appearance.token);
}

std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::MakeHeaderField(const std::string& cs) const
{
	return MakeIndentation(1) + cs + ";\n";
}

std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::MakeHeaderAstInformationPrototype() const
{
	return MakeHeaderPrototype(MakeClassName() + "(deamer::AstInformation* astInformation)");
}

std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::MakeHeaderGeneralPrototype() const
{
	return MakeHeaderPrototype(MakeClassName() + "(std::vector<deamer::AstNode*> astNodes)");
}

std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::MakeHeaderBasePrototype() const
{
	return MakeHeaderPrototype(MakeClassName() + "(bool isNode, std::string astNodeName)");
}

std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::MakeHeaderAstIdPrototype() const
{
	return MakeHeaderPrototype("int GetAstId() override");
}

std::string deamer::AstInterpreterBuilder::AstNodeHeaderFormatter::MakeHeaderSystemPrototypes() const
{
	return MakeHeaderPrototype("void Generate(deamer::AstContext& ast_context)");
}