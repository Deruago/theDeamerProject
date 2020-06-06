#ifndef DEAMER_TYPES_BUILDER_H
#define DEAMER_TYPES_BUILDER_H

/*
Defines abstract class Builder.
*/

#include <string>
#include <iostream>

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
        std::string GetOutput(); // Returns the output
        void WriteOutputToFile();
};

#endif //DEAMER_TYPES_BUILDER_H