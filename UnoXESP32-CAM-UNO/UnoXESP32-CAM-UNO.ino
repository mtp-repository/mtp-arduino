// https://forum.arduino.cc/t/esp32-sending-string-to-arduino-uno/693074
// https://www.programmingboss.com/2021/04/esp32-arduino-serial-communication-with-code.html

// this sample code provided by www.programmingboss.com
void setup() {
  Serial.begin(9600);
}
void loop() {
  Serial.println("Hello Boss");
  Serial.println(Serial.readString());
  delay(1500);
}