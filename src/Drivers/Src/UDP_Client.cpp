#include "../Inc/UDP_Client.hpp"
#include "../../Settings/Settings.h"

void UDPClient::connect(const uint16_t port) 
{ 
  Port = port; 

  bool connected = false;

  for(int i=0; i < sizeof(Settings::Network::WiFi_Logins)/sizeof(Settings::Network::WiFi_Logins[0]); i++)
  {
    Serial.print("\nConnecting to ");
    Serial.print(Settings::Network::WiFi_Logins[i][0]);
    // /* connect to your WiFi */
    WiFi.begin((char*)Settings::Network::WiFi_Logins[i][0], (char*)Settings::Network::WiFi_Logins[i][1]);
    // /* wait until ESP32 connect to WiFi*/
    int timeout = 0;
    while (WiFi.status() != WL_CONNECTED && timeout<=20) 
    {
      delay(1000);
      Serial.print(".");
      timeout++;
    }

    if(timeout > 20) continue;

    else
    {
      Serial.println("Connected to %s");
      Serial.println(Settings::Network::WiFi_Logins[i][0]);
      Serial.println("\nBrainPatch EEG running on:");
      Serial.print("  IP Address: ");
      Serial.println(WiFi.localIP());
      Serial.print("  Port: ");
      Serial.println(Port);
      connected = true;
      break;
    }
  }

  if (!connected)
  {
      Serial.print("Cannot connect to WiFi.\nPlease check Settings.h to ensure the SSID and Password are correct.\n");
      while(true);
  }
}


void UDPClient::send(uint8_t* buffer, unsigned short size) 
{
  udp.beginPacket(Settings::Network::ServerIP, Port);
  udp.write(buffer, size);
  udp.endPacket();
}
