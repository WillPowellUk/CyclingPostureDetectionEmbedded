#pragma once
#include<WiFi.h>
#include <WiFiUdp.h>


/**********************
 *
 * Class UDPClient is a generic udp client that connects to the wifi, sends and receives udp packets
 *
 ***********************/

class UDPClient{

public:
    // No Constructor

    WiFiUDP udp;
    
    // Method to connect to WiFi
    void connect(const uint16_t port);

    // method to send UDP Packets to server
    void send(uint8_t* buffer, unsigned short size);
private:
    uint16_t Port = 0;
};