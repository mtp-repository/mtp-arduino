/*  
  Robot Car with Speed Sensor Demonstration
  RobotCarSpeedSensorDemo.ino
  Demonstrates use of Hardware Interrupts
  to control motors on Robot Car
  
  DroneBot Workshop 2017
  http://dronebotworkshop.com
*/

// Constants for Interrupt Pins
// Change values if not using Arduino Uno

const byte MOTOR_A = 6;  // Motor 2 Interrupt Pin - INT 1 - Right Motor
const byte MOTOR_B = 9;  // Motor 1 Interrupt Pin - INT 0 - Left Motor

// Constant for steps in disk
const float stepcount = 20.00;  // 20 Slots in disk, change if different

// Constant for wheel diameter
const float wheeldiameter = 66.10; // Wheel diameter in millimeters, change if different

// Integers for pulse counters
volatile int counter_A = 0;
volatile int counter_B = 0;


int enA = 10;
int in1 = 6;
int in2 = 9;

// Interrupt Service Routines

// Motor A pulse count ISR
void ISR_countA()  
{
  counter_A++;  // increment Motor A counter value
} 

// Motor B pulse count ISR
void ISR_countB()  
{
  counter_B++;  // increment Motor B counter value
}

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
   counter_A = 0;  //  reset counter A to zero
   counter_B = 0;  //  reset counter B to zero
   
   // Set Motor A forward
   digitalWrite(in1, HIGH);
   digitalWrite(in2, HIGH);
}

// Function to Move in Reverse
void MoveReverse(int steps, int mspeed) 
{
   counter_A = 0;  //  reset counter A to zero
   counter_B = 0;  //  reset counter B to zero
   
   // Set Motor A reverse
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  

}

// Function to Spin Right
void SpinRight(int steps, int mspeed) 
{
   counter_A = 0;  //  reset counter A to zero
   counter_B = 0;  //  reset counter B to zero
   
   // Set Motor A reverse
  digitalWrite(in1, LOW);
  

  // Set Motor B forward
  digitalWrite(in2, HIGH);     

}

// Function to Spin Left
void SpinLeft(int steps, int mspeed) 
{
   counter_A = 0;  //  reset counter A to zero
   counter_B = 0;  //  reset counter B to zero
   
   // Set Motor A forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);   
}

void setup() 
{
  // Attach the Interrupts to their ISR's
  attachInterrupt(digitalPinToInterrupt (MOTOR_A), ISR_countA, RISING);  // Increase counter A when speed sensor pin goes High
  attachInterrupt(digitalPinToInterrupt (MOTOR_B), ISR_countB, RISING);  // Increase counter B when speed sensor pin goes High
  
  // Test Motor Movement  - Experiment with your own sequences here  
  
  MoveForward(CMtoSteps(50), 255);  // Forward half a metre at 255 speed
  delay(1000);  // Wait one second
  MoveReverse(10, 255);  // Reverse 10 steps at 255 speed
  delay(1000);  // Wait one second
  MoveForward(10, 150);  // Forward 10 steps at 150 speed
  delay(1000);  // Wait one second
  MoveReverse(CMtoSteps(25.4), 200);  // Reverse 25.4 cm at 200 speed
  delay(1000);  // Wait one second
  SpinRight(20, 255);  // Spin right 20 steps at 255 speed
  delay(1000);  // Wait one second
  SpinLeft(60, 175);  // Spin left 60 steps at 175 speed
  delay(1000);  // Wait one second
  MoveForward(1, 255);  // Forward 1 step at 255 speed
} 


void loop()
{
  // Put whatever you want here!

  
}
