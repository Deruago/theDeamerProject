#ifndef DEAMER_TYPES_GENERATOR_H
#define DEAMER_TYPES_GENERATOR_H

/*
Describes an Generator abstract class.
*/

#include <string>

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

#endif //DEAMER_TYPES_GENERATOR_H