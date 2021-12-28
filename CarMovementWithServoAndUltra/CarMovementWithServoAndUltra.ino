/*  
  Robot Car with Speed Sensor Demonstration
  RobotCarSpeedSensorDemo.ino
  Demonstrates use of Hardware Interrupts
  to control motors on Robot Car
  
  DroneBot Workshop 2017
  http://dronebotworkshop.com
*/

// Constants for Interrupt Pins

// Constant for steps in disk
const float stepcount = 20.00;  // 20 Slots in disk, change if different

// Constant for wheel diameter
const float wheeldiameter = 66.10; // Wheel diameter in millimeters, change if different

// PINS for motor
int in1 = 6;
int in2 = 9;

// PINS for ultra sensor
const int pingPin = 5; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 4; // Echo Pin of Ultrasonic Sensor

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
void MoveForward(int steps, int mspeed) 
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
void SpinRight(int steps, int mspeed) 
{  
   // Set Motor A reverse
  digitalWrite(in1, LOW); 
  // Set Motor B forward
  digitalWrite(in2, HIGH);     
}

// Function to Spin Left
void SpinLeft(int steps, int mspeed) 
{  
   // Set Motor A forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);   
}

void setup() 
{ 
  // Test Motor Movement  - Experiment with your own sequences here  
  Serial.begin(9600); // Starting Serial Terminal
  Serial.println("Start Car!");
} 


void loop()
{
  Serial.println("Enter loop!");
  // Put whatever you want here!
  long distance = getDistanceInInch();
  Serial.println("Distance: " + String(distance) + "inch");
  if(distance > 5) {
    MoveForward(CMtoSteps(50), 255);  // Forward half a metre at 255 speed
  } else {
    MoveReverse();
  }

  delay(1000);  // Wait one second
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
