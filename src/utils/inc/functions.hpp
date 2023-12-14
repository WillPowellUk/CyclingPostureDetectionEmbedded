#pragma once
#include <Arduino.h>
#include <vector>
#include "commonParams.hpp"

namespace utils
{
    void printFormattedFloat(float val, uint8_t leading, uint8_t decimals);
    void printPaddedInt16b(int16_t val);
    void printIMUPackets(std::vector<Common::IMUPackage> packets);
    void printEMGPackets(const std::vector<Common::EMGPackage>& packets);
} // namespace utils
