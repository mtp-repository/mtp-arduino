/*  
  Wall-e Version 1.0

  Author
    - Cenon Dinno Ebora III
    - cenon4dno@gmail.com

  Components
    - Arduino Uno
    - Car Chassis 
    - 2 way motor & 16 way servo
    - 2 DC motor
    - 1 Servo motor
    - 1 Ultrasonic Sensor
    - 4 AA batteries    
    - 1 powerbank

  Functionality:
  V1.0
    - Movement
        - Forward,
        - Right
        - Left
    - Check distance of front, left and right thru ultrasonic sensor and servo motor.
   V1.1
    - Infra distance
      - Add accuracy, help ultrasensor

  References:
  http://dronebotworkshop.com
*/

// Include packages
#include <Servo.h>

// Constants for Interrupt Pins

// Constant for steps in disk
const float stepcount = 20.00;  // 20 Slots in disk, change if different

// Constant for wheel diameter
const float wheeldiameter = 66.10; // Wheel diameter in millimeters, change if different

// PINS for motor
int in1 = 6;
int in2 = 9;
int enable = 1;

// PINS for IR
int IRSensor1 = 2; // Right IR sensor
int IRSensor2 = 3; // Left IR sensor

// PINS for ultra sensor
const int pingPin = 5; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 4; // Echo Pin of Ultrasonic Sensor

// PIN for servo
int servoPin = 10;

// Constant vars
int inchDistanceStop = 20;

// Create a servo object 
Servo Servo1;

// Function to convert from centimeters to steps
int CMtoSteps(float cm) {

  int result;  // Final calculation result
  float circumference = (wheeldiameter * 3.14) / 10; // Calculate wheel circumference in cm
  float cm_step = circumference / stepcount;  // CM per Step
  
  float f_result = cm / cm_step;  // Calculate result as a float
  result = (int) f_result; // Convert to an integer (note this is NOT rounded)
  
  return result;  // End and return result

}

// Function to Move Forward
void MoveForward() 
{  
   // Set Motor A forward
   digitalWrite(in1, HIGH);
   digitalWrite(in2, HIGH);
}

// Function to Move in Reverse
void MoveReverse() 
{  
   // Set Motor A reverse
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
}

// Function to Spin Right
void SpinRight() 
{  
   // Set Motor A reverse
  digitalWrite(in1, LOW); 
  // Set Motor B forward
  digitalWrite(in2, HIGH);     
}

// Function to Spin Left
void SpinLeft() 
{  
   // Set Motor A forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);   
}

void servoLook0() {
  Serial.println("Look 0 degrees");
   // Make servo go to 0 degrees 
   Servo1.write(0);
   delay(200);
}

void servoLook90() {  
   Serial.println("Look 90 degrees");
   // Make servo go to 90 degrees 
   Servo1.write(90);
   delay(200);
}

void servoLook180() {
  Serial.println("Look 180 degrees");
   // Make servo go to 180 degrees 
   Servo1.write(180);
   delay(200);
}

long getDistanceInInch() {
   long duration, inches, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);
   Serial.print(inches);
   Serial.print("in, ");

   return inches;
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

void setup() 
{ 
  // Test Motor Movement  - Experiment with your own sequences here  
  Serial.begin(9600); // Starting Serial Terminal
  Serial.println("Start Car!");
  Servo1.attach(servoPin);  

  // Set IR
  pinMode (IRSensor1, INPUT); // sensor pin INPUT
  pinMode (IRSensor2, INPUT); // sensor pin INPUT

  // Reset Servo to 90
  servoLook90();
} 

void loop() {
  Serial.println("Start Loop");
  
  // Move forward if 
  servoLook90();
  long distance = getDistanceInInch();
  while(distance > inchDistanceStop) {
    Serial.println("Keep moving forward");
    MoveForward();
    delay(170);
    distance = getDistanceInInch();
  }

  // Stop
  MoveReverse();
  Serial.println("STOOOOOOOOP");
  delay(170);
  
  // If distance is D <= inchDistanceStop
  // Evaluate left and right distance

  // Look right
  servoLook0();
  long rightDistance = getDistanceInInch();
  Serial.println("Distance 0deg: " + String(rightDistance));
  delay(500);

  // Get straight distance
  servoLook90();
  long distance90 = getDistanceInInch();
  Serial.println("Distance 90deg: " + String(distance90));
  delay(500);

  // Look right
  servoLook180();
  long leftDistance = getDistanceInInch();
  Serial.println("Distance 180deg: " + String(leftDistance));
  delay(500);

  servoLook90();

  // Reposition and decide which has more space
  int statusSensor1 = digitalRead (IRSensor1);
  Serial.println("IR 1: " + String(statusSensor1));
  int statusSensor2 = digitalRead (IRSensor2);
  Serial.println("IR 2:" + String(statusSensor2));
  
  if (statusSensor1 < 1 || statusSensor2 < 1) {
    MoveReverse();
    if (statusSensor1 < 1) {
      SpinLeft();
    } else {
      SpinRight();      
    }

    delay(300);
  } else if (distance90 > rightDistance && distance90 > leftDistance && distance90 > inchDistanceStop) {
    Serial.println("Keep moving forward");
    MoveForward();
    delay(180);
  } else if (distance90 < rightDistance && leftDistance < rightDistance && rightDistance > inchDistanceStop) {
    // Right has more space
    Serial.println("Turn Right");
    SpinRight();
    delay(180); // left motor seems slower than the right motor
  } else if (distance90 < leftDistance && rightDistance < leftDistance && leftDistance > inchDistanceStop) {
    // Left has more space
    Serial.println("Turn Left");
    SpinLeft();
    delay(180);
  } else {
    // U turn
    if (rightDistance > leftDistance) {
      Serial.println("U Turn to the right");
      SpinRight();  
    } else {
      Serial.println("U Turn to the left");
      SpinLeft();  
    }    
    delay(300);
  }

  // Reset Servo to 90
  Serial.println("Reset Servo");
  servoLook90();
  MoveReverse();
  delay(200);
}
