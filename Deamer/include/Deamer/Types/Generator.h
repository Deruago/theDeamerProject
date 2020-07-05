/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_TYPES_GENERATOR_H
#define DEAMER_TYPES_GENERATOR_H

/*
Describes an Generator abstract class.
*/

#include <string>

namespace deamer
{
    class Generator
    {
        protected:
            Generator();
        public:
            virtual void DirTarget(std::string dirTarget) = 0;
            virtual void FileTarget(std::string fileTarget) = 0;
            virtual bool Build();
            virtual bool Write();
            bool DoesDirectoryExist(std::string* Directory);
            bool CreateDirectory(std::string* Directory);
            void CreateDirectoryIfNotExist(std::string* Directory);
    };
}

#endif //DEAMER_TYPES_GENERATOR_H