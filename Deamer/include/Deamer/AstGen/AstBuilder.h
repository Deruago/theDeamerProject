/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -August 2020 Thimo B�hmer
 */

#ifndef DEAMER_ASTGEN_ASTBUILDER_H
#define DEAMER_ASTGEN_ASTBUILDER_H

#include "Deamer/Types/Builder.h"

namespace deamer
{
	class Type;
	class Node;
	class Token;
	class FileClassSection;
	class AstBuilder : public Builder
	{
	private:
	protected:
		std::string language_name_;

		// Currently not used
		FileClassSection* _AstNode = nullptr; 
		FileClassSection* type_int = nullptr;
		FileClassSection* type_void = nullptr;
	public:
		AstBuilder(const std::string& directory, const std::string& language_name);
	    virtual ~AstBuilder() = default;

		virtual void StartBuild() = 0;
		virtual void Build(Type& type) = 0;
		virtual void Build(Node& node) = 0;
		virtual void FinishBuild() = 0;
	};
}

#endif //DEAMER_ASTGEN_ASTBUILDER_H