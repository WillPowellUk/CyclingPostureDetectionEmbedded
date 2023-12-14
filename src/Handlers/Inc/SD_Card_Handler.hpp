#include "../../Drivers/Inc/SD_Card_Lib.hpp"
#include "../../utils/inc/commonParams.hpp"
#include <vector>
#include <string>

class SDCardHandler: public SDCard
{
public:
    // constructor
    SDCardHandler();

    // main fn to store new recorded data to SD card as a CSV file
    void storeNewPacket(std::string filePath, Common::SDCardPackage package);
    std::string createCSVFile();
};
