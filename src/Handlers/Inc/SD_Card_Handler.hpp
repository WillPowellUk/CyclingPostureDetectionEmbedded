#include "../../Drivers/Inc/SD_Card_Lib.hpp"
#include "../../utils/inc/commonParams.hpp"
#include <vector>


class SDHandler: public SDCard
{
public:
    // constructor
    SDHandler();

    // main fn to store new recorded data to SD card as a CSV file
    void storeNewPacket(std::vector<Common::ICMPackage> ICMPackage, std::vector<Common::EMGPackage> EMGPackage);

private:
    void createCSVFile();
    
};
