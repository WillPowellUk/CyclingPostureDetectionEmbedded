#pragma once
#include "ICM_20948.h"
#include "../../utils/inc/commonParams.hpp"

class ICM20948
{
public:
  bool init();
  Common::ICMPackage getPacket();
  void printFormattedData();
  void printRawData();
private:
  ICM_20948_I2C icm;
};