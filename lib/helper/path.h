#pragma once

#include <stdint.h>

namespace helper
{

inline const char *getPathBase(const char *path)
{
    static constexpr char empty[] = "";

    if (path == nullptr)
    {
        return empty;
    }

    const char *lastSeparator = nullptr;

    for (const char *pathChar = path; *pathChar != '\0'; pathChar++)
    {
        if (*pathChar == '/' || *pathChar == '\\')
        {
            lastSeparator = pathChar;
        }
    }

    return lastSeparator ? (lastSeparator + 1) : path;
}

} // namespace helper