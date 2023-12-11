#pragma once

#include <Arduino.h>
#include "SD.h"
#include "SPI.h"

class SDCard
{
public:
  //constructor - checks sd card and creates new recording directory and txt file
  SDCard();
  void testFileIO(const char * path);
  void appendFile(const char* path, const char* message);
  char* latestFileLocation;

protected:
  //checks if sd is mounted and prints size
  void checkSD();
  //set latestFileLocation as next valid csv file in directory
  void getLatestFile(const char* dirname);
  void listDir(const char* dirname, uint8_t levels);
  void createDir(const char* path);
  void removeDir(const char* path);
  void readFile(const char* path);
  void writeFile(const char* path, const char* message);
  void renameFile(const char* path1, const char* path2);
  void deleteFile(const char* path);
};
