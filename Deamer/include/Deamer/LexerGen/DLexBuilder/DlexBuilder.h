/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
 /*
  * Part of the DeamerProject.
  * For more information go to: https://github.com/Deruago/theDeamerProject
  */
#ifndef DEAMER_LEXERGEN_DLEXBUILDER_DLEXBUILDER_H
#define DEAMER_LEXERGEN_DLEXBUILDER_DLEXBUILDER_H

#include "Deamer/LexerGen/LexerBuilder.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"

namespace deamer
{
    class DlexBuilder : public LexerBuilder
    {
    public:
        DlexBuilder(const LanguageDefinition* langDef);
        void AddNode(Node* node) override;
        void AddIgnoreNode(Node* node) override;
        void AddDeleteNode(Node* node) override;
        bool FinishBuild() override;
        bool StartBuild() override;
    };
}

#endif //DEAMER_LEXERGEN_DLEXBUILDER_DLEXBUILDER_H
