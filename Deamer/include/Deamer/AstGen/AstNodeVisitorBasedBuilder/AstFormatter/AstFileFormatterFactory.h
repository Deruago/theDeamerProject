/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_ASTGEN_ASTNODEINTERPRETERBASEDBUILDER_ASTFORMATTER_ASTFILEFORMATTERFACTORY_H
#define DEAMER_ASTGEN_ASTNODEINTERPRETERBASEDBUILDER_ASTFORMATTER_ASTFILEFORMATTERFACTORY_H
#include "Deamer/AstGen/AstFileFormatter.h"
#include <memory>

namespace deamer {
	enum class AstType;
	enum class AstFileType;
	namespace AstVisitorBuilder {

	class AstFileFormatterFactory
	{
	private:
	protected:
	public:
		AstFileFormatterFactory() = default;
		~AstFileFormatterFactory() = default;

		std::unique_ptr<AstFileFormatter> MakeAstFileFormatter(Token* token, const std::string& language_name, AstFileType ast_file_type) const;
	};
}}

#endif //DEAMER_ASTGEN_ASTNODEINTERPRETERBASEDBUILDER_ASTFORMATTER_ASTFILEFORMATTERFACTORY_H