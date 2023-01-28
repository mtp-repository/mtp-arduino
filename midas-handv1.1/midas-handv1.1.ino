/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-potentiometer-triggers-servo-motor
 */

#include <Servo.h>

// constants won't change
const int POTENTIOMETER_PIN   = A0; // Arduino pin connected to Potentiometer pin
const int SERVO_PIN           = 6; // Arduino pin connected to Servo Motor's pin
const float VOLTAGE_THRESHOLD = 2.5; // Voltages
int analogPrevValue = 0;
int servoPosition = 0;

Servo servo; // create servo object to control a servo

void setup() {
  Serial.begin(9600); // Initialize UART with 9600 Baud rate
  servo.attach(SERVO_PIN);   // attaches the servo on pin 9 to the servo object
  servo.write(servoPosition);
}

void loop() {
  int analogValue = analogRead(POTENTIOMETER_PIN);      // read the input on analog pin
  float voltage = floatMap(analogValue, 0, 1023, 0, 5); // Rescale to potentiometer's voltage
  int analogValueDiff = 0;
  //Serial.println("Voltage: " + String(voltage));

  // analog Value ranges from 0-1023
  // voltage ranges from 0-5

  //Minor turn 
  // Value + 32
  // Voltage + .16

  // if(voltage > VOLTAGE_THRESHOLD)
  //   servo.write(0); // rotate servo motor to 90 degree
  // else if () 
  // else
  //   servo.write(90);  // rotate servo motor to 0 degree

  if (analogPrevValue != analogValue) {
    analogValueDiff = analogValue - analogPrevValue;
    Serial.println("Difference: " + String(analogValueDiff));
  }

  if (analogValueDiff != 0) {
    int newPosition = servoPosition + (analogValueDiff/7.5);
    servo.write(newPosition);
    Serial.println("New servo position: " + String(newPosition));
  }
}

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



