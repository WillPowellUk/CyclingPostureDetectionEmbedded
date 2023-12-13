#include "../Inc/ICM_20948.hpp"
#include "../../Settings/Pinout.h"
#include "../../Settings/Settings.h"
#include "../../Utils/inc/functions.hpp"
#include <Wire.h>


bool ICM20948::init() 
{    
    //icm.enableDebugging(); // Uncomment this line to enable helpful debug messages on Serial

    bool initialized = false;
    while (!initialized)
    {
        icm.begin(Wire, Pinout::IMU::AD0_VAL);

        if (icm.status != ICM_20948_Stat_Ok)
        {
            Serial.println("Could not connect to ICM_20948, retrying in 0.5s");
            delay(500);
        }
        else initialized = true; 
    }

    return true;
}

Common::IMUPackage ICM20948::getPacket() 
{
    while (!icm.dataReady())
    {
        Serial.println("Waiting for  imu data");
        delay(500);
    }

    icm.getAGMT(); // updates readings from the ICM20948
    #ifdef DEBUG        
    printRawData(); 
    #endif
    Common::IMUPackage package(icm.accX(), icm.accY(), icm.accZ(), icm.gyrX(), icm.gyrY(), icm.gyrZ(), icm.magX(), icm.magY(), icm.magZ());

    return package;
}

void ICM20948::printRawData()
{
  Serial.print("RAW. Acc [ ");
  utils::printPaddedInt16b(icm.agmt.acc.axes.x);
  Serial.print(", ");
  utils::printPaddedInt16b(icm.agmt.acc.axes.y);
  Serial.print(", ");
  utils::printPaddedInt16b(icm.agmt.acc.axes.z);
  Serial.print(" ], Gyr [ ");
  utils::printPaddedInt16b(icm.agmt.gyr.axes.x);
  Serial.print(", ");
  utils::printPaddedInt16b(icm.agmt.gyr.axes.y);
  Serial.print(", ");
  utils::printPaddedInt16b(icm.agmt.gyr.axes.z);
  Serial.print(" ], Mag [ ");
  utils::printPaddedInt16b(icm.agmt.mag.axes.x);
  Serial.print(", ");
  utils::printPaddedInt16b(icm.agmt.mag.axes.y);
  Serial.print(", ");
  utils::printPaddedInt16b(icm.agmt.mag.axes.z);
  Serial.print(" ], Tmp [ ");
  utils::printPaddedInt16b(icm.agmt.tmp.val);
  Serial.print(" ]");
  Serial.println();
}

void ICM20948::printFormattedData()
{
  Serial.print("Scaled. Acc (mg) [ ");
  utils::printFormattedFloat(icm.accX(), 5, 2);
  Serial.print(", ");
  utils::printFormattedFloat(icm.accY(), 5, 2);
  Serial.print(", ");
  utils::printFormattedFloat(icm.accZ(), 5, 2);
  Serial.print(" ], Gyr (DPS) [ ");
  utils::printFormattedFloat(icm.gyrX(), 5, 2);
  Serial.print(", ");
  utils::printFormattedFloat(icm.gyrY(), 5, 2);
  Serial.print(", ");
  utils::printFormattedFloat(icm.gyrZ(), 5, 2);
  Serial.print(" ], Mag (uT) [ ");
  utils::printFormattedFloat(icm.magX(), 5, 2);
  Serial.print(", ");
  utils::printFormattedFloat(icm.magY(), 5, 2);
  Serial.print(", ");
  utils::printFormattedFloat(icm.magZ(), 5, 2);
  Serial.print(" ], Tmp (C) [ ");
  utils::printFormattedFloat(icm.temp(), 5, 2);
  Serial.print(" ]");
  Serial.println();
}