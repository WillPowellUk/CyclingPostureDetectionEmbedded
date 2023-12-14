#include "src/Handlers/Inc/IMU_Handler.hpp"
#include "src/Handlers/Inc/EMG_Handler.hpp"
#include "src/Handlers/Inc/SD_Card_Handler.hpp"

#include "src/Settings/Settings.h"
#include "src/utils/inc/commonParams.hpp"
#include "src/utils/inc/functions.hpp"

void setup()
{
  #ifdef DEBUG
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Cycling Posture Dection System Running");
  #endif

  IMUHandler imu;
  EMGHandler emg;
  SDCardHandler sd;

  //imu.init();
  // emg.init();

  sd.init();
  sd.createCSVFile();
  
  while (true)
  {
    std::vector<std::vector<Common::IMUPackage>> imuPackets;
    std::vector<std::vector<Common::EMGPackage>> emgPackets;
    std::vector<unsigned long> timestamps;

    for (int i = 0; i < Settings::Device::NumOfPacketsPerBatch; i++)
    {
      timestamps.push_back(micros());
      imuPackets.push_back(imu.getPackets());
      // #ifdef DEBUG
      // utils::printIMUPackets(imuPackets);
      // #endif
      emgPackets.push_back(emg.getPackets());
    }
    Common::SDCardPackage package(timestamps, imuPackets, emgPackets);
    sd.storeNewPacket(package);

    #ifdef DEBUG
    delay(1000);
    #endif
  }
}

void loop()
{ 

}
