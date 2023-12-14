#include "../Inc/SD_Card_Lib.hpp"
#include "../../Settings/Pinout.h"
#include "../../Settings/Settings.h"
#include <SD.h>

SDCard::SDCard()
{
}

void SDCard::init()
{
  // pinMode(Pinout::SD::MISO, INPUT_PULLUP);
  // pinMode(Pinout::SD::MOSI, OUTPUT);
  // pinMode(Pinout::SD::CLK, OUTPUT);
  // pinMode(Pinout::SD::CS, INPUT_PULLUP);
  if (!SD.begin(Pinout::SD::CS))
  {
    delay(1000);
    Serial.println("\n\n!!!!!!!!!!!!!!!!!!!!!!!!");
    Serial.println("Card Mount Failed");
    Serial.println("Insert SD Card and reset");
    Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!\n\n");
    while (true);
  }
  else
  {
    Serial.println("SD Card mounted successfully");
  }
}

void SDCard::mkdir(const char *dirPath)
{
  if (SD.mkdir(dirPath))
  {
    Serial.println("Dir created");
  }
  else
  {
    Serial.println("mkdir failed");
  }
}

void SDCard::WriteFile(const char *filename, const char *message)
{
  File file = SD.open(filename, FILE_WRITE);
  if (!file)
  {
    Serial.print("Failed to open ");
    Serial.println(filename);
    return;
  }
  #ifdef DEBUG
  if (file.print(message))
  {
    Serial.println("File written");
  }
  #endif
  else
  {
    Serial.println("Write failed");
  }
  file.close();
}