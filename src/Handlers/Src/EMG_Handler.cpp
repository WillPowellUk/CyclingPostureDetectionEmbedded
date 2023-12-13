#include "../Inc/EMG_Handler.hpp"
#include "../../Settings/Settings.h"
#include "../../Settings/Pinout.h"

EMGHandler::EMGHandler() {}

void EMGHandler::init() 
{
    for (int x = 0; x < Settings::Device::NumOfEMGs; x++) {
        pinMode(Pinout::EMG::Pin[x], INPUT); // EMG devices have inbuilt pull downs
    }
}

std::vector<Common::EMGPackage> EMGHandler::getPackets() 
{
    std::vector<Common::EMGPackage> emgPackage;

    for (int x = 0; x < Settings::Device::NumOfEMGs; x++) {
        Common::EMGPackage package;
        package.signal = analogRead(Pinout::EMG::Pin[x]);
        #ifdef DEBUG
        Serial.print("EMG ");
        Serial.print(x);
        Serial.print(": ");
        Serial.println(package.signal);
        #endif
        emgPackage.push_back(package);
    }

    return emgPackage;
}