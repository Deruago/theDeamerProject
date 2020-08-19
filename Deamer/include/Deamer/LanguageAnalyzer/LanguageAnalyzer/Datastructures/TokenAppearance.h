/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -August 2020 Thimo B�hmer
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