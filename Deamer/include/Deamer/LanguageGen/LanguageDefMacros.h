#ifndef DEAMER_LANGUAGEGEN_LANGUAGE_DEFMACROS_H
#define DEAMER_LANGUAGEGEN_LANGUAGE_DEFMACROS_H

#include "Deamer/LanguageGen/LanguageGen.h"

#define currentLangDef

#define GET_MACRO_NODE(_1,_2,_3,NAME,...) NAME
#define GET_MACRO_TYPE(_1,_2,NAME,...) NAME

#define newNode(...) GET_MACRO_NODE(__VA_ARGS__, newNode2, newNode1) (__VA_ARGS__)
#define newType(...) GET_MACRO_TYPE(__VA_ARGS__, newType2, newType1) (__VA_ARGS__)

#define newNode1(node, regex) \
Node* node = currentLangDef.CreateNode(#node, regex);

#define newNode2(node, regex, createAst) \
Node* node = currentLangDef.CreateNode(#node, regex);

#define newType1(type) \
Type* type = currentLangDef.CreateType(#type);

#define newType2(type, createAst) \
Type* type = currentLangDef.CreateType(#type, createAst);

#define newRule(type, ...) \
currentLangDef.CreateRule(type, {__VA_ARGS__});

#define EMPTY_RULE 

#endif //DEAMER_LANGUAGEGEN_LANGUAGE_DEFMACROS_H