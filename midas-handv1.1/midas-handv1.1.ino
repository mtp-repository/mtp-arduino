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
const int SERVO_PIN1           = 3; // Arduino pin connected to Servo Motor's pin
const int SERVO_PIN2           = 4;
const int SERVO_PIN3           = 5;
const int SERVO_PIN4           = 6;
const int SERVO_PIN5           = 7;
const int SERVO_PIN6           = 8;
//
int analogPrevValue = 0;
int servoPosition = 0;
int servoPosition1 = 0;
int servoPosition2 = 0;
int servoPosition3 = 0;
int servoPosition4 = 0;
int servoPosition5 = 0;
int servoPosition6 = 0;
int servoConstant1 = 7.5; // for servo 1 - 7.5, servo 2 = 7.5, , servo 3 = 7.5, , servo 4 = 7.5, , servo 5 = 3, , servo 6 = 7.5
int servoConstant2 = 7.5;
int servoConstant3 = 7.5;
int servoConstant4 = 7.5;
int servoConstant5 = 3;
int servoConstant6 = 3;


Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6; // create servo object to control a servo

void setup() {
  Serial.begin(9600); // Initialize UART with 9600 Baud rate
  Serial.println("Boot up");
  servo1.attach(SERVO_PIN1);
  servo1.write(servoPosition1);
  servo2.attach(SERVO_PIN2);
  servo2.write(servoPosition2);
  servo3.attach(SERVO_PIN3);
  servo3.write(servoPosition3);
  // servo4.attach(SERVO_PIN4);
  // servo4.write(servoPosition);
  // servo5.attach(SERVO_PIN5);
  // servo5.write(servoPosition);
  // servo6.attach(SERVO_PIN6);
  // servo6.write(servoPosition);
}

void loop() {
  // Check potentionmeter1
  moveServo(checkPotentiometer(POTENTIOMETER_PIN1), servoConstant1, 1);
  moveServo(checkPotentiometer(POTENTIOMETER_PIN2), servoConstant2, 2);
  moveServo(checkPotentiometer(POTENTIOMETER_PIN3), servoConstant3, 3);
  // moveServo(checkPotentiometer(POTENTIOMETER_PIN4), servoConstant4, 4);
  // moveServo(checkPotentiometer(POTENTIOMETER_PIN5), servoConstant5, 5);
  // moveServo(checkPotentiometer(POTENTIOMETER_PIN6), servoConstant6, 6);
}

int checkPotentiometer(int potentionmeter) {
  int analog = analogRead(potentionmeter);      // read the input on analog pin
  Serial.println("New " + String(potentionmeter) +" position: " + String(analog));
  return analog;
}

void moveServo(int analogValue, int servoConstant, int servoId) {
    int newPosition = 0;
    switch(servoId) {
      case 1: 
        newPosition = servoPosition1 + (analogValue/servoConstant);
        servo1.write(newPosition);
        //Serial.println("New servo1 position: " + String(newPosition));
        break;
       case 2: 
        newPosition = servoPosition2 + (analogValue/servoConstant);
        servo2.write(newPosition);
        //Serial.println("New servo2 position: " + String(newPosition));
        break;
      case 3: 
        newPosition = servoPosition3 + (analogValue/servoConstant);
        servo3.write(newPosition);
        //Serial.println("New servo3 position: " + String(newPosition));
        break;
      case 4: 
        newPosition = servoPosition4 + (analogValue/servoConstant);
        servo4.write(newPosition);
        Serial.println("New servo4 position: " + String(newPosition));
        break;
      case 5: 
        newPosition = servoPosition5 + (analogValue/servoConstant);
        servo5.write(newPosition);
        Serial.println("New servo5 position: " + String(newPosition));
        break;
      case 6: 
        newPosition = servoPosition6 + (analogValue/servoConstant);
        servo6.write(newPosition);
        Serial.println("New servo6 position: " + String(newPosition));
        break;
    }
}


