#include "Deamer/Types/Generator.h"
#include <filesystem>
#include <sys/types.h>
#include <sys/stat.h>

deamer::Generator::Generator()
{
    
}

bool deamer::Generator::Build()
{
    return false;
}

bool deamer::Generator::Write()
{
    return false;
}

bool deamer::Generator::DoesDirectoryExist(std::string* Directory)
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

bool deamer::Generator::CreateDirectory(std::string* Directory)
{
    int status;
    status = mkdir(Directory->c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    return status;
}

void deamer::Generator::CreateDirectoryIfNotExist(std::string* Directory)
{
    if(!deamer::Generator::DoesDirectoryExist(Directory))
    {
        deamer::Generator::CreateDirectory(Directory);
    }
}