////////////////////////////////////////////////////////////
//
// V5C2 — Vu5eruz's Chess For Two
// Copyright (C) 2020 vu5eruz (undefined@disroot.org)
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////


#include "Main.h"
#include "Utils.h"

#ifdef V5C2_PLATFORM_UNIX
#include <sys/time.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#endif

#ifdef V5C2_PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif


namespace v5c2::utils
{

    void Sleep(unsigned int Duration)
    {
#if defined(V5C2_PLATFORM_WINDOWS)
        ::Sleep(Duration);
#elif defined(V5C2_PLATFORM_UNIX)
        struct timespec Req{}, Rem{};

        Req.tv_sec = static_cast<long>(Duration / 1000);
        Req.tv_nsec = static_cast<long>(Duration % 1000) * 1000000l;

        while (::nanosleep(&Req, &Rem) && (errno == EINTR))
        {
            Req = Rem;
        }
#else
#error "Implement v5c2::utils::Sleep for this platform"
#endif
    }

}
