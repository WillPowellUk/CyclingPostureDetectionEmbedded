#include "../Inc/SD_Card_Handler.hpp"
#include "../../Settings/Settings.h"
#include <string>
#include <sstream>

SDHandler::SDHandler()
{
}


void SDHandler::createCSVFile()
{
  // creates directory if necessary and creates new filelocation name
  // e.g. folderName = "/PostureDetectionData/Device 0"
  char folderName[50];
  sprintf(folderName, "/%s/%s", Settings::SD::RootDirectory, Settings::Device::DeviceID);

  // updates latestFileLocation
  getLatestFile(folderName);

  // e.g. csvHeader = "Device 0"
  char csvHeader[50];
  sprintf(csvHeader, "%s", Settings::Device::DeviceID);

    std::stringstream header;

    // Append the EMG header
    header << ",";
    for(int i = 0; i < Settings::Device::NumOfEMGs; ++i) {
        header << "CH " << (i + 1) << ",";
    }

    // Append the IMU headers
    for(int i = 0; i < Settings::Device::NumOfIMUs; ++i) {
        header << "IMU " << (i + 1) << ",,,,,,,,,";
    }

    header << "\nTimestamp (uS),";
    for(int i = 0; i < Settings::Device::NumOfEMGs; ++i) {
        header << ",";
    }

    // Each IMU has 9 data columns
    for(int i = 0; i < Settings::Device::NumOfIMUs; ++i) {
        header << "Acc X (mg),Acc Y (mg),Acc Z (mg),Gyr X (DPS),Gyr Y (DPS),Gyr Z (DPS),Mag X (uT),Mag Y (uT),Mag Z (uT),";
    }

    // Write the complete header to the CSV file
    writeFile(latestFileLocation, header.str().c_str());
}


void SDHandler::storeNewPacket(std::vector<Common::ICMPackage> ICMPackage, std::vector<Common::EMGPackage> EMGPackage)
{ 
    File file = SD.open(latestFileLocation, FILE_WRITE);
    if(!file)
    {
      Serial.print("Failed to open ");
      Serial.print(latestFileLocation);
      Serial.println(" for appending");
      return;
    }

    for (int i = 0; i < Settings::Device::NumOfPackets; i++)
    {
        for (byte x = 0; x < Settings::Device::NumOfIMUs; x++)
        {
            packets.push_back(imu[x]->getPacket());
        }
    }
    
}

