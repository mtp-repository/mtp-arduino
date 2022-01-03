/*  
  Wall-e Version 2.0

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

   Roadmap
    - Infrared
    - Tracking
    - Buzzer
    - WIFI     

  Library
    - 
    

  References:
  http://dronebotworkshop.com
  DC Motor/ L298N - https://arduinogetstarted.com/tutorials/arduino-dc-motor
*/

// Include Wire Library for I2C
#include <Wire.h>
// Include NewLiquidCrystal Library for I2C
#include <LiquidCrystal_I2C.h>

// Define LCD pinout
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;

// Define I2C Address - change if reqiuired
const int i2c_addr = 0x27;

LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

// connect motor controller pins to Arduino digital pins
// motor one
int enA = 10;
int in1 = 9;
int in2 = 8;
// motor two
int enB = 5;
int in3 = 7;
int in4 = 6;

void motorInit() {
  lcdMsg("Start Car!", 0, 1000);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  delay(2000);
  lcd.clear();
}

void lcdInit() {
  // Set display type as 16 char, 2 rows
  lcd.begin(16,2);

  lcdMsg("Love you Cookie!", 0, 1000);
  lcdMsg("Enjoy the ride", 1, 1000);

  // Clear the display
  lcd.clear();
}

void lcdMsg(String msg, int line ,int duration) {
  lcd.setCursor(line,0);
  lcd.print(msg);
  delay(duration);
  lcd.clear();
}

void forward(int speed, int duration) {
  lcdMsg("Forward", 0, 1000);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, speed);
  
  // turn on motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, speed);
  delay(duration);
}

void backward(int speed, int duration) {
  lcdMsg("Backward", 0, 1000);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, speed);
  
  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, speed);
  delay(duration);
}


void pause(int duration) {
  lcdMsg("Pause: " + String(duration) + "ms", 0, 1000);
  // turn off motor A
  digitalWrite(in1, LOW);  
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);
  
  // turn on motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enB, 0);
  
  delay(duration);
}

void left(int speed, int duration) {
  lcdMsg("Turn Left", 0, 1000);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, speed);
  
  // turn on motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, (speed/2));
  
  delay(duration);
}

void right(int speed, int duration) {
  lcdMsg("Turn Right", 0, 1000);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, (speed/2));
  
  // turn on motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, speed);
  
  delay(duration);
}

void setup()
{
  // set all the motor control pins to outputs
  Serial.begin(9600); // Starting Serial Terminal
  lcdInit();
  motorInit();
}

void loop()
{
  forward(255, 2000);
  backward(255, 2000);
  pause(2000);
  right(255, 3000);
  left(255, 3000);
  delay(1000);
}
