//==========================================================
//
//  V5C2  --  src/core/utils.h
//
//==========================================================


#ifndef V5C2_UTILS_H
#define V5C2_UTILS_H 1

#include "core/main.h"

#ifdef V5C2_PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <tchar.h>
#include <windows.h>
#endif // V5C2_PLATFORM_WINDOWS

#include <string>


namespace v5c2::core
{
#ifdef V5C2_PLATFORM_WINDOWS

    using TextString = std::basic_string<TCHAR>;
    using TextStringView = std::basic_string<TCHAR>;

    TextString TextFromUtf8(const std::string_view& Ansi);

    std::string Utf8FromText(const TextStringView& Text);

#endif // V5C2_PLATFORM_WINDOWS
}

#endif // !V5C2_UTILS_H
