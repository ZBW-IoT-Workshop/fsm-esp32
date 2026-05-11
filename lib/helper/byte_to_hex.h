#pragma once

#include <cstdint>

namespace helper
{

static inline char *byte_to_hex(uint8_t byte, char out[3])
{
    static constexpr char hexDigits[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                                           '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    out[0] = hexDigits[byte >> 4];
    out[1] = hexDigits[byte & 0x0F];
    out[2] = '\0';

    return out;
}

} // namespace helper