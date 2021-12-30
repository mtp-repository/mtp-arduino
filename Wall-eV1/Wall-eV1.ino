/*  
  Wall-e Version 1.0

  Components
    - Arduino Uno
    - Car Chassis 
    - 2 way motor & 16 way servo
    - 2 DC motor
    - 1 Servo motor
    - 1 Ultrasonic Sensor
    - 4 AA batteries    
    - 1 powerbank

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

  // Reset Servo to 90
  servoLook90();
} 

void loopTest() {
  Serial.println("Start Loop");
  Serial.println("enable " + String(enable));
  if (enable == 1) {
    MoveForward();
    delay(170);
    enable = 0;
    MoveReverse();
  }
  Serial.println("enable " + String(enable));
  Serial.println("End Loop");  
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
  if (distance90 > rightDistance && distance90 < leftDistance && distance90 > inchDistanceStop) {
    Serial.println("Keep moving forward");
    MoveForward();
    delay(170);
  } else if (distance90 < rightDistance && leftDistance < rightDistance && rightDistance > inchDistanceStop) {
    // Right has more space
    Serial.println("Turn Right");
    SpinRight();
    //delay(500); // left motor seems slower than the right motor
  } else if (distance90 < leftDistance && rightDistance < leftDistance && leftDistance > inchDistanceStop) {
    // Left has more space
    Serial.println("Turn Left");
    SpinLeft();
    delay(180);
  } else {
    // U turn
    Serial.println("U Turn");
    SpinLeft();
    delay(300);
  }

  // Reset Servo to 90
  Serial.println("Reset Servo");
  servoLook90();
  MoveReverse();
  delay(200);
}

void oldloop() {
   Serial.println("Enter loop!");
  // Put whatever you want here!
  long distance = getDistanceInInch();
  Serial.println("Distance: " + String(distance) + "inch");
  if(distance >= 20) {
    Serial.println("Forward");
    MoveForward();  // Forward half a metre at 255 speed
    delay(400);
  } else {
    Serial.println("Stop");
    MoveReverse();

    Serial.println("Look 90");
    servoLook90();
    long distance90 = getDistanceInInch();
    delay(1000);
    Serial.println("Look 0");
    servoLook0();    
    long distance0 = getDistanceInInch();
    delay(1000);
    Serial.println("Look 180");
    servoLook180();
    long distance180 = getDistanceInInch();
    delay(1000);
    Serial.println("distance 0 = " + String(distance0) + " <--- > distance 180 = " + String(distance180));

    if ((distance90 > distance180) && (distance90 > distance0) && (distance90 >= 20)) {
      Serial.println("Forward");
      MoveForward();  // Forward half a metre at 255 speed
      delay(400);
    } else if ((distance0 > distance90) && (distance0 > distance90) && (distance0 >= 20)) {
      Serial.println("Turn Right");
      SpinRight();
      delay(400);
    } else if ((distance180 > distance0) && (distance180 > distance90) && (distance180 >= 20)) {
      Serial.println("Turn Left");
      SpinLeft();
      delay(400);
    } else {
      MoveReverse();
      if (distance0 > distance180) {
        Serial.println("Uturn right");
        SpinRight();      
      } else {
        Serial.println("Uturn left");
        SpinLeft();  
      }      
      delay(700);
    }    
    // Reset - look forward
    servoLook90();
    
  }
}
