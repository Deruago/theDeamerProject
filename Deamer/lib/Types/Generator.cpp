/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/Types/Generator.h"
#include <filesystem>
#include <sys/types.h>
#include <sys/stat.h>

void deamer::Generator::DirTarget(std::string dirTarget)
{
}

void deamer::Generator::FileTarget(std::string fileTarget)
{
}

void deamer::Generator::Build()
{
}

void deamer::Generator::Write()
{
}

bool deamer::Generator::DoesDirectoryExist(const std::string& Directory) const
{
    struct stat info;

    if(stat(Directory.c_str(), &info ) != 0 )
    {
        return false;
    }
    else if(info.st_mode & S_IFDIR )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool deamer::Generator::CreateDirectory(const std::string& Directory) const
{
	const unsigned status = mkdir(Directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    return status;
}

void deamer::Generator::CreateDirectoryIfNotExist(const std::string& Directory) const
{
    if(!DoesDirectoryExist(Directory))
    {
        CreateDirectory(Directory);
    }
}