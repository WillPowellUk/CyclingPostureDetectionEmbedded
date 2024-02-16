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
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  delay(2000);
#endif
  Serial.println("Cycling Posture Dection System Running");

  IMUHandler imu;
  EMGHandler emg;
  SDCardHandler sd;

  imu.init();
  emg.init();
  sd.init();

  std::string filePath = sd.createCSVFile();

  // get starting timestamp
  unsigned long startTimestamp = micros();
  unsigned long windowStartTimestamp = micros();
  while (true)
  {
    std::vector<std::vector<Common::IMUPackage>> imuPackets;
    std::vector<std::vector<Common::EMGPackage>> emgPackets;
    std::vector<unsigned long> timestampsEMG;
    std::vector<unsigned long> timestampsIMU;
    windowStartTimestamp = micros();
    while ((micros() - windowStartTimestamp) < Settings::Device::WindowSizeEMG)
    {
      timestampsEMG.push_back(micros() - startTimestamp);
      emgPackets.push_back(emg.getPackets());
    }
    Common::SDCardPackageEMG packageEMG(timestampsEMG, emgPackets);
    sd.storeNewPacket(filePath, packageEMG);

    windowStartTimestamp = micros();
    while ((micros() - windowStartTimestamp) < Settings::Device::WindowSizeIMU)
    {
      timestampsIMU.push_back(micros() - startTimestamp);
      imuPackets.push_back(imu.getPackets());
    }
    Common::SDCardPackageIMU packageIMU(timestampsIMU, imuPackets);
    sd.storeNewPacket(filePath, packageIMU);

#ifdef DEBUG
    delay(2000);
#endif
  }
}

void loop()
{
}
