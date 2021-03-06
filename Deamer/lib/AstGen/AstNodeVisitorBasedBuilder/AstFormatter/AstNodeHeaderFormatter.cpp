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

#include "Deamer/AstGen/AstNodeVisitorBasedBuilder/AstFormatter/AstNodeHeaderFormatter.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/TypeAnalyzer.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include "Deamer/Types/SmartPointer/BaseAutoPtr.h"


std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::MakeStringAllCaps(std::string cs) const
{
	std::string name_upper;
	for (char i : cs)
	{
		name_upper += toupper(i);
	}
	return name_upper;
}

deamer::AstVisitorBuilder::AstNodeHeaderFormatter::AstNodeHeaderFormatter(Token* token, std::string language_name) : AstFileFormatter::AstFileFormatter(token, language_name)
{
}

std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::MakeAstFile() const
{
	return MakeHeaderGuardBegin() +
		MakeIncludeSectionHeaderAstDependencies() +
		"\n" +
		MakeIncludeSectionHeaderSystemDependencies() +
		MakeSystemNamespace(
			MakeForwardDeclarationSectionHeaderSystemDependencies() +
			MakeSystemForwardDeclaration("AstVisitor")
		) +
		MakeHeaderNamespace(
			MakeHeaderClassDefinition()
		) +
		MakeHeaderGuardEnd();
}

std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::MakeHeaderGuardMacro() const
{
	return "ASTNODES_" + MakeStringAllCaps(MakeClassName(token_)) + "_H";
}

std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::MakeHeaderGuardBegin() const
{
	return "#ifndef " + MakeHeaderGuardMacro() + "\n" + "#define " + MakeHeaderGuardMacro() + "\n";
}

std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::MakeHeaderGuardEnd() const
{
	return "#endif //" + MakeHeaderGuardMacro() + "\n";
}

std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::MakeHeaderNamespace(const std::string& cs) const
{
	return "namespace " + language_name_ + " {\n" + cs + "}\n";
}

std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::MakeHeaderClassDefinition() const
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

std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::MakeHeaderPrivateSection() const
{
	return "private:\n";
}

std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::MakeHeaderProtectedSection() const
{
	return "protected:\n";
}

std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::MakeHeaderPublicSection() const
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

std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::MakeClassSubclass() const
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

std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::InheritFromBaseClassInClassDefinition(Token* token) const
{
	return "public " + MakeClassName(token);
}


std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::MakeHeaderSpecificConstructorPrototypes() const
{
	std::string constructors;
	if (!token_->TokenPermission.has_flag(TokenPermission_t::node))
	{
		Type* tmpType = static_cast<Type*>(token_);
		auto rules = TypeAnalyzer(*tmpType).GetVectorOfUniqueRulesApplyingIgnoredTokens();
		for (const BaseAutoPtr<Rule> rule : rules)
		{
			constructors += MakeHeaderPrototype(MakeSpecificConstructorPrototype(&rule.GetReferenceToItem()));
		}
	}
	return constructors;
}

std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::MakeHeaderPrototype(const std::string& prototype) const
{
	return MakeIndentation(1) + prototype + ";\n";
}

std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::MakeSystemRequiredFields() const
{
	return MakeHeaderField(language_name_ + "::AstEnum_t AstType = " + language_name_ + "::AstEnum_t::" + token_->TokenName);
}

std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::MakeSpecificConstructorFields() const
{
	std::string specific_constructor_fields;
	if (!token_->TokenPermission.has_flag(TokenPermission_t::node))
	{
		std::vector<TokenAppearance> token_appearances = TypeAnalyzer(*static_cast<Type*>(token_)).GetVectorOfMinimalAmountOfTokensUsedDefiningThisType();
		for (TokenAppearance token_appearance : token_appearances)
		{
			specific_constructor_fields += MakeFieldsFromTokenAppearance(token_appearance);
		}
	}
	return specific_constructor_fields;
}

std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::MakeFieldsFromTokenAppearance(
	const TokenAppearance& token_appearance) const
{
	std::string fields;
	for (unsigned i = 1; i <= token_appearance.token_count; i++)
		fields += MakeHeaderField(MakeClassFieldType(token_appearance) + "* " + MakeClassFieldName(token_appearance, i) + " = nullptr");

	return fields;
}

std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::MakeClassFieldName(const deamer::TokenAppearance& token_appearance,
	unsigned i) const
{
	return token_appearance.token->TokenName + std::to_string(i) + "_";
}

std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::MakeClassFieldType(const TokenAppearance& token_appearance) const
{
	if (token_appearance.token->TokenType.has_flag(TokenType_t::vector))
		return "std::vector<" + MakeClassName(token_appearance.token) + "*>";
	else
		return MakeClassName(token_appearance.token);
}

std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::MakeHeaderField(const std::string& cs) const
{
	return MakeIndentation(1) + cs + ";\n";
}

std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::MakeHeaderAstInformationPrototype() const
{
	return MakeHeaderPrototype(MakeClassName() + "(deamer::AstInformation* astInformation)");
}

std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::MakeHeaderGeneralPrototype() const
{
	return MakeHeaderPrototype(MakeClassName() + "(std::vector<deamer::AstNode*> astNodes)");
}

std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::MakeHeaderBasePrototype() const
{
	return MakeHeaderPrototype(MakeClassName() + "(bool isNode, std::string astNodeName)");
}

std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::MakeHeaderAstIdPrototype() const
{
	return MakeHeaderPrototype("unsigned int GetAstId() override");
}

std::string deamer::AstVisitorBuilder::AstNodeHeaderFormatter::MakeHeaderSystemPrototypes() const
{
	return MakeHeaderPrototype("void Accept(deamer::AstVisitor& ast_visitor)");
}