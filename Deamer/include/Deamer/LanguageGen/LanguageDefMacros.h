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

#include "Deamer/LanguageGen/LanguageDefinitionBuilder.h"

#define currentLangDef
#define EMPTY_RULE 

#define GET_MACRO_NODE(_1,_2,_3,_4,NAME,...) NAME
#define GET_MACRO_TYPE(_1,_2,_3,NAME,...) NAME

#define newNode(...) GET_MACRO_NODE(__VA_ARGS__, newNode2, _1, newNode1) (__VA_ARGS__)
#define newType(...) GET_MACRO_TYPE(__VA_ARGS__, newType2, _1, newType1) (__VA_ARGS__)

#define NODE(...) GET_MACRO_NODE(__VA_ARGS__, newNode2, _1, newNode1) (__VA_ARGS__)
#define IGNORENODE(node, regex) deamer::Node* node = currentLangDef.AddIgnorableNode(#node, regex);

#define TYPE(...) GET_MACRO_TYPE(__VA_ARGS__, newType2, _1, newType1) (__VA_ARGS__)
#define STARTTYPE(start_type) deamer::Type* start_type = currentLangDef.AddStartType(#start_type);
#define GROUPEDTYPE(type) deamer::Type* type = currentLangDef.AddGroupedType(#type);
#define GROUPTOKENS(grouped_type, ...) deamer::Type* grouped_type = currentLangDef.AddTokensToGroupedType(grouped_type, {__VA_ARGS__});

#define RULE(type, ...) currentLangDef.AddRuleToType(type, {__VA_ARGS__});


#define newNode1(node, regex) \
deamer::Node* node = currentLangDef.AddNode(#node, regex);

#define newNode2(node, regex, token_type, token_permission) \
deamer::Node* node = currentLangDef.AddNode(#node, regex, token_type, token_permission);

#define newType1(type) \
deamer::Type* type = currentLangDef.AddType(#type);

#define newType2(type, token_type, token_permission) \
deamer::Type* type = currentLangDef.AddType(#type, token_type, token_permission);

#endif //DEAMER_LANGUAGEGEN_LANGUAGE_DEFMACROS_H
