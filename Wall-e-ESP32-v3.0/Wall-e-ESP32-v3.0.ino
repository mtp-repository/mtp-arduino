/*  
  Wall-e Version 3.0

  Code for ESP 32 BT

  Author
    - Cenon Dinno Ebora III
    - cenon4dno@gmail.com

  Components
    - Arduino Uno
    - Car Chassis 
    - L298N
    - 4 DC motor
    - 2 18650 battery
    - 18650 battery shield
    - LCD screen

    New Components on v3
    - ESP32 with WIFI, BT and camera
    - 

  Additional Steps
    - Add library LiquidCrystal_I2C in LcdDisplay/lib/LiquidCrystal_V1.2.1.zip
    - Open library I2CIO.cpp and change line 35 from '<../Wire/Wire.h>' to <Wire.h> 

  Functionality:
    - Movement
        - Forward,
        - Right
        - Left
    - Show status on LCD
    - Battery are rechargable
  New Functionality
    - Camera
    - Wifi access to camera
    - BT phone controller

   Roadmap
    - RFID locking
    - Sensors     

  Library
    - 
    

  References:
  http://dronebotworkshop.com
  DC Motor/ L298N - https://arduinogetstarted.com/tutorials/arduino-dc-motor
  Sources:
    https://www.youtube.com/watch?v=YVPumD16Y_Y&t=321s
    https://roboticadiy.com/send-data-from-arduino-to-nodemcu-and-nodemcu-to-arduino-via-serial-communication/
*/
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

#define RXD2 16
#define TXD2 17

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32Dino"); //Bluetooth device name
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (SerialBT.available()) {
    //Serial.write(SerialBT.read());
    String received = SerialBT.readString();
    Serial.println("Send msg:");
    Serial2.println(received);
    Serial.println(received);
  }
  
  delay(20);
}
