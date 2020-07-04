//==========================================================
//
//  V5C2  --  src/core/network.cpp
//
//==========================================================


#include "core/main.h"
#include "core/network.h"

#ifdef V5C2_PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#endif // V5C2_PLATFORM_WINDOWS

#include <stdexcept>

#include <stb_sprintf.h>


namespace v5c2::core
{
    void InitializeNetwork()
    {
#ifdef V5C2_PLATFORM_WINDOWS

        WSADATA WsaData{};
        switch (int Ret{ WSAStartup(0x0101, &WsaData) }; Ret)
        {
            case 0: // Success
                break;

            case WSASYSNOTREADY:
                throw std::runtime_error("WSAStartup failed: network not ready");

            case WSAVERNOTSUPPORTED:
            case WSAEINVAL:
                throw std::runtime_error("WSAStartup failed: requested version not supported");

            default:
            {
                char Message[64];
                stbsp_snprintf(Message, sizeof(Message), "WSAStartup failed: error code %i", Ret);
                throw std::runtime_error(Message);
            }
        }

#endif // V5C2_PLATFORM_WINDOWS
    }


    void UninitializeNetwork()
    {
#ifdef V5C2_PLATFORM_WINDOWS

        WSACleanup();

#endif // V5C2_PLATFORM_WINDOWS
    }
}
