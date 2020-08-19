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
        public:
            Generator() = default;
            virtual void DirTarget(std::string dirTarget);
            virtual void FileTarget(std::string fileTarget);
            virtual void Build();
            virtual void Write();
            bool DoesDirectoryExist(const std::string& Directory) const;
            bool CreateDirectory(const std::string& Directory) const;
            void CreateDirectoryIfNotExist(const std::string& Directory) const;
    };
}

#endif //DEAMER_TYPES_GENERATOR_H