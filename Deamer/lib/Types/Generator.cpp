#include "Deamer/Types/Generator.h"
#include <filesystem>
#include <sys/types.h>
#include <sys/stat.h>

Generator::Generator()
{
    
}

bool Generator::Build()
{
    return false;
}

bool Generator::Write()
{
    return false;
}

bool Generator::DoesDirectoryExist(std::string* Directory)
{
    struct stat info;

    if(stat(Directory->c_str(), &info ) != 0 )
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

bool Generator::CreateDirectory(std::string* Directory)
{
    int status;
    status = mkdir(Directory->c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    return status;
}

void Generator::CreateDirectoryIfNotExist(std::string* Directory)
{
    if(!Generator::DoesDirectoryExist(Directory))
    {
        Generator::CreateDirectory(Directory);
    }
}