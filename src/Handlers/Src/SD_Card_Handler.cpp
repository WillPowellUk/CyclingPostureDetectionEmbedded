#include "../Inc/SD_Card_Handler.hpp"
#include "../../Settings/Settings.h"
#include <string>
#include <sstream>

SDCardHandler::SDCardHandler()
{
}


void SDCardHandler::createCSVFile()
{
  // creates directory if necessary and creates new file location name
  // e.g. folderName = "/PostureDetectionData/Device 0"
  char folderName[50];
  sprintf(folderName, "/%s/%s", Settings::SD::RootDirectory, Settings::Device::DeviceID);

  // updates latestFileLocation
  getLatestFile(folderName);

  // e.g. csvHeader = "Device 0"
  char csvHeader[50];
  sprintf(csvHeader, "%s", Settings::Device::DeviceID);

  writeFile(latestFileLocation, csvHeader); 

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
        header << "Acc X (mg),Acc Y (mg),Acc Z (mg),Gyr X (DPS),Gyr Y (DPS),Gyr Z (DPS),Mag X (uT),Mag Y (uT),Mag Z (uT)\n";
    }

    // Write the complete header to the CSV file
    writeFile(latestFileLocation, header.str().c_str());

    Serial.println("Created New File");
}
   
void SDCardHandler::storeNewPacket(Common::SDCardPackage package)
{
    File file = SD.open(latestFileLocation, FILE_WRITE);
    if (!file)
    {
        Serial.print("Failed to open ");
        Serial.print(latestFileLocation);
        Serial.println(" for appending");
        return;
    }

    // Write the timestamp and EMG data to the CSV file
    for (int t = 0; t < package.timestamps.size(); t++)
    {
        file.print(package.timestamps[t]);
        for (int i = 0; i < Settings::Device::NumOfIMUs; i++)
        {
            file.print(",");
            file.print(package.imuPackets[t][i].accX);
            file.print(",");
            file.print(package.imuPackets[t][i].accY);
            file.print(",");
            file.print(package.imuPackets[t][i].accZ);
            file.print(",");
            file.print(package.imuPackets[t][i].gyrX);
            file.print(",");
            file.print(package.imuPackets[t][i].gyrY);
            file.print(",");
            file.print(package.imuPackets[t][i].gyrZ);
            file.print(",");
            file.print(package.imuPackets[t][i].magX);
            file.print(",");
            file.print(package.imuPackets[t][i].magY);
            file.print(",");
            file.print(package.imuPackets[t][i].magZ);
            file.print(",");
        }
        for (int e = 0; e < Settings::Device::NumOfEMGs; e++)
        {
            file.print(package.emgPackets[t][e].signal);
            file.print(",");
        }

        file.println();
    }
    file.close();
}
