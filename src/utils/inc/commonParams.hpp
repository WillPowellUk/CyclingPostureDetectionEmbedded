#pragma once

namespace Common
{   
    #pragma pack(push,1)
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
    };
    #pragma pack(pop)

    #pragma pack(push,1)
    struct EMGPackage
    {
        int signal;
    };
    #pragma pack(pop)

    #pragma pack(push,1)
    struct SDCardPackage
    {
        std::vector<unsigned long> timestamps;
        std::vector<std::vector<IMUPackage>> IMUPackage;
        std::vector<std::vector<EMGPackage>> EMGPackage;

        SDCardPackage(std::vector<unsigned long> ts,
                      std::vector<std::vector<Common::IMUPackage>> imu,
                      std::vector<std::vector<Common::EMGPackage>> emg)
            : timestamps(ts), IMUPackage(imu), EMGPackage(emg)
        {
        }
    };
    #pragma pack(pop)
    
} // namespace Common
