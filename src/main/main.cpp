//==========================================================
//
//  V5C2  --  src/main/main.cpp
//
//==========================================================


#include "main/main.h"

#include <iostream>


namespace v5c2::main
{
    void Main()
    {
        std::ios::sync_with_stdio(false);
        std::cout <<
        "V5C2\n"
        "  vu5eruz's chess for two\n"
        "  version " V5C2_VERSION " ("
#if defined(V5C2_PLATFORM_LINUX)
        "Linux"
#elif defined(V5C2_PLATFORM_APPLE)
        "Mac OS"
#elif defined(V5C2_PLATFORM_WINDOWS)
        "Windows"
#endif
        ")\n"
#ifdef V5C2_DEBUG
        "  debug release\n"
#endif // V5C2_DEBUG
        << std::endl;

        std::cin.get();
    }
}
