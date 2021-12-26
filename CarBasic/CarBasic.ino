/*  Arduino DC Motor Control - PWM | H-Bridge | L298N  -  Example 01
    by Dejan Nedelkovski, www.HowToMechatronics.com
*/
#define enA 5
#define in1 1
#define in2 8
#define button 4
int rotDirection = 0;
int pressed = true;

void setup() {
  Serial.println("Setup start!");
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(button, INPUT);
  
  // Set initial rotation direction
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
}

void loop() {
  Serial.println("Loop start!");
  int potValue = analogRead(A0); // Read potentiometer value
  Serial.println(potValue);
  int pwmOutput = map(potValue, 0, 1023, 0 , 255); // Map the potentiometer value from 0 to 255
  analogWrite(enA, pwmOutput); // Send PWM signal to L298N Enable pin
  
  // If button is pressed - change rotation direction
  if (pressed == true) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
    rotDirection = 1;
    delay(20);
  }
  
  Serial.println("Loop end!");
}
