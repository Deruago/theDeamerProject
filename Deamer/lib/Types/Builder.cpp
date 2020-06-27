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

bool Builder::WriteOutputToFile()
{
    std::ostringstream oss0;
    oss0 << Builder::Directory << Builder::FileName;
    std::ofstream newParserFile;

    newParserFile.open(oss0.str(), std::ios_base::app);

    newParserFile << Builder::Output << '\n';
    
    newParserFile.close();

    return true;
}