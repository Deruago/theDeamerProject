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

std::string deamer::Builder::GetOutput() const
{
    return Output;
}

void deamer::Builder::WriteOutputToFile() const
{
    std::ostringstream file_path;
    file_path << Directory << FileName;
    std::ofstream new_file;

    new_file.open(file_path.str(), std::ios_base::app);

    new_file << Output << '\n';
    
    new_file.close();
}


void deamer::Builder::WriteOutputToFile(const std::string& file_name, const std::string& file_content) const
{
    std::ostringstream file_path;
    file_path << Directory << file_name;
    std::ofstream new_file;

    new_file.open(file_path.str(), std::ios_base::app);

    new_file << file_content << '\n';

    new_file.close();
}