#pragma once
#include <vector>
#include <Arduino.h>

namespace Common
{
#pragma pack(push, 1)
    struct IMUPackage
    {
        float accX;
        float accY;
        float accZ;
        float gyrX;
        float gyrY;
        float gyrZ;
        float magX;
        float magY;
        float magZ;

        // Constructor
        IMUPackage(float _accX, float _accY, float _accZ, float _gyrX, float _gyrY, float _gyrZ, float _magX, float _magY, float _magZ)
            : accX(_accX), accY(_accY), accZ(_accZ), gyrX(_gyrX), gyrY(_gyrY), gyrZ(_gyrZ), magX(_magX), magY(_magY), magZ(_magZ)
        {
        }
    };
#pragma pack(pop)

#pragma pack(push, 1)
    struct EMGPackage
    {
        uint16_t signal;
    };
#pragma pack(pop)

    struct SDCardPackageIMUEMG
    {
    public:
        std::vector<unsigned long> timestamps;
        std::vector<std::vector<Common::IMUPackage>> imuPackets;
        std::vector<std::vector<Common::EMGPackage>> emgPackets;

        // Constructor
        SDCardPackageIMUEMG(const std::vector<unsigned long> &_timestamps,
                            const std::vector<std::vector<Common::IMUPackage>> &_imuPackets,
                            const std::vector<std::vector<Common::EMGPackage>> &_emgPackets)
            : timestamps(_timestamps), imuPackets(_imuPackets), emgPackets(_emgPackets)
        {
        }
    };

    struct SDCardPackageEMG
    {
    public:
        std::vector<unsigned long> timestamps;
        std::vector<std::vector<Common::EMGPackage>> emgPackets;

        // Constructor
        SDCardPackageEMG(const std::vector<unsigned long> &_timestamps,
                         const std::vector<std::vector<Common::EMGPackage>> &_emgPackets)
            : timestamps(_timestamps), emgPackets(_emgPackets)
        {
        }
    };

    struct SDCardPackageIMU
    {
    public:
        std::vector<unsigned long> timestamps;
        std::vector<std::vector<Common::IMUPackage>> imuPackets;

        // Constructor
        SDCardPackageIMU(const std::vector<unsigned long> &_timestamps,
                         const std::vector<std::vector<Common::IMUPackage>> &_imuPackets)
            : timestamps(_timestamps), imuPackets(_imuPackets)
        {
        }
    };
} // namespace Common
