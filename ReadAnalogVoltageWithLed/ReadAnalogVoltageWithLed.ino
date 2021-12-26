/*
  ReadAnalogVoltageWithLed

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/ReadAnalogVoltage
  https://www.youtube.com/watch?v=xb_0QxeInDs
*/
#define LED 13
#define pot A0

int potReading = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(pot, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  potReading = analogRead(pot);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = potReading * (5.0 / 1023.0);
  // print out the value you read:
  Serial.println(voltage);
  analogWrite(LED, potReading);
}
