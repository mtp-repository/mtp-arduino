/*  
  Wall-e Version 3.0

  Code for Arduino Uno

  Author
    - Cenon Dinno Ebora III
    - cenon4dno@gmail.com

  Components
    - Arduino Uno
    - Car Chassis 
    - L298N
    - 4 DC motor
    - 2 18650 battery
    - 18650 battery shieldEnable features
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
     https://forum.arduino.cc/t/esp32-sending-string-to-arduino-uno/693074
     https://www.programmingboss.com/2021/04/esp32-arduino-serial-communication-with-code.html
*/

// Include Wire Library for I2C
#include <Wire.h>

// Include settings of features
#include "features.h"
#include "car_movement_settings.h"
#include "car_lcd_settings.h"

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5);
  
  init();
}

void loop() {
  String valor = "";
  
  while (Serial.available() > 0) {
    String line = Serial.readString();
    for(int i = 0 ;i < line.length(); i++){
      int character = line[i];
      if (isDigit(character)) {
         valor += (char)character;
      }else if (character != '\n') {
          code = character;
      }else{
        break;
      }  
    }
  }
  
  Serial.println(">>"+String(code)+"<<");
  switch(code){
    case 'F': forward(); break;
    case 'G': backward(); break;
    case 'R': rightforward(); break;
    case 'L': leftforward(); break;
    case 'X': increaseSpeed(); break;
    case 'Y': decreaseSpeed();break;
    //case 'S': stop(); break;
    case 'M':
      break;
    case 'N':
      break;
  }
  
  delay(duration);
}

void init() {
  if (WALLE_CAR_MOVEMENT == 1) {
    initCarMovement();      
  }

  if (WALLE_CAR_LCD == 1) {
    initCarLcd();      
  }

  if (WALLE_CAR_TRACKING == 1) {
    initCarTracking();      
  }

  if (WALLE_CAR_BUZZER == 1) {
    initCarBuzzer();      
  }

  if (WALLE_CAR_WIFI == 1) {
    initCarWifi();      
  }

  if (WALLE_CAR_CAMERA == 1) {
    initCarCamera();      
  }
}

void initCarMovement() {
  Serial.println("Car Movement initiating!");
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void initCarLcd() {  
}

void initCarTracking() {  
}

void initCarBuzzer() {  
}

void initCarWifi() {  
}

void initCarCamera() {  
}

void backward(){
    Serial.println("Backward function start");

    analogWrite(enA, speed);
    analogWrite(enB, speed);
    
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    delay(20);
}

void forward(){
  Serial.println("Forward function start");

  analogWrite(enA, speed);
  analogWrite(enB, speed);

  digitalWrite (in1, HIGH);
  digitalWrite (in2, LOW);
  digitalWrite (in3, HIGH);
  digitalWrite (in4, LOW);

  delay(20);
}

void stop(){
  Serial.println("Stop function start");

  analogWrite(enA, 0);
  analogWrite(enB, 0);

  digitalWrite (in1, LOW);
  digitalWrite (in2, LOW);
  digitalWrite (in3, LOW);
  digitalWrite (in4, LOW);

  delay(20);
}

void leftforward(){
  Serial.println("Left-forward function start");
  
  analogWrite(enA, speed);
  analogWrite(enB, 0);

  digitalWrite (in1, HIGH);
  digitalWrite (in2, LOW);
  digitalWrite (in3, HIGH);
  digitalWrite (in4, LOW);
  delay(20);
}

void rightforward(){
  Serial.println("Right-forward function start");

  analogWrite(enA, 0);
  analogWrite(enB, speed);
  
  digitalWrite (in1, HIGH);
  digitalWrite (in2, LOW);
  digitalWrite (in3, HIGH);
  digitalWrite (in4, LOW);
  delay(20);
}

void leftbackward(){
  Serial.println("Left-backward function start");
  analogWrite(enA, speed);
  analogWrite(enB, 0);

  digitalWrite (in1, LOW);
  digitalWrite (in2, HIGH);
  digitalWrite (in3, LOW);
  digitalWrite (in4, HIGH);
  delay(20);
}

void rightbackward(){
  Serial.println("Right-backward function start");
  analogWrite(enA, 0);

  analogWrite(enB, speed);
  digitalWrite (in1, LOW);
  digitalWrite (in2, HIGH);
  digitalWrite (in3, LOW);
  digitalWrite (in4, HIGH);
  delay(20);
}

void increaseSpeed() {
  if (speed < 255) {
    speed = speed + speedRateVal;
  }
}

void decreaseSpeed() {
  if (speed > speedRateVal) {
    speed = speed - speedRateVal;
  }
}