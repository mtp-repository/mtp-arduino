#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>
#define ESP8266_BAUD 9600

char auth[] = "WqUjECVtZc28mF7pidl-2zrhDoA9aQlN";
char ssid[] = "Cookie_Asus"; //You can replace the wifi name to your wifi 

char pass[] = "dinnohoney678";  //Type password of your wifi.

SoftwareSerial EspSerial(2, 3); // RX, TX
//WidgetLCD lcd(V0);

ESP8266 wifi(&EspSerial);

void setup()
{

  Serial.begin(9600);
  EspSerial.begin(ESP8266_BAUD);
  EspSerial.write("AT+CIOBAUD=9600");
  Blynk.begin(auth, wifi, ssid, pass);
   //lcd.clear();
// lcd.print(1, 1, "IoT");
}

void loop()
{
  Blynk.run();
}
