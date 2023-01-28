/*
 * Created by Dinno Ebora
 *
 * Notes
 * Analog Value ranges from 0-1023
 * Voltage ranges from 0-5
 *
 * Minor turn 
 * Approx Value per knob turn + 32
 * Approx Voltage per knob turn + .16
 *
 * Reference: https://arduinogetstarted.com/tutorials/arduino-potentiometer-triggers-servo-motor
 */

#include <Servo.h>

// constants for potentionmeter
const int POTENTIOMETER_PIN1   = A0; // Arduino pin connected to Potentiometer pin
const int POTENTIOMETER_PIN2   = A1;
const int POTENTIOMETER_PIN3   = A2;
const int POTENTIOMETER_PIN4   = A3;
const int POTENTIOMETER_PIN5   = A4;
const int POTENTIOMETER_PIN6   = A5;
// constants for servo
const int SERVO_PIN1           = 6; // Arduino pin connected to Servo Motor's pin
const int SERVO_PIN2           = 4;
const int SERVO_PIN3           = 5;
const int SERVO_PIN4           = 6;
const int SERVO_PIN5           = 7;
const int SERVO_PIN6           = 8;
//
int analogPrevValue = 0;
int servoPosition = 0;
int servoConstant1 = 7.5; // for servo 1 - 7.5, servo 2 = 7.5, , servo 3 = 7.5, , servo 4 = 7.5, , servo 5 = 3, , servo 6 = 7.5
int servoConstant2 = 7.5;
int servoConstant3 = 7.5;
int servoConstant4 = 7.5;
int servoConstant5 = 3;
int servoConstant6 = 3;


Servo servo; // create servo object to control a servo

void setup() {
  Serial.begin(9600); // Initialize UART with 9600 Baud rate
  servo.attach(SERVO_PIN1);   // attaches the servo on pin 9 to the servo object
  servo.write(servoPosition);
}

void loop() {
  // Check potentionmeter1
  moveServo(checkPotentiometer(POTENTIOMETER_PIN1), servoConstant1, 1);
}

int checkPotentiometer(int potentionmeter) {
  return analogRead(potentionmeter);      // read the input on analog pin
}

void moveServo(int analogValue, int servoConstant, int servoId) {
    int newPosition = servoPosition + (analogValue/servoConstant);
    switch(servoId) {
      case 1: 
        servo.write(newPosition);
        Serial.println("New servo1 position: " + String(newPosition));
        break;
       case 2: 
        servo.write(newPosition);
        Serial.println("New servo1 position: " + String(newPosition));
        break;
      case 3: 
        servo.write(newPosition);
        Serial.println("New servo1 position: " + String(newPosition));
        break;
      case 4: 
        servo.write(newPosition);
        Serial.println("New servo1 position: " + String(newPosition));
        break;
      case 5: 
        servo.write(newPosition);
        Serial.println("New servo1 position: " + String(newPosition));
        break;
      case 6: 
        servo.write(newPosition);
        Serial.println("New servo1 position: " + String(newPosition));
        break;
    }
}


