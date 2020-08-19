/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/Types/Builder.h"
#include <iostream>
#include <fstream>
#include <sstream>

deamer::Builder::Builder()
{
    
}

void deamer::Builder::SetDirTarget(std::string dirName)
{
    Directory = dirName;
}

void deamer::Builder::SetFileTarget(std::string fileName)
{
    FileName = fileName;
}

std::string deamer::Builder::GetOutput()
{
    return Output;
}

bool deamer::Builder::WriteOutputToFile()
{
    std::ostringstream oss0;
    oss0 << Directory << FileName;
    std::ofstream newParserFile;

    newParserFile.open(oss0.str(), std::ios_base::app);

    newParserFile << Output << '\n';
    
    newParserFile.close();

    return true;
}