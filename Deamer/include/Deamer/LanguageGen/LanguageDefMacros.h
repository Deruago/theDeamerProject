/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_LANGUAGEGEN_LANGUAGE_DEFMACROS_H
#define DEAMER_LANGUAGEGEN_LANGUAGE_DEFMACROS_H

#include "Deamer/LanguageGen/LanguageGen.h"

#define currentLangDef

#define GET_MACRO_NODE(_1,_2,_3,NAME,...) NAME
#define GET_MACRO_TYPE(_1,_2,NAME,...) NAME

#define newNode(...) GET_MACRO_NODE(__VA_ARGS__, newNode2, newNode1) (__VA_ARGS__)
#define newType(...) GET_MACRO_TYPE(__VA_ARGS__, newType2, newType1) (__VA_ARGS__)

#define NODE(...) newNode(__VA_ARGS__)
#define TYPE(...) newType(__VA_ARGS__)
#define RULE(type, ...) newRule(type, __VA_ARGS__)

#define IGNORENODE(node, regex) \
deamer::Node* node = currentLangDef.IgnoreNode(#node, regex);

#define newNode1(node, regex) \
deamer::Node* node = currentLangDef.CreateNode(#node, regex, true);

#define newNode2(node, regex, createAst) \
deamer::Node* node = currentLangDef.CreateNode(#node, regex, createAst);

#define newType1(type) \
deamer::Type* type = currentLangDef.CreateType(#type, true);

#define newType2(type, createAst) \
deamer::Type* type = currentLangDef.CreateType(#type, createAst);

#define newRule(type, ...) \
currentLangDef.CreateRule(type, {__VA_ARGS__});


#define EMPTY_RULE 

#endif //DEAMER_LANGUAGEGEN_LANGUAGE_DEFMACROS_H
