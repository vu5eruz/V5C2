//==========================================================
//
//  V5C2  --  src/core/main.cpp
//
//==========================================================


#include "client/main.h"
#include "core/main.h"
#include "core/network.h"

#include <exception>
#include <iostream>

#define STB_SPRINTF_IMPLEMENTATION 1
#include <stb_sprintf.h>


namespace v5c2::core
{
    namespace
    {
        void AppMain()
        {
            InitializeNetwork();
            client::InitializeClient();

            while (client::IsRunning())
            {
                client::DoCycle();
            }

            client::UninitializeClient();
            UninitializeNetwork();
        }
    }

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

        try
        {
            AppMain();
        }
        catch (const std::exception& Exc)
        {
            std::cerr <<
                "\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n"
                "\nUNCAUGHT EXCEPTION:\n\n    "
            <<  Exc.what() << "\n"
                "\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n"
            << std::endl;

            std::cin.get();
        }
    }
}
