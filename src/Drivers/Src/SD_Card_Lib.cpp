#include "../Inc/SD_Card_Lib.hpp"
#include "../../Settings/Pinout.h"

SDCard::SDCard()
{
  pinMode(Pinout::SD::DATA1, INPUT_PULLUP);
  pinMode(Pinout::SD::DATA0, INPUT_PULLUP);
  pinMode(Pinout::SD::DATA3, INPUT_PULLUP);
  pinMode(Pinout::SD::DATA4, INPUT_PULLUP);
  pinMode(Pinout::SD::CMD, INPUT_PULLUP);

  //ensures sd is mounted and formatted ok
  checkSD();
}


void SDCard::checkSD()
{
  if (!SD.begin(Pinout::SD::CMD))
  {
    delay(1000);
    Serial.println("\n\n!!!!!!!!!!!!!!!!!!!!!!!!");
    Serial.println("Card Mount Failed");
    Serial.println("Insert SD Card and reset");
    Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!\n\n");
  }
}


void SDCard::getLatestFile(const char* dirname)
{
  free(latestFileLocation);
  latestFileLocation = reinterpret_cast<char*>(malloc(50*sizeof(char)));
  
  File root = SD.open(dirname);
  if (!root)
  {
    createDir(dirname);
  }

  int i = 1;
  while (root.openNextFile())
  {
    i++;
  }
  sprintf(latestFileLocation, "%s/Recording %d.csv", dirname, i);
}

void SDCard::listDir(const char * dirname, uint8_t levels)
{
  Serial.print("Listing directory: ");
  Serial.println(dirname);

  File root = SD.open(dirname);
  if (!root) {
    Serial.println("Failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels) {
        listDir(file.name(), levels - 1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}

void SDCard::createDir(const char * path)
{
  Serial.print("Creating Dir: ");
  Serial.println(path);
  if (SD.mkdir(path)) {
    Serial.println("Dir created");
  } else {
    Serial.println("mkdir failed");
  }
}

void SDCard::removeDir(const char * path)
{
    Serial.print("Removing Dir: ");
  Serial.println(path);
  if (SD.rmdir(path)) {
    Serial.println("Dir removed");
  } else {
    Serial.println("rmdir failed");
  }
}

void SDCard::readFile(const char* path)
{
    Serial.print("Reading Path: ");
    Serial.println(path);

  File file = SD.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  while (file.available()) {
    Serial.write(file.read());
  }
}

void SDCard::writeFile(const char* path, const char* message)
{
  Serial.print("Writing to file: ");
  Serial.println(path);

  File file = SD.open(path, FILE_WRITE);
  if (!file)
  {
    Serial.println("Failed to open file for writing");
    return;
  }
  if(!file.print(message)) 
  {
    Serial.println("Write failed");
  }
}

void SDCard::appendFile(const char* path, const char* message)
{
  File file = SD.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (!file.print(message))
  {
    Serial.println("Append failed");
    delay(1000);
  }
}

void SDCard::deleteFile(const char * path)
{
    Serial.print("Deleting File: ");
  Serial.println(path);
  if (SD.remove(path)) {
    Serial.println("File deleted");
  } else {
    Serial.println("Delete failed");
  }
}

void SDCard::testFileIO(const char * path)
{
  File file = SD.open(path);
  static uint8_t buf[512];
  size_t len = 0;
  uint32_t start = millis();
  uint32_t end = start;
  if (file) {
    len = file.size();
    size_t flen = len;
    start = millis();
    while (len) {
      size_t toRead = len;
      if (toRead > 512) {
        toRead = 512;
      }
      file.read(buf, toRead);
      len -= toRead;
    }
    end = millis() - start;
    Serial.print(flen);
    Serial.print("bytes read for ");
    Serial.print(end);
    Serial.println(" ms");
    file.close();
  } else {
    Serial.println("Failed to open file for reading");
  }


  file = SD.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }

  size_t i;
  start = millis();
  for (i = 0; i < 2048; i++) {
    file.write(buf, 512);
  }
  end = millis() - start;
    Serial.print(2048 * 512);
    Serial.print("bytes written for ");
    Serial.print(end);
    Serial.println(" ms");
  file.close();
}
