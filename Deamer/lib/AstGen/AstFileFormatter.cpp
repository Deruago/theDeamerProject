/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#include "Deamer/AstGen/AstFileFormatter.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/TypeAnalyzer.h"
#include <vector>

deamer::AstFileFormatter::AstFileFormatter(Token* token, std::string& language_name)
{
	token_ = token;
    language_name_ = language_name;
}

std::string deamer::AstFileFormatter::MakeIncludeSectionSourceClassDefinitionDependency() const
{
    return AstClassDefinitionClassDependency();
}

std::string deamer::AstFileFormatter::AstClassDefinitionClassDependency() const
{
    return MakeIncludeHeader(MakeClassName(token_));
}

std::string deamer::AstFileFormatter::AstTreeClassDefinitionClassDependency() const
{
    return MakeIncludeHeader(MakeClassName(token_));
}

std::string deamer::AstFileFormatter::AstNodeClassDefinitionClassDependency() const
{
    return MakeIncludeHeader(MakeClassName(token_));
}

std::string deamer::AstFileFormatter::MakeIncludeSectionSourceSystemDependencies() const
{
    std::string include_system_headers = MakeSystemIncludeHeader("Deamer/AstGen/AstNode") +
							             MakeSystemIncludeHeader("Deamer/AstGen/AstInformation") +
	                                     MakeSystemStandardLibraryIncludeHeader("vector");
    return include_system_headers;
}

std::string deamer::AstFileFormatter::MakeIncludeSectionHeaderSystemDependencies() const
{
    return  MakeSystemIncludeHeader("Deamer/AstGen/AstNode") +
	        MakeSystemIncludeHeader("Deamer/AstGen/AstInformation") +
	        MakeIncludeHeader("AstEnum") +
	        MakeSystemStandardLibraryIncludeHeader("vector");
}

std::string deamer::AstFileFormatter::MakeForwardDeclarationSectionHeaderSystemDependencies() const
{
    return "";
}

std::string deamer::AstFileFormatter::MakeIncludeSectionSourceAstDependencies() const
{
    std::string tmpHeaderIncludes;
    if (!token_->TokenPermission.has_flag(TokenPermission_t::node))
    {
        Type* tmpType = static_cast<Type*>(token_);
        const std::vector<Token*> unique_tokens = TypeAnalyzer(*tmpType).GetVectorOfUniqueTokensDefiningThisType();
        for (Token* token_unique : unique_tokens)
            if (token_unique != token_)
                tmpHeaderIncludes += MakeIncludeHeader(MakeClassName(token_unique));
    }
    return tmpHeaderIncludes;
}

std::string deamer::AstFileFormatter::MakeIncludeSectionHeaderAstDependencies() const
{
    std::string tmpHeaderIncludes;
    for (Token* base_token : token_->BaseTokens)
            tmpHeaderIncludes += MakeIncludeHeader(MakeClassName(base_token));

	return tmpHeaderIncludes;
}

std::string deamer::AstFileFormatter::MakeForwardDeclaration(deamer::Token* token_unique) const
{
	return MakeSystemForwardDeclaration(MakeClassName(token_unique));
}

std::string deamer::AstFileFormatter::MakeSystemForwardDeclaration(const std::string& class_name) const
{
    return MakeIndentation(0) + "class " + class_name + ";\n";
}

std::string deamer::AstFileFormatter::MakeForwardDeclarationSectionHeaderAstDependencies() const
{
    std::string tmpHeaderIncludes;
	
    if (!token_->TokenPermission.has_flag(TokenPermission_t::node))
    {
        Type* tmpType = static_cast<Type*>(token_);
        const std::vector<Token*> unique_tokens = TypeAnalyzer(*tmpType).GetVectorOfUniqueTokensDefiningThisType();
        for (Token* token_unique : unique_tokens)
            if (token_unique != token_)
                tmpHeaderIncludes += MakeForwardDeclaration(token_unique);
    }
    return tmpHeaderIncludes;
}

std::string deamer::AstFileFormatter::MakeIndent() const
{
    std::string indent_str;
    for (unsigned i = 0; i < indent_size; i++)
    {
        indent_str += ' ';
    }
    return indent_str;
}

std::string deamer::AstFileFormatter::MakeIndentation() const
{
    std::string indentation;
    for (unsigned i = 0; i < depth; i++)
    {
        indentation += MakeIndent();
    }
    return indentation;
}

std::string deamer::AstFileFormatter::MakeIndentation(unsigned depth_) const
{
    std::string indentation;
    for (unsigned i = 0; i < depth_; i++)
    {
        indentation += MakeIndent();
    }
    return indentation;
}

std::string deamer::AstFileFormatter::MakeIncludeHeader(const std::string& header_path) const
{
    return "#include \"" + header_path + ".h\"\n";
}

std::string deamer::AstFileFormatter::MakeSystemIncludeHeader(const std::string& header_path) const
{
    return "#include <" + header_path + ".h>\n";
}

std::string deamer::AstFileFormatter::MakeSystemNamespace(const std::string& cs) const
{
    return "namespace deamer {\n" + cs + "}\n";
}

std::string deamer::AstFileFormatter::MakeSystemStandardLibraryIncludeHeader(const std::string& header_path) const
{
    return "#include <" + header_path + ">\n";
}

std::string deamer::AstFileFormatter::MakeConstructorNameWithLanguageNamespace() const
{
    return language_name_ + "::" + MakeConstructorName();
}

std::string deamer::AstFileFormatter::MakeConstructorName() const
{
    return MakeClassName() + "::" + MakeClassName();
}

std::string deamer::AstFileFormatter::MakeClassName() const
{
    return MakeClassName(token_);
}

std::string deamer::AstFileFormatter::MakeClassName(const Token* token) const
{
    if (token->TokenType.has_flag(TokenType_t::start))
        return "AstTree_" + token->TokenName;
    else
        return "AstNode_" + token->TokenName;
}


std::string deamer::AstFileFormatter::MakeConstructorFunctionArgumentsFromProductionRule(Rule* rule) const
{
    std::string constructor_arguments;
    std::vector<Token*> track_visited_tokens;
    unsigned i = 0;
    for (Token* token : rule->Tokens)
    {
        if (token->TokenPermission.has_flag(TokenPermission_t::ignore) || token_ == token)
            continue;
        track_visited_tokens.push_back(token);
        if (i == 0)
            constructor_arguments += MakeConstructorArgumentFromToken(token, track_visited_tokens);
        else
            constructor_arguments += ", " + MakeConstructorArgumentFromToken(token, track_visited_tokens);
        i++;
    }
    return constructor_arguments;
}

std::string deamer::AstFileFormatter::MakeConstructorArgumentFromToken(Token* token, const std::vector<Token*>&
    visited_tokens) const
{
    const unsigned count_token = CountTokenInVector(token, visited_tokens);
    if (token->TokenType.has_flag(TokenType_t::vector))
        return "std::vector<" + MakeClassName(token) + "*>* " + MakeArgumentNameOfType(token, count_token);
    else
        return MakeClassName(token) + "* " + MakeArgumentNameOfType(token, count_token);
}

std::string deamer::AstFileFormatter::MakeFieldNameOfType(const Token* token, const unsigned count_token) const
{
    return MakeArgumentNameOfType(token, count_token) + "_";
}

std::string deamer::AstFileFormatter::MakeArgumentNameOfType(const Token* token, const unsigned count_token) const
{
    if (token->TokenType.has_flag(TokenType_t::vector))
        return token->TokenName + std::to_string(count_token);
    else
        return token->TokenName + std::to_string(count_token);
}

unsigned deamer::AstFileFormatter::CountTokenInVector(deamer::Token* token,
    const std::vector<deamer::Token*>& visited_tokens) const
{
    unsigned token_count = 0;
    for (Token* visited_token : visited_tokens)
        if (visited_token == token)
            token_count++;
    return token_count;
}

std::string deamer::AstFileFormatter::IsTokenNodeString() const
{
    if (token_->TokenPermission.has_flag(TokenPermission_t::node))
        return "true";
    else
        return "false";
}

std::string deamer::AstFileFormatter::MakeGetAstIdPrototype() const
{
    return "unsigned int " + language_name_ + "::" + MakeClassName(token_) + "::GetAstId()";
}

std::string deamer::AstFileFormatter::MakeInterpreterFunctionPrototype() const
{
    return "void " + language_name_ + "::" + MakeClassName(token_) + "::Generate(deamer::AstContext& ast_context)";
}

std::string deamer::AstFileFormatter::MakeVisitorFunctionPrototype() const
{
    return "void " + language_name_ + "::" + MakeClassName(token_) + "::Accept(deamer::AstVisitor& ast_visitor)";
}

std::string deamer::AstFileFormatter::MakeSpecificConstructorPrototypeWithPath(deamer::Rule* rule) const
{
    const std::string ctor_function_name = MakeConstructorNameWithLanguageNamespace();
    const std::string ctor_function_arguments = MakeConstructorFunctionArgumentsFromProductionRule(rule);
    return ctor_function_name + "(" + ctor_function_arguments + ")";
}

std::string deamer::AstFileFormatter::MakeSpecificConstructorPrototype(deamer::Rule* rule) const
{
    const std::string ctor_function_name = MakeClassName();
    const std::string ctor_function_arguments = MakeConstructorFunctionArgumentsFromProductionRule(rule);
    return ctor_function_name + "(" + ctor_function_arguments + ")";
}

std::string deamer::AstFileFormatter::MakeSpecificConstructorPrototypeWithBaseConstructorImplementations(Rule* rule) const
{
    return MakeSpecificConstructorPrototypeWithPath(rule) + MakeCtorImplementationsForSpecificCtor();
}

std::string deamer::AstFileFormatter::MakeCtorImplementationsForSpecificCtor() const
{
    if (token_->BaseTokens.empty())
        return " : deamer::AstNode::AstNode(" + IsTokenNodeString() + ", \"" + token_->TokenName + "\")\n";

    unsigned i = 0;
    std::string CtorImplementation;
    for (Token* base_type : token_->BaseTokens)
    {
        if (i == 0)
            CtorImplementation += " : " + MakeClassName(base_type) + "(" + IsTokenNodeString() + ", \"" + token_->TokenName + "\")\n";
        else
            CtorImplementation += ", " + MakeClassName(base_type) + "(" + IsTokenNodeString() + ", \"" + token_->TokenName + "\")\n";
        i++;
    }

    return CtorImplementation;
}

std::string deamer::AstFileFormatter::MakeCtorImplementationsForGeneralCtor() const
{
    if (token_->BaseTokens.empty())
        return " : deamer::AstNode::AstNode(astNodes, " + IsTokenNodeString() + ", \"" + token_->TokenName + "\")\n";

    unsigned i = 0;
    std::string CtorImplementation;
    for (Token* base_type : token_->BaseTokens)
    {
        if (i == 0)
            CtorImplementation += " : " + MakeClassName(base_type) + "(astNodes)\n";
        else
            CtorImplementation += ", " + MakeClassName(base_type) + "(astNodes)\n";
        i++;
    }

    return CtorImplementation;
}

std::string deamer::AstFileFormatter::MakeStandardInterpreterTypeImplementation(const Token* token, const unsigned count_token) const
{
    return MakeIndentation(2) + MakeFieldNameOfType(token, count_token) + "->Generate(ast_context);\n";
}
std::string deamer::AstFileFormatter::MakeSpecificConstructors() const
{
    std::string constructors;
    if (!token_->TokenPermission.has_flag(TokenPermission_t::node))
    {
        Type* tmpType = static_cast<Type*>(token_);
        for (Rule* rule : TypeAnalyzer(*tmpType).GetVectorOfUniqueRulesApplyingIgnoredTokens())
        {
            constructors += MakeAstConstructorFunction(MakeSpecificConstructorPrototypeWithBaseConstructorImplementations(rule), MakeSpecificConstructorImplementation(rule));
        }
    }
    return constructors;
}

std::string deamer::AstFileFormatter::MakeSpecificConstructorImplementation(Rule* rule) const
{
    std::string specific_constructor_implementation;
    std::vector<Token*> track_visited_tokens;
    unsigned i = 0;
    for (Token* token : rule->Tokens)
    {
        if (token->TokenPermission.has_flag(TokenPermission_t::ignore) || token_ == token)
            continue;
        track_visited_tokens.push_back(token);
        const unsigned count_token = CountTokenInVector(token, track_visited_tokens);

        specific_constructor_implementation += MakeIndentation(1) + MakeFieldNameOfType(token, count_token) + " = " + MakeArgumentNameOfType(token, count_token) + ";\n";

        i++;
    }
    return specific_constructor_implementation;
}

std::string deamer::AstFileFormatter::MakeCtorImplementationsForAstInformation() const
{
    if (token_->BaseTokens.empty())
        return " : deamer::AstNode::AstNode(astInformation, " + IsTokenNodeString() + ", \"" + token_->TokenName + "\")\n";

    unsigned i = 0;
    std::string CtorImplementation;
    for (Token* base_type : token_->BaseTokens)
    {
        if (i == 0)
            CtorImplementation += " : " + MakeClassName(base_type) + "(astInformation)\n";
        else
            CtorImplementation += ", " + MakeClassName(base_type) + "(astInformation)\n";
        i++;
    }

    return CtorImplementation;
}

std::string deamer::AstFileFormatter::MakeAstConstructorFunction(const std::string& constructor_prototype) const
{
    return MakeFunction(constructor_prototype);
}

std::string deamer::AstFileFormatter::MakeAstConstructorFunction(const std::string& constructor_prototype, const std::string& constructor_function_implementation) const
{
    return MakeFunction(constructor_prototype, constructor_function_implementation);
}

std::string deamer::AstFileFormatter::MakeAstConstructorAstInformationFunction(const std::string& constructor_prototype) const
{
    return MakeFunction(constructor_prototype + MakeCtorImplementationsForAstInformation());
}

std::string deamer::AstFileFormatter::MakeAstConstructorAstInformationFunction(const std::string& constructor_prototype, const std::string& constructor_function_implementation) const
{
    return MakeFunction(constructor_prototype + MakeCtorImplementationsForAstInformation(), constructor_function_implementation);
}

std::string deamer::AstFileFormatter::MakeAstConstructorGeneralFunction(const std::string& constructor_prototype) const
{
    return MakeFunction(constructor_prototype + MakeCtorImplementationsForGeneralCtor());
}

std::string deamer::AstFileFormatter::MakeAstConstructorGeneralFunction(const std::string& constructor_prototype, const std::string& constructor_function_implementation) const
{
    return MakeFunction(constructor_prototype + MakeCtorImplementationsForGeneralCtor(), constructor_function_implementation);
}

std::string deamer::AstFileFormatter::MakeAstConstructorSpecificFunction(const std::string& constructor_prototype) const
{
    return MakeFunction(constructor_prototype + MakeCtorImplementationsForSpecificCtor());
}

std::string deamer::AstFileFormatter::MakeAstConstructorSpecificFunction(const std::string& constructor_prototype, const std::string& constructor_function_implementation) const
{
    return MakeFunction(constructor_prototype + MakeCtorImplementationsForSpecificCtor(), constructor_function_implementation);
}

std::string deamer::AstFileFormatter::MakeEmptyFunction(const std::string& function_prototype) const
{
    return MakeFunction(function_prototype, "");
}

std::string deamer::AstFileFormatter::MakeCurrentTreeHeaderDeclaration() const
{
    if (token_->TokenType.has_flag(TokenType_t::start))
        return "    void SetCurrentTree(" + MakeClassName(token_) + "* new_ast_base_node);\n";
    return "";
}

std::string deamer::AstFileFormatter::MakeSetCurrentTreeHeaderDeclaration() const
{
    if (token_->TokenType.has_flag(TokenType_t::start))
        return "    static " + MakeClassName(token_) + "* currentTree;\n";
    return "";
}

std::string deamer::AstFileFormatter::MakeCurrentTreeDeclaration() const
{
    if (token_->TokenType.has_flag(TokenType_t::start))
        return language_name_ + "::" + MakeClassName(token_) + "* " + language_name_ + "::" + MakeClassName(token_) + "::currentTree;\n\n";
    return "";
}

std::string deamer::AstFileFormatter::MakeSetTree() const
{
    if (token_->TokenType.has_flag(TokenType_t::start))
        return  "void " + language_name_ + "::" + MakeClassName(token_) + "::SetCurrentTree(" + MakeClassName(token_) + "* new_ast_base_node)\n"
        "{\n"
        "    currentTree = new_ast_base_node;\n"
        "}\n";
    return "";
}

std::string deamer::AstFileFormatter::MakeFunction(const std::string& function_prototype) const
{
    return MakeEmptyFunction(function_prototype);
}

std::string deamer::AstFileFormatter::MakeFunction(const std::string& function_prototype, const std::string& function_implementation) const
{
    std::string reformatted_function_prototype;
    if (*function_prototype.end() != '\n')
        reformatted_function_prototype = function_prototype + '\n';
    else
        reformatted_function_prototype = function_prototype;

    return reformatted_function_prototype +
        MakeFunctionImplementation(function_implementation);
}

std::string deamer::AstFileFormatter::MakeFunctionImplementation(const std::string& cs) const
{
    return "{\n" +
        cs +
        "}\n"
        "\n";
}