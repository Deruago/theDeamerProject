#ifndef DEAMER_LANGUAGEGEN_LANGUAGE_DEFMACROS_H
#define DEAMER_LANGUAGEGEN_LANGUAGE_DEFMACROS_H

#include "Deamer/LanguageGen/LanguageGen.h"

#define currentLangDef

#define newNode(node, regex) \
Node* node = currentLangDef.CreateNode(#node, regex);

#define newType(type) \
Type* type = currentLangDef.CreateType(#type);

#define newRule(type, ...) \
currentLangDef.CreateRule(type, {__VA_ARGS__});

#define EMPTY_RULE 

#endif //DEAMER_LANGUAGEGEN_LANGUAGE_DEFMACROS_H