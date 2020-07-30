#include "Deamer/LanguageGen/TokenTypeBuilder.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"

void deamer::TokenTypeBuilder::BuildTokenTypeForNode()
{
	tokenType.set_flag(TokenType_t::none);
}

void deamer::TokenTypeBuilder::BuildTokenTypeForType()
{
	tokenType.set_flag(TokenType_t::standard);
}

void deamer::TokenTypeBuilder::SetTokenTypeStart()
{
	tokenType.set_flag(TokenType_t::start);
}

void deamer::TokenTypeBuilder::SetTokenTypeGrouped()
{
	tokenType.set_flag(TokenType_t::grouped);
}

void deamer::TokenTypeBuilder::SetTokenTypeVector()
{
	tokenType.set_flag(TokenType_t::vector);
}

BitwiseEnum<deamer::TokenType_t> deamer::TokenTypeBuilder::GetTokenType() const
{
	return tokenType;
}
