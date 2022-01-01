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
    - 1 powerbank

  Functionality:
    - Movement
        - Forward,
        - Right
        - Left
    - Check distance of front, left and right thru ultrasonic sensor and servo motor.
    

  References:
  http://dronebotworkshop.com
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

  lcdMsg("Dinno's world!", 0, 1000);
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

void demoOne()
{
  lcdMsg("Start Demo1", 1, 1000);
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200);
  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 200);
  delay(2000);
  // now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  delay(2000);
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

 lcdMsg("End Demo1", 1, 1000);
}
void demoTwo()
{
  lcdMsg("Start Demo2", 1, 1000);
  
  // this function will run the motors across the range of possible speeds
  // note that maximum speed is determined by the motor itself and the operating voltage
  // the PWM values sent by analogWrite() are fractions of the maximum speed possible 
  // by your hardware
  // turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  // accelerate from zero to maximum speed

 for (int i = 0; i < 256; i++) { 
  analogWrite(enA, i); 
  analogWrite(enB, i); 
  delay(20); 
  } 
// decelerate from maximum speed to zero 
for (int i = 255; i > 0; --i)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  } 

 
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);  

  lcdMsg("End Demo2", 1, 1000);
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
  demoOne();
  delay(1000);
  demoTwo();
  delay(1000);
}
