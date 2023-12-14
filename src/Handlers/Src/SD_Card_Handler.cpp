#include "../Inc/SD_Card_Handler.hpp"
#include "../../Settings/Settings.h"
#include <string>
#include <sstream>
#include <SD.h>

SDCardHandler::SDCardHandler()
{
}


std::string SDCardHandler::createCSVFile()
{
    std::string dirPath;
    
    dirPath = Settings::SD::RootDirectory;
    dirPath += "/";
    dirPath += Settings::Device::DeviceID;

    Serial.println(dirPath.c_str());   
    if (!SD.exists(dirPath.c_str()))
    {
        mkdir(dirPath.c_str());
    }

    int i = 0;
    std::string filePath;
    while (true) {
        char tempFilePath[50];
        sprintf(tempFilePath, "%s/Rec%d.csv", dirPath.c_str(), i);
        filePath = tempFilePath; 
        if (!SD.exists(filePath.c_str())) {
            break; // Exit the loop when the file doesn't exist
        }
        i++;
    }
    Serial.print("Writing to file: ");
    Serial.println(filePath.c_str());

    std::stringstream header;

    // Append the EMG header
    header << "," << "EMG ";
    for(int i = 0; i < Settings::Device::NumOfEMGs; ++i) {
        header << ",";
    }

    // Append the IMU headers
    for(int i = 0; i < Settings::Device::NumOfIMUs; ++i) {
        header << "IMU " << (i + 1) << ",,,,,,,,,";
    }

    header << "\nTimestamp (uS),";

    for(int i = 0; i < Settings::Device::NumOfEMGs; ++i) {
        header << "CH" << (i + 1) << ",";
    }

    // Each IMU has 9 data columns
    for(int i = 0; i < Settings::Device::NumOfIMUs; ++i) {
        header << "Acc X (mg),Acc Y (mg),Acc Z (mg),Gyr X (DPS),Gyr Y (DPS),Gyr Z (DPS),Mag X (uT),Mag Y (uT),Mag Z (uT)" << ",";
    }
    header << "\n";

    // Write the complete header to the CSV file
    writeFile(filePath.c_str(), header.str().c_str());

    return filePath;
}

void SDCardHandler::storeNewPacket(std::string filePath, Common::SDCardPackage package)
{
    File file = SD.open(filePath.c_str(), FILE_WRITE);
    if (!file)
    {
        Serial.print("Failed to open ");
        Serial.print(filePath.c_str());
        Serial.println(" for appending");
        return;
    }

    // Write the timestamp and EMG data to the CSV file
    for (int t = 0; t < package.timestamps.size(); t++)
    {
        file.print(package.timestamps[t]);
        file.print(",");
        for (int e = 0; e < Settings::Device::NumOfEMGs; e++)
        {
            file.print(package.emgPackets[t][e].signal);
            file.print(",");
        }

        for (int i = 0; i < Settings::Device::NumOfIMUs; i++)
        {
            file.print(package.imuPackets[t][i].accX, Settings::SD::numOfDigitsForFloats);
            file.print(",");
            file.print(package.imuPackets[t][i].accY, Settings::SD::numOfDigitsForFloats);
            file.print(",");
            file.print(package.imuPackets[t][i].accZ, Settings::SD::numOfDigitsForFloats);
            file.print(",");
            file.print(package.imuPackets[t][i].gyrX, Settings::SD::numOfDigitsForFloats);
            file.print(",");
            file.print(package.imuPackets[t][i].gyrY, Settings::SD::numOfDigitsForFloats);
            file.print(",");
            file.print(package.imuPackets[t][i].gyrZ, Settings::SD::numOfDigitsForFloats);
            file.print(",");
            file.print(package.imuPackets[t][i].magX, Settings::SD::numOfDigitsForFloats);
            file.print(",");
            file.print(package.imuPackets[t][i].magY, Settings::SD::numOfDigitsForFloats);
            file.print(",");
            file.print(package.imuPackets[t][i].magZ, Settings::SD::numOfDigitsForFloats);
            file.print(",");
        }
        file.println();
    }
    file.close();
}
