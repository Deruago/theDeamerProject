/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -June 2020 Thimo B�hmer
 * -July 2020 Thimo B�hmer
 */

#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/LexerGen/LexerBuilder.h"

deamer::LexerBuilder::LexerBuilder(const LanguageDefinition* languageDefinition) : langDef(languageDefinition)
{
}