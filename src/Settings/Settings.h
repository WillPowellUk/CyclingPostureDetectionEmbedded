#pragma once
#include <Arduino.h>

namespace Settings
{
  #define DEBUG // Comment out to disable debug messages
  namespace Network
  {
    /* Ip address of server (PC) and port */
    constexpr const char *ServerIP = "192.168.0.35";
    constexpr const uint16_t Port = 42069;

    constexpr const char* WiFi_Logins[][2] = 
    { 
      // {SSID, Password}
      // {"DoWiFi", "hackedwifi"},
      {"SSID", "password"},
      {"OtherSSIDs", "blahblah"}
    };
  } // namespace Network
  
  namespace Device
  {    
    constexpr const char* DeviceID = "Device 0";
    constexpr const bool OnlineMode = false;
    constexpr const int NumOfIMUs = 1; 
    constexpr const int NumOfEMGs = 3; 
    constexpr const int NumOfPacketsPerBatch = 10; // Number of packets to send to sd card per batch
  } // namespace Device
  
  namespace IMU
  {

  } // namespace IMU

  namespace SD
  {
    constexpr const char* RootDirectory = "PostureDetectionData";
  } // namespace SD
  


} // namespace Settings