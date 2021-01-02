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

#ifndef DEAMER_LANGUAGEGEN_TOKENCONSTANTS_H
#define DEAMER_LANGUAGEGEN_TOKENCONSTANTS_H

/*
This header file is to declare the constants used by the Token class and relateable classes that use the Token class.
The constants are in enums.
*/

namespace deamer
{
    typedef enum Token_Constants_s
    {
        MAX_ALLOWED_TOKENS_IN_RULE = 64,
        MAX_ALLOWED_RULES_FOR_TYPE = 64
    } Token_Constants;
}

#endif //DEAMER_LANGUAGEGEN_TOKENCONSTANTS_H