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
        virtual bool Build();
        virtual bool Write();
};

#endif //DEAMER_TYPES_GENERATOR_H