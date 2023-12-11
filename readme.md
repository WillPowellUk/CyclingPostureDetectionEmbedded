# Cycling Posture Detection
This device records data from a three 9DoF IMUs (ICM-20948) and 3 EMG devices and stores to SD card in real time.

## Getting Started
* [Arduino IDE Legacy](https://www.arduino.cc/en/software/OldSoftwareReleases) must be installed in addition to the [ESP32 board manager](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)
* Clone this repo and install the Arduino Extension for VSCode
* Go to Visual Studio Code, click File > Preferences > Settings, then click the Open Settings (JSON) icon in the upper-right corner of the Settings page
add "arduino.path": "C:\\Program Files (x86)\\Arduino"
* Set the correct COM Port for the ESP32: ctrl-shift-p and type Arduino: Select Serial Port. N.B. if the COM port is not visible, please install the [ESP32 driver](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads).
* Configure the *Settings.h* file by inputting the correct WiFi SSID and Password and the ip address of the Server (PC running the EEG-Recorder-Python script)
