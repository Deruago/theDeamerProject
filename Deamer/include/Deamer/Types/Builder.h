/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_TYPES_BUILDER_H
#define DEAMER_TYPES_BUILDER_H

/*
Defines abstract class Builder.
*/

#include <string>
#include <iostream>

namespace deamer
{
    class Builder
    {
        protected:
            std::string Output;
            std::string Directory;
            std::string FileName;
            Builder();
        public:
            void SetDirTarget(std::string dirName);
            void SetFileTarget(std::string fileName);
            std::string GetOutput() const; // Returns the output
            void WriteOutputToFile() const;
            void WriteOutputToFile(const std::string& file_name, const std::string& file_content) const;
    };
}

#endif //DEAMER_TYPES_BUILDER_H