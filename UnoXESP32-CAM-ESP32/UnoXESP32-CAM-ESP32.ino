// this sample code provided by www.programmingboss.com
#define RXp2 16
#define TXp2 0
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
}
void loop() {
    Serial.println("Message Received: ");
    Serial.println(Serial2.readString());
    Serial2.println("Test ESP32 msg");
}