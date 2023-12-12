#include "../../Drivers/Inc/SD_Card_Lib.hpp"
#include "../../utils/inc/commonParams.hpp"
#include <vector>


class SDCardHandler: public SDCard
{
public:
    // constructor
    SDCardHandler();

    // main fn to store new recorded data to SD card as a CSV file
    void storeNewPacket(std::vector<unsigned long> timestamps, std::vector<std::vector<Common::IMUPackage>> IMUPackage, std::vector<std::vector<Common::EMGPackage>> EMGPackage);
    void createCSVFile();

private:
    
};
