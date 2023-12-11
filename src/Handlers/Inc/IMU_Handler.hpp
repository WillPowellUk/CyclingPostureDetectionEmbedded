#pragma once
#include <SparkFun_I2C_Mux_Arduino_Library.h>
#include "../../Drivers/Inc/ICM_20948.hpp"
#include <vector>

class IMUHandler
{
public:
    IMUHandler();

    bool init();
    std::vector<Common::ICMPackage> getPackets();
private:
    QWIICMUX mux;
    ICM20948 **imu; //Create pointer to a set of pointers to the icm class

};