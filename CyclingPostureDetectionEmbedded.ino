#include "src/Handlers/Inc/IMU_Handler.hpp"
#include "src/Handlers/Inc/EMG_Handler.hpp"
#include "src/Handlers/Inc/SD_Card_Handler.hpp"

#include "src/Settings/Settings.h"
#include "src/utils/inc/commonParams.hpp"
#include "src/utils/inc/functions.hpp"

#include <FreeRTOS.h>
#include "semphr.h" // For using queues

// Task prototypes
void sensorTask(void *pvParameters);
void storageTask(void *pvParameters);

// Global handler instances
IMUHandler imu;
EMGHandler emg;
SDCardHandler sd;
std::string filePath;

// Global queue handle
QueueHandle_t dataQueue;

void setup() {
  //#ifdef DEBUG
  Serial.begin(115200);
  while (!Serial) { ; } // Wait for serial port to connect.
  // #endif
  Serial.println("Cycling Posture Detection System Running");

  // Initialize handlers
  imu.init();
  emg.init();
  sd.init();
  filePath = sd.createCSVFile();

  // Create a queue capable of holding 10 pointers to SDCardPackage
  dataQueue = xQueueCreate(10, sizeof(Common::SDCardPackage*));

  if (dataQueue == NULL) {
    Serial.println("Failed to create the queue");
    // Handle error
  }

  // Create tasks for sensor reading and data storage on different cores
  xTaskCreatePinnedToCore(sensorTask, "SensorTask", 10000, NULL, 1, NULL, 0); // Core 0
  xTaskCreatePinnedToCore(storageTask, "StorageTask", 10000, NULL, 1, NULL, 1); // Core 1
}

void loop() {
  // Empty, as FreeRTOS tasks are handling the logic.
}

void sensorTask(void *pvParameters) {
  for (;;) {
    // Prepare the data
    std::vector<unsigned long> timestamps;
    std::vector<std::vector<Common::IMUPackage>> imuPackets;
    std::vector<std::vector<Common::EMGPackage>> emgPackets;

    // Assuming you fill these vectors with the appropriate data...
    timestamps.push_back(micros());
    imuPackets.push_back(imu.getPackets());
    emgPackets.push_back(emg.getPackets());

    // Now create a new instance of SDCardPackage with the prepared data
    auto package = new Common::SDCardPackage(timestamps, imuPackets, emgPackets);

    // Attempt to send the package to the queue
        // Capture the start time
    unsigned long queueStartTime = micros();

    if (xQueueSend(dataQueue, &package, portMAX_DELAY) != pdPASS) {
      // Failed to send the package to the queue
      #ifdef DEBUG
      Serial.println("Failed to send package to the queue");
      #endif
      delete package; // Important to avoid memory leak
    }

    // Capture the end time and calculate the duration
    unsigned long queueEndTime = micros();
    unsigned long queueDuration = queueEndTime - queueStartTime;

    Serial.print("xQueueSend duration (microseconds): ");
    Serial.println(queueDuration);
    // if (xQueueSend(dataQueue, &package, portMAX_DELAY) != pdPASS) {
    //   // Failed to send the package to the queue
    //   #ifdef DEBUG
    //   Serial.println("Failed to send package to the queue");
    //   #endif
    //   delete package; // Important to avoid memory leak
    // }

    #ifdef DEBUG
    vTaskDelay(pdMS_TO_TICKS(2000)); // Delay for a bit before next reading
    #endif
  }
}

void storageTask(void *pvParameters) {
  Common::SDCardPackage* receivedPackage;

  for (;;) {
    if (xQueueReceive(dataQueue, &receivedPackage, portMAX_DELAY) == pdPASS) {
      // Successfully received a package, proceed to store it
      sd.storeNewPacket(filePath, *receivedPackage);

      // Once done, free the allocated memory
      delete receivedPackage;
    }
    else 
    {
      #ifdef DEBUG
      Serial.println("Failed to send package to the queue");
      #endif
    }
  }
}