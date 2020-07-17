/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

/*
 * Is used to contain logic for FileVariableTypes.
 * Types are basically things such as: int, string, char, std::vector<T>, namespace_a::class_b ect
 * This class is abstract and is used as an interface. As types are classes it uses a FileClassSection
 */

#ifndef DEAMER_FILEBUILDER_FILEVARIABLETYPE_H
#define DEAMER_FILEBUILDER_FILEVARIABLETYPE_H
#include <string>

namespace deamer
{
	class FileVariableType
	{
		private:
			FileVariableType* _variableTypeSection;
		protected:
		public:
			FileVariableType(FileVariableType* variableTypeSection);
			FileVariableType();
			virtual ~FileVariableType() = default;
			FileVariableType* GetFileVariableType() const;
			virtual std::string GetOutputType() const = 0; //Outputs Variabletype. e.g deamer::filebuilder::class_a
	};
}

#endif //DEAMER_FILEBUILDER_FILEVARIABLETYPE_H