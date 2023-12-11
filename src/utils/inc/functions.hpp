#pragma once
#include <Arduino.h>

namespace utils
{
    void printFormattedFloat(float val, uint8_t leading, uint8_t decimals);
    void printPaddedInt16b(int16_t val);
} // namespace utils
