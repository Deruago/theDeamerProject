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