#include "../../Drivers/Inc/SD_Card_Lib.hpp"
#include "../../utils/inc/commonParams.hpp"
#include <vector>


class SDCardHandler: public SDCard
{
public:
    // constructor
    SDCardHandler();

    // main fn to store new recorded data to SD card as a CSV file
    void storeNewPacket(Common::SDCardPackage package);
    void createCSVFile();

private:
    char filePath[20];
};
