#include "src/Handlers/Inc/IMU_Handler.hpp"
#include "src/Handlers/Inc/EMG_Handler.hpp"
#include "src/Handlers/Inc/SD_Card_Handler.hpp"

#include "src/Settings/Settings.h"
#define DEBUG

void setup()
{
  #ifdef DEBUG
  Serial.begin(115200);
  delay(3000);
  #endif

  IMUHandler imu;
  EMGHandler emg;
  SDCardHandler sd;

  imu.init();
  emg.init();
  sd.createCSVFile();

  while (true)
  {
    std::vector<std::vector<Common::IMUPackage>> imuPackets;
    std::vector<std::vector<Common::EMGPackage>> emgPacekts;
    std::vector<unsigned long> timestamps;

    for (int i = 0; i < Settings::Device::NumOfPackets; i++)
    {
      timestamps.push_back(micros());
      imuPackets.push_back(imu.getPackets());
      emgPacekts.push_back(emg.getPackets());
    }
    sd.storeNewPacket(timestamps, imuPackets, emgPacekts);
  }
}

void loop()
{ 

}
