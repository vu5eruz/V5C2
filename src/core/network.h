//==========================================================
//
//  V5C2  --  src/core/network.h
//
//==========================================================


#include "core/main.h"

#ifndef V5C2_PLATFORM_WINDOWS
#   include <sys/socket.h>
#   include <netinet/in.h>
#   ifndef __CYGWIN__
#       include <netinet/tcp.h>
#   endif
#else
#   include <winsock2.h>
#   include <ws2tcpip.h>
#endif // !V5C2_PLATFORM_WINDOWS


namespace v5c2::core
{
    union SocketAddressType
    {
        struct sockaddr Sa;
        struct sockaddr_in SaIn;
        struct sockaddr_in6 SaIn6;
    };

#ifdef V5C2_PLATFORM_WINDOWS
    using SocketType = SOCKET;
#else
    using SocketType = int;
#endif

    void InitializeNetwork();

    void UninitializeNetwork();
}
