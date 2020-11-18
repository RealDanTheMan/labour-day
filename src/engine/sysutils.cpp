#include "sysutils.hpp"
#include <fstream>

using namespace Engine;

bool SysUtils::FileExists(const std::string &filepath)
{
    std::ifstream stream(filepath.c_str(), std::ios::in);
    if(stream.fail())
    {
        stream.close();
        return false;
    }

    stream.close();
    return true;
}