#include "../Inc/IMU_Handler.hpp"
#include "../../Settings/Settings.h"

IMUHandler::IMUHandler() 
{

}

bool IMUHandler::init()
{
    Wire.begin();
    Wire.setClock(400000);

    //Assign pointers to instances of the class
    imu = new ICM20948*[Settings::Device::NumOfIMUs];
    for (int x = 0; x < Settings::Device::NumOfIMUs; x++)
        imu[x] = new ICM20948();

    if (!mux.begin())
    {
        Serial.println("Mux not detected. Freezing...");
        while (1)
        ;
    }
    Serial.println("Mux detected");

    byte currentPortNumber = mux.getPort();
    Serial.print("CurrentPort: ");
    Serial.println(currentPortNumber);

    //Initialize all the IMUs
    for (byte x = 0; x < Settings::Device::NumOfIMUs; x++)
    {
        mux.setPort(x);
        if (!imu[x]->init())
        {
            Serial.print("Sensor ");
            Serial.print(x);
            Serial.println(" did not begin! Check wiring");
            while(true);
        }
        else
        {
            Serial.print("Sensor ");
            Serial.print(x);
            Serial.println(" configured");
        }
    }
}

std::vector<Common::IMUPackage> IMUHandler::getPackets() 
{
    std::vector<Common::IMUPackage> packets;
    for (byte x = 0; x < Settings::Device::NumOfIMUs; x++)
    {
        packets.push_back(imu[x]->getPacket());
    }

    return packets;
}