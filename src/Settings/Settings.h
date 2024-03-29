#pragma once
#include <Arduino.h>

// #define DEBUG // Comment out to disable debug messages

namespace Settings
{
  namespace Network
  {
    /* Ip address of server (PC) and port */
    constexpr const char *ServerIP = "192.168.0.35";
    constexpr const uint16_t Port = 42069;

    constexpr const char *WiFi_Logins[][2] =
        {
            // {SSID, Password}
            {"SSID", "password"},
            {"OtherSSIDs", "blahblah"}};
  } // namespace Network

  namespace Device
  {
    constexpr const char *DeviceID = "Device0";
    constexpr const bool OnlineMode = false;
    constexpr const int NumOfIMUs = 3;
    constexpr const int NumOfEMGs = 3;
    constexpr const int NumOfPacketsPerBatchEMG = 10000; // Number of EMG packets to send to sd card per batch
    constexpr const int NumOfPacketsPerBatchIMU = 1000; // Number of IMU packets to send to sd card per batch
    constexpr const unsigned long WindowSizeEMG = 5e6; // in microseconds
    constexpr const unsigned long WindowSizeIMU = 5e6; // in microseconds
  }                                                // namespace Device

  namespace IMU
  {
    constexpr const uint16_t SamplingRate = 100; // Hz
  }                                              // namespace IMU

  namespace SD
  {
    constexpr const char *RootDirectory = "/AML"; // Dir path cannot be longer than 20 characters
    constexpr const int numOfDigitsForFloats = 5; // Number of digits to keep after the decimal point
  }                                               // namespace SD

} // namespace Settings