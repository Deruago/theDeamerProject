/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -June 2020 Thimo B�hmer
 * -July 2020 Thimo B�hmer
 */

#ifndef DEAMER_ASTGEN_ASTNODEINTERPRETERBASEDBUILDER_ASTBUILDER_H
#define DEAMER_ASTGEN_ASTNODEINTERPRETERBASEDBUILDER_ASTBUILDER_H

#include "Deamer/Types/Builder.h"
#include <string>
#include <fstream>
#include <vector>

namespace deamer
{
	class Token;
	class FileClassSection;

	class AstBuilder : public Builder
	{
	private:
		std::string languageName;
		FileClassSection* _AstNode;
		FileClassSection* type_int;
		FileClassSection* type_void;
		deamer::FileClassSection* GetAstNodeFileBuilderClass() const;

		std::string MakeSubclassesOfToken(Token* token) const;
		std::string MakeSubclassesForAstTree(Token* token) const;
		std::string MakeAstNodeConstructorPrototypes(Token* token) const;
		std::string MakeCtorFields(Token* token) const;
		std::string MakeAstTreeConstructorPrototypes(Token* token) const;

		void FillAstSourceFile(std::ofstream* astSourceFile, Token* token, std::string* defaultTokenName, bool isNode) const;
		void FillAstHeaderFile(std::ofstream* astHeaderFile, Token* token, std::string* defaultTokenName) const;
		void FillAstTreeSourceFile(std::ofstream* astSourceFile, Token* token, std::string* defaultTokenName, bool isNode) const;
		void FillAstTreeHeaderFile(std::ofstream* astHeaderFile, Token* token, std::string* defaultTokenName) const;
	public:
		AstBuilder();
		void CreateAstNode(Token* token, bool isNode); // Creates an AST Node and writes it to file.
		void CreateAstTree(Token* token, bool isNode) const;

		void CreateAstNodeEnumFile() const;
		void AppendAstNodeEnumFile(std::string TokenName) const;
		void FinishAstNodeEnumFile() const;

		void CreateGlobalHeaderFile() const;
		void AppendAstNodeHeaderFile(std::string TokenName) const;
		void AppendAstTreeHeaderFile(std::string TokenName) const;
		void FinishGlobalHeaderFile() const;

		void SetLanguageName(std::string languageName);
	};
}

#endif //DEAMER_ASTGEN_ASTNODEINTERPRETERBASEDBUILDER_ASTBUILDER_H