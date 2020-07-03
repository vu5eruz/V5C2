//==========================================================
//
//  V5C2  --  src/main.cpp
//
//==========================================================


#include "main.h"

#include <iostream>


namespace v5c2
{
    void main()
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
        "\n" << std::endl;

        std::cin.get();
    }
}


#if defined(V5C2_PLATFORM_LINUX) || defined(V5C2_PLATFORM_APPLE)

int main(int, char**)
{
    v5c2::main();
    return 0;
}

#elif defined(V5C2_PLATFORM_WINDOWS)

#define WIN32_LEAN_AND_MEAN

#include <sdkddkver.h>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int APIENTRY _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    ::AllocConsole();

    FILE* dummy{};
    ::_tfreopen_s(&dummy, _T("CONIN$"), _T("r"), stdin);
    ::_tfreopen_s(&dummy, _T("CONOUT$"), _T("w"), stdout);
    ::_tfreopen_s(&dummy, _T("CONOUT$"), _T("w"), stderr);

    std::cin.clear();
    std::cout.clear();
    std::cerr.clear();
    std::clog.clear();
    
    v5c2::main();

    ::FreeConsole();
    
    return 0;
}

#endif
