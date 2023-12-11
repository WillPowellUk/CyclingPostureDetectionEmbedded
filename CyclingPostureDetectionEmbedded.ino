#include "src/Handlers/Inc/IMU_Handler.hpp"

#include "src/Settings/Settings.h"
#define DEBUG

void setup()
{
  #ifdef DEBUG
  Serial.begin(115200);
  delay(3000);
  #endif

  IMUHandler imu;
  imu.init();
  imu.getPackets();

}

void loop()
{ 

}
