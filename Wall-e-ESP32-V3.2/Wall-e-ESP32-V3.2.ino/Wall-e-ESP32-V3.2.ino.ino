/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "Cookie_Asus";
const char* password = "dinnohoney678";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;
int currentLoop = 0;
int myTimeOut = 0;

// Include settings of features
#include "car_movement_settings.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Car Movement initiating!");
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.setTimeout(myTimeOut);
  server.begin();  
}

void loop(){ 
  WiFiClient client = server.available();   // Listen for incoming clients  
  client.setTimeout(myTimeOut);

  if (currentLoop == 0) {
    // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
    // and a content-type so the client knows what's coming, then a blank line:
    Serial.println("testx " + String(currentLoop));
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();
  }
  
  if (client) {                             // If a new client connects,
    while (client.available()) {  // loop while the client's connected      
        Serial.println("test " + String(currentLoop));
        String c = client.readString();        // read a byte, then
        Serial.println("test2");
        //Serial.println(c);                    // print it out the serial monitor
        Serial.println("test3");
        header = c;
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (header.indexOf("GET /F") >= 0) {
              forward();
            } else if (header.indexOf("GET /G") >= 0) {
              backward();
            } else if (header.indexOf("GET /R") >= 0) {
              rightforward();
            } else if (header.indexOf("GET /L") >= 0) {
              leftforward();
            } else if (header.indexOf("GET /S") >= 0) {
              stop();
            } else if (header.indexOf("GET /U") >= 0) {
              increaseSpeed();
            } else if (header.indexOf("GET /D") >= 0) {
              decreaseSpeed();
            } else if (header.indexOf("GET /K") >= 0) {
              stop();
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Wifi Car Controller</h1>");

            
            // Move Buttons
            client.println("<div style=\"display:inline-block\"><table>");
            client.println("<tr>");
            client.println("<td rowspan=2><a href=\"/L\"><button class=\"button\">&#8592;</button></a></td>");
            client.println("<td><a href=\"/F\"><button class=\"button\">&#8593;</button></a></td>");
            client.println("<td rowspan=2><a href=\"/R\"><button class=\"button\">&#8594;</button></a></td>");
            client.println("</tr>");

            client.println("<tr>");
            client.println("<td><a href=\"/G\"><button class=\"button\">&#8595;</button></a></td>");
            client.println("</tr>");
            client.println("</table></div>");

            // Option Button
            client.println("<div style=\"display:inline-block\"><table>");
            client.println("<tr>");
            client.println("<td rowspan=2><a href=\"/S\"><button class=\"button\" style=\"border-radius: 50px\">S</button></a></td>");
            client.println("<td><a href=\"/U\"><button class=\"button\" style=\"border-radius: 50px\">U</button></a></td>");
            client.println("<td rowspan=2><a href=\"/K\"><button class=\"button\" style=\"border-radius: 50px\">K</button></a></td>");
            client.println("</tr>");

            client.println("<tr>");
            client.println("<td><a href=\"/D\"><button class=\"button\" style=\"border-radius: 50px\">D</button></a></td>");
            client.println("</tr>");
            client.println("</table></div>");
            
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
    }
    currentLoop += 1;
    // Clear the header variable
    header = "";
  }
}

void forward(){
  Serial.println("Forward");

  analogWrite(enA, speed);
  analogWrite(enB, speed);
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void backward(){
  Serial.println("Back");

  analogWrite(enA, speed);
  analogWrite(enB, speed);

  digitalWrite (in1, HIGH);
  digitalWrite (in2, LOW);
  digitalWrite (in3, HIGH);
  digitalWrite (in4, LOW);
}

void stop(){
  Serial.println("Stop");

  analogWrite(enA, 100);
  analogWrite(enB, 100);

  digitalWrite (in1, LOW);
  digitalWrite (in2, LOW);
  digitalWrite (in3, LOW);
  digitalWrite (in4, LOW);
}

void leftforward(){
  Serial.println("Left-forward");
  
  analogWrite(enA, speed);
  analogWrite(enB, 0);

  digitalWrite (in1, LOW);
  digitalWrite (in2, HIGH);
  digitalWrite (in3, LOW);
  digitalWrite (in4, HIGH);
}

void rightforward(){
  Serial.println("Right-forward");

  analogWrite(enA, 0);
  analogWrite(enB, speed);
  
  digitalWrite (in1, LOW);
  digitalWrite (in2, HIGH);
  digitalWrite (in3, LOW);
  digitalWrite (in4, HIGH);
}

void leftbackward(){
  Serial.println("Left-backward");
  analogWrite(enA, speed);
  analogWrite(enB, 0);

  digitalWrite (in1, LOW);
  digitalWrite (in2, HIGH);
  digitalWrite (in3, LOW);
  digitalWrite (in4, HIGH);
}

void rightbackward(){
  Serial.println("Right-backward");
  analogWrite(enA, 0);

  analogWrite(enB, speed);
  digitalWrite (in1, LOW);
  digitalWrite (in2, HIGH);
  digitalWrite (in3, LOW);
  digitalWrite (in4, HIGH);
}

void increaseSpeed() {
  Serial.println("Speed Up");
  if (speed < 255) {
    speed = speed + speedRateVal;
  }
}

void decreaseSpeed() {
  Serial.println("Speed Down");
  if (speed > speedRateVal) {
    speed = speed - speedRateVal;
  }
}