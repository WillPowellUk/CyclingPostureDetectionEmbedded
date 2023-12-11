#pragma once

namespace Common
{   
    #pragma pack(push,1)
    struct ICMPackage
    {
        float accelX;
        float accelY;
        float accelZ;
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
    
} // namespace Common

