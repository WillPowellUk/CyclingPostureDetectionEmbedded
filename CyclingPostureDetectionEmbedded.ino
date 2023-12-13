#include "src/Handlers/Inc/IMU_Handler.hpp"
#include "src/Handlers/Inc/EMG_Handler.hpp"
#include "src/Handlers/Inc/SD_Card_Handler.hpp"

#include "src/Settings/Settings.h"
#include "src/utils/inc/commonParams.hpp"

#define DEBUG

void setup()
{
  #ifdef DEBUG
  Serial.begin(115200);
  delay(3000);
  Serial.println("Cycling Posture Dection System Running");
  // while (!Serial) {
  //   ; // wait for serial port to connect
  // }
  #endif

  IMUHandler imu;
  EMGHandler emg;
  SDCardHandler sd;

  imu.init();
  imu.getPackets();
  // emg.init();
  // sd.init();
  //sd.createCSVFile();

  // while (true)
  // {
  //   std::vector<std::vector<Common::IMUPackage>> imuPackets;
  //   std::vector<std::vector<Common::EMGPackage>> emgPackets;
  //   std::vector<unsigned long> timestamps;

  //   for (int i = 0; i < Settings::Device::NumOfPackets; i++)
  //   {
  //     timestamps.push_back(micros());
  //     imuPackets.push_back(imu.getPackets());
  //     emgPackets.push_back(emg.getPackets());
  //   }
  //   Common::SDCardPackage package(timestamps, imuPackets, emgPackets);
  //   sd.storeNewPacket(package);   
  // }
}

void loop()
{ 

}
