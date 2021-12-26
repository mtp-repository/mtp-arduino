/*
* Source:
* https://create.arduino.cc/projecthub/pibots555/how-to-connect-dht11-sensor-with-arduino-uno-f4d239
* https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button
*/

#include "DHT.h"
// Include Wire Library for I2C
#include <Wire.h>
// Include NewLiquidCrystal Library for I2C
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define buttonPin 4
#define DHTTYPE DHT11   // DHT 11

// Define LCD pinout
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;

// Define I2C Address - change if reqiuired
const int i2c_addr = 0x27;

// variable for reading the pushbutton status
int buttonState = 0;

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);


void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  pinMode(buttonPin, INPUT);
  lcdSetup();

  dht.begin();
}

void loop() {
  buttonState = digitalRead(buttonPin);
  Serial.println("Button State:" +  String(buttonState)); 
  if (buttonState == HIGH) {
    // Wait a few seconds between measurements.
    delay(2000);
  
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    float f = dht.readTemperature(true);
  
    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
  
    // Compute heat index in Fahrenheit (the default)
    float hif = dht.computeHeatIndex(f, h);
    // Compute heat index in Celsius (isFahreheit = false)
    float hic = dht.computeHeatIndex(t, h, false);

    String lcdMsg1 = "H: " + String(h) + " T: " + String(t);
    String lcdMsg2 = "Heat: " + String(hic);
    lcdPrint(lcdMsg1, lcdMsg2);
    Serial.print(F(" Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.print(F("C "));
    Serial.print(f);
    Serial.print(F("F  Heat index: "));
    Serial.print(hic);
    Serial.print(F("C "));
    Serial.print(hif);
    Serial.println(F("F"));
  } else {
    Serial.println(F("Button State: LOW"));
  }
}

void lcdSetup() {
  
  // Set display type as 16 char, 2 rows
  lcd.begin(16,2);
  
  // Print on first row
  lcd.setCursor(0,0);
  lcd.print("Dinno's world!");
  
  // Wait 1 second
  delay(1000);
  
  // Print on second row
  lcd.setCursor(0,1);
  lcd.print("Enjoy the ride");
  
  // Wait 8 seconds
  delay(2000);
  
  // Clear the display
  lcd.clear();
}

void lcdPrint(String line1, String line2) {
  lcd.setCursor(0,0);
  lcd.print(line1);
  lcd.setCursor(0,1);
  lcd.print(line2);
  delay(10000);
  lcd.clear();
}
