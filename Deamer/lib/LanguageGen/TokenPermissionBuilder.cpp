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
}

void deamer::TokenPermissionBuilder::SetAstCreation()
{
}

void deamer::TokenPermissionBuilder::SetIgnoreToken()
{
	tokenPermission.set_flag(TokenPermission_t::ignore);
}

void deamer::TokenPermissionBuilder::SetDeleteToken()
{
	tokenPermission.set_flag(TokenPermission_t::ignore);
	tokenPermission.set_flag(TokenPermission_t::delete_);
}

BitwiseEnum<deamer::TokenPermission_t> deamer::TokenPermissionBuilder::GetTokenPermission() const
{
	return tokenPermission;
}
