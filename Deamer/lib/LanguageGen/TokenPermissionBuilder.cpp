#include "Deamer/LanguageGen/TokenPermissionBuilder.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"

void deamer::TokenPermissionBuilder::SetTypeToNode()
{
	tokenPermission.set_flag(TokenPermission_t::node);
}

void deamer::TokenPermissionBuilder::SetTypeToType()
{
	tokenPermission.clear_flag(TokenPermission_t::node);
}

void deamer::TokenPermissionBuilder::SetAllPermissions()
{
	tokenPermission.set_flag(TokenPermission_t::ast);
}

void deamer::TokenPermissionBuilder::SetAstCreation()
{
	tokenPermission.set_flag(TokenPermission_t::ast);
}

void deamer::TokenPermissionBuilder::SetIgnoreToken()
{
	tokenPermission.set_flag(TokenPermission_t::ignore);
}

BitwiseEnum<deamer::TokenPermission_t> deamer::TokenPermissionBuilder::GetTokenPermission() const
{
	return tokenPermission;
}
