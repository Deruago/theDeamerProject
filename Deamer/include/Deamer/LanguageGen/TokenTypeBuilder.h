/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

 /*
  * TokenTypeBuilder is used to construct token types.
  * The output is thus a bitwise enum with the specified flags.
  */

#ifndef DEAMER_LANGUAGEGEN_TOKENTYPEBUILDER_H
#define DEAMER_LANGUAGEGEN_TOKENTYPEBUILDER_H
#include "Deamer/Types/BitwiseEnum.h"

namespace deamer
{
	enum class TokenType_t;
	
	class TokenTypeBuilder
	{
	private:
		BitwiseEnum<TokenType_t> tokenType;
	public:
		TokenTypeBuilder() = default;
		~TokenTypeBuilder() = default;

		void BuildTokenTypeForNode();
		void BuildTokenTypeForType();

		void SetTokenTypeStart();
		void SetTokenTypeGrouped();
		void SetTokenTypeVector();
		BitwiseEnum<TokenType_t> GetTokenType() const;
	};
}

#endif //DEAMER_LANGUAGEGEN_TOKENPERMISSIONBUILDER_H