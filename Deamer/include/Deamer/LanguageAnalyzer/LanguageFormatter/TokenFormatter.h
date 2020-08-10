/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -August 2020 Thimo B�hmer
 */

#ifndef DEAMER_LANGUAGEANALYZER_LANGUAGEFORMATTER_TOKENFORMATTER_H
#define DEAMER_LANGUAGEANALYZER_LANGUAGEFORMATTER_TOKENFORMATTER_H
#include <string>


namespace deamer
{
	class TokenFormatter
	{
	private:
	protected:
	public:
		TokenFormatter() = default;
		~TokenFormatter() = default;

		std::string MakeFunctionArgument();
		std::string MakeTypeCallAsClassField();
		std::string MakeTypeAsCtorInputVariable();
		std::string MakeConstructorTypeAssignment();
		std::string MakeTypeAsClassField();
	};
}

#endif //DEAMER_LANGUAGEANALYZER_LANGUAGEFORMATTER_TOKENFORMATTER_H