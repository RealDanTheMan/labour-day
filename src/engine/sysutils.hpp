#ifndef SYS_UTILS_HPP_
#define SYS_UTILS_HPP_

#include <string>

namespace Engine
{
    class SysUtils
    {
        public:
        static bool FileExists(const std::string &filepath);
    };
}

#endif