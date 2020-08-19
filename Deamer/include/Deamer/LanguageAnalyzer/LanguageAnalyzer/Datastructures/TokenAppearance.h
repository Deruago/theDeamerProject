/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_DATASTRUCTURES_TOKENAPPEARANCE_H
#define DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_DATASTRUCTURES_TOKENAPPEARANCE_H

namespace deamer
{
	class Token;

	struct TokenAppearance
	{
		const Token* token;
		const unsigned token_count;
	};
}

#endif //DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_DATASTRUCTURES_TOKENAPPEARANCE_H