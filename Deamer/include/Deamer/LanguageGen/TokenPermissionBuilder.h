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

 /*
  * TokenTypeBuilder is used to construct token permissions.
  * The output is thus a bitwise enum with the specified flags.
  */

#ifndef DEAMER_LANGUAGEGEN_TOKENPERMISSIONBUILDER_H
#define DEAMER_LANGUAGEGEN_TOKENPERMISSIONBUILDER_H
#include "Deamer/Types/BitwiseEnum.h"

namespace deamer
{
	enum class TokenPermission_t;
	
	class TokenPermissionBuilder
	{
	private:
		BitwiseEnum<TokenPermission_t> tokenPermission;
	public:
		TokenPermissionBuilder() = default;
		~TokenPermissionBuilder() = default;

		void SetTypeToNode();
		void SetTypeToType();

		void SetAllPermissions();
		void SetAstCreation();
		void SetIgnoreToken();
		void SetDeleteToken();

		BitwiseEnum<TokenPermission_t> GetTokenPermission() const;
	};
}

#endif //DEAMER_LANGUAGEGEN_TOKENPERMISSIONBUILDER_H