/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

/*
 * FileVariable is used to contain logic for variables.
 * You can declare variables using the VariableType and VariableName.
 * You can then use a FileInstructionSection to make instructions such as: b = a + c;
 */

#ifndef DEAMER_FILEBUILDER_FILEVARIABLE_H
#define DEAMER_FILEBUILDER_FILEVARIABLE_H
#include <string>

namespace deamer
{
	class FileVariableType;
	class StringBuilder;
	
	class FileVariable
	{
		private:
			FileVariableType* variableType;
			std::string variableName;
			bool _is_member;

			void AddOutputTypePath(StringBuilder* stringBuilder) const;
			void AddVariableName(StringBuilder* stringBuilder) const;
		protected:
		public:
			FileVariable(FileVariableType* varType, std::string varName, bool isMember);
			virtual ~FileVariable() = default;
			std::string GetOutput() const; // Returns full path. Thus including namespaces and classes. e.g int a, namespace_a::class_b c
			std::string GetVariableName() const; // Returns only the variable name
	};
}

#endif //DEAMER_FILEBUILDER_FILEVARIABLE_H