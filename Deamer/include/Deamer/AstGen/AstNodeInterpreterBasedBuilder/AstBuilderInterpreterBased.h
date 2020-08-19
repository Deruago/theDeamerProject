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

#include "Deamer/AstGen/AstBuilder.h"
#include "Deamer/AstGen/AstEnumHeaderSectionFormatter.h"
#include "Deamer/AstGen/AstGlobalHeaderFormatter.h"
#include <string>

namespace deamer {
	class Token;
	class FileClassSection;
	namespace AstInterpreterBuilder {
	
		class AstBuilderInterpreterBased : public AstBuilder
		{
		private:
			AstEnumHeaderSectionFormatter enum_header_section_formatter_ = AstEnumHeaderSectionFormatter("", "");
			AstGlobalHeaderFormatter global_header_formatter_ = AstGlobalHeaderFormatter("", "");

			deamer::FileClassSection* GetAstNodeFileBuilderClass() const;
			std::string FillAstSourceFile(Token* token) const;
			std::string FillAstHeaderFile(Token* token) const;
		public:
			AstBuilderInterpreterBased(const std::string& directory, const std::string& language_name);

			void StartBuild() override;
			void Build(Node& node) override;
			void Build(Type& type) override;
			void FinishBuild() override;
	};
}}

#endif //DEAMER_ASTGEN_ASTNODEINTERPRETERBASEDBUILDER_ASTBUILDER_H