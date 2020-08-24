/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -July 2020 Thimo B�hmer
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