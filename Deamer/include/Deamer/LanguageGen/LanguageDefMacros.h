#ifndef DEAMER_LANGUAGEGEN_LANGUAGE_DEFMACROS_H
#define DEAMER_LANGUAGEGEN_LANGUAGE_DEFMACROS_H

#include "Deamer/LanguageGen/LanguageGen.h"

#define currentLangGen

#define newNode(node, regex) \
Node* node = currentLangGen.CreateNode(#node, regex);

#define newType(type) \
Type* type = languageGen.CreateType(#type);

#define newRule(type, ...) \
languageGen.CreateRule(type, {__VA_ARGS__});


#endif //DEAMER_LANGUAGEGEN_LANGUAGE_DEFMACROS_H