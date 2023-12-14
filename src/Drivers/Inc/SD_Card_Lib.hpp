#pragma once

#include <Arduino.h>
#include "SPI.h"

class SDCard
{
public:
  //constructor - checks sd card and creates new recording directory and txt file
  SDCard();
  //checks if sd is mounted
  void init();
  void writeFile(const char *filename, const char *message);
  void mkdir(const char *dirPath);
};
