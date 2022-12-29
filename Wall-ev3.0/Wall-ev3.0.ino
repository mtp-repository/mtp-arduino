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
     https://forum.arduino.cc/t/esp32-sending-string-to-arduino-uno/693074
     https://www.programmingboss.com/2021/04/esp32-arduino-serial-communication-with-code.html
*/

// Include Wire Library for I2C
#include <Wire.h>
// Include NewLiquidCrystal Library for I2C
//#include <LiquidCrystal_I2C.h>

// Define LCD pinout
//const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;

// Define I2C Address - change if reqiuired
//const int i2c_addr = 0x27;

//LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

// connect motor controller pins to Arduino digital pins
// motor one
int enA = 10;
int in1 = 9;
int in2 = 8;
// motor two
int enB = 5;
int in3 = 7;
int in4 = 6;
int duration = 1000;

// Enable features
bool bMovement = true;
bool bLcd = false;
bool bTracking = false;
bool bBuzzer = false;
bool bWifi = false;
bool bCamera = false;

// Code from bluetooth
char code = 'F';
int speed = 255;
int speedRateVal = 10;

void setup() {
  
  // inicializar la comunicación serial a 9600 bits por segundo
  Serial.begin(9600);
  Serial.setTimeout(5);

  Serial.println("Car initiating!");
  
  // Configuramos los pines como salida
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
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

void backward(){
    Serial.println("Backward function start");
    analogWrite(enA, speed);
    analogWrite(enB, speed);
    
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    delay(20);

    Serial.println("backward function Stop");
}

void forward(){
  Serial.println("forward function start");
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
  Serial.println("Left function start");
  analogWrite(enA, speed);
  analogWrite(enB, 0);
  digitalWrite (in1, HIGH);
  digitalWrite (in2, LOW);
  digitalWrite (in3, HIGH);
  digitalWrite (in4, LOW);
}

void rightforward(){
  Serial.println("Right function start");
  analogWrite(enA, 0);
  analogWrite(enB, speed);
  digitalWrite (in1, HIGH);
  digitalWrite (in2, LOW);
  digitalWrite (in3, HIGH);
  digitalWrite (in4, LOW);
}

void leftbackward(){
  Serial.println("Left function start");
  analogWrite(enA, speed);
  analogWrite(enB, 0);
  digitalWrite (in1, LOW);
  digitalWrite (in2, HIGH);
  digitalWrite (in3, LOW);
  digitalWrite (in4, HIGH);
}

void rightbackward(){
  Serial.println("Right function start");
  analogWrite(enA, 0);
  analogWrite(enB, speed);
  digitalWrite (in1, LOW);
  digitalWrite (in2, HIGH);
  digitalWrite (in3, LOW);
  digitalWrite (in4, HIGH);
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