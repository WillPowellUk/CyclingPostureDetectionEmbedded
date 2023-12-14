#include "../inc/functions.hpp"
#include <iostream>

namespace utils
{
    void printFormattedFloat(float val, uint8_t leading, uint8_t decimals)
    {
    float aval = abs(val);
    if (val < 0)
    {
        Serial.print("-");
    }
    else
    {
        Serial.print(" ");
    }
    for (uint8_t indi = 0; indi < leading; indi++)
    {
        uint32_t tenpow = 0;
        if (indi < (leading - 1))
        {
        tenpow = 1;
        }
        for (uint8_t c = 0; c < (leading - 1 - indi); c++)
        {
        tenpow *= 10;
        }
        if (aval < tenpow)
        {
        Serial.print("0");
        }
        else
        {
        break;
        }
    }
    if (val < 0)
    {
        Serial.print(-val, decimals);
    }

    else
    {
        Serial.print(val, decimals);
    }
    }

    void printPaddedInt16b(int16_t val)
    {
    if (val > 0)
    {
        Serial.print(" ");
        if (val < 10000)
        {
        Serial.print("0");
        }
        if (val < 1000)
        {
        Serial.print("0");
        }
        if (val < 100)
        {
        Serial.print("0");
        }
        if (val < 10)
        {
        Serial.print("0");
        }
    }
    else
    {
        Serial.print("-");
        if (abs(val) < 10000)
        {
        Serial.print("0");
        }
        if (abs(val) < 1000)
        {
        Serial.print("0");
        }
        if (abs(val) < 100)
        {
        Serial.print("0");
        }
        if (abs(val) < 10)
        {
        Serial.print("0");
        }
    }
    Serial.print(abs(val));
    }

    void printIMUPackets(std::vector<Common::IMUPackage> packets) 
    {
    for (Common::IMUPackage& packet : packets) {
        Serial.print("accX: ");
        Serial.println(packet.accX);
        Serial.print("accY: ");
        Serial.println(packet.accY);
        Serial.print("accZ: ");
        Serial.println(packet.accZ);
        Serial.print("gyrX: ");
        Serial.println(packet.gyrX);
        Serial.print("gyrY: ");
        Serial.println(packet.gyrY);
        Serial.print("gyrZ: ");
        Serial.println(packet.gyrZ);
        Serial.print("magX: ");
        Serial.println(packet.magX);
        Serial.print("magY: ");
        Serial.println(packet.magY);
        Serial.print("magZ: ");
        Serial.println(packet.magZ);
    }
    }

    #include <iostream>

    void printEMGPackets(const std::vector<Common::EMGPackage>& packets) 
    {
        for (const Common::EMGPackage& packet : packets) {
            Serial.print("signal: ");
            Serial.println(packet.signal);
        }
    }
} // namespace utils


