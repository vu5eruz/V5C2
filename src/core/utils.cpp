//==========================================================
//
//  V5C2  --  src/core/utils.h
//
//==========================================================


#include "core/main.h"
#include "core/utils.h"


namespace v5c2::core
{
#ifdef V5C2_PLATFORM_WINDOWS

    TextString TextFromUtf8(const std::string_view&)
    {
        // TODO(vu5eruz): UTF-8 to TCHAR conversion

        return TextString();
    }

    std::string Utf8FromText(const TextStringView&)
    {
        // TODO(vu5eruz): TCHAR to UTF-8 conversion

        return std::string();
    }

#endif // V5C2_PLATFORM_WINDOWS
}
