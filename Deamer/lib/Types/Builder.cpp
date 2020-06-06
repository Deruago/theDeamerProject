#include "Deamer/Types/Builder.h"
#include <iostream>
#include <fstream>
#include <sstream>

Builder::Builder()
{
    
}

void Builder::SetDirTarget(std::string dirName)
{
    Builder::Directory = dirName;
}

void Builder::SetFileTarget(std::string fileName)
{
    Builder::FileName = fileName;
}

std::string Builder::GetOutput()
{
    return Builder::Output;
}

void Builder::WriteOutputToFile()
{
    std::ostringstream oss;
    oss << Builder::Directory << Builder::FileName;
    std::ofstream outputFile(oss.str());

    outputFile << Builder::GetOutput();
}