#include <ArduinoJson.h>

#include <Arduino_JSON.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif

#include "config.h"

unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

String clashStatus;

String clashProxy;
float clashArray[9];
const char* proxySetting = "mode";
String upData;

struct payload{
  int payload1;
  int payload2;
};
payload clashTraffic;
void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 25);

  WiFi.begin(ssid, password);
  display.clearDisplay();
  display.println("Connecting");
  display.display();
  delay(100);
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    display.print(".");
    display.display();
  }
  display.clearDisplay();
  display.setCursor(15, 25);
  display.print("WiFi: ");
  display.print(ssid);
  display.display();
  display.setCursor(15, 35);
  display.print("IP:   ");
  display.print(WiFi.localIP());
  display.display();
  
  delay(5000);
}
void loop() {
  //Send an HTTP POST request every 10 minutes
    if(WiFi.status()== WL_CONNECTED){          
      clashStatus = httpGETRequest(serverName);
      clashTraffic = httpGETRequest2(serverName2);
      display.clearDisplay();
      JSONVar myMode = JSON.parse(clashStatus);
//      int myTraffic = clashTraffic;
      if (JSON.typeof(myMode) == "undefined") {
        display.clearDisplay();
        display.println("Mode Parsing input failed!");
        display.display();
        delay(5000);
        return;
      } 
      Serial.print("clashTraffic: ");
      Serial.println(clashTraffic.payload1);
      display.clearDisplay();
      display.setCursor(0,1);  
      display.print("Proxy Mode = ");
      JSONVar value = myMode[proxySetting];
      display.println(value);
      display.println("");
      display.print("Up:    ");
      
      if ((clashTraffic.payload1 >= 0) && (clashTraffic.payload1 <= 1000)){
          display.setTextSize(2);
          display.print(clashTraffic.payload1);
          display.setTextSize(1);
          display.println("B/s");
      }
      else if ((clashTraffic.payload1 >= 1001) && (clashTraffic.payload1 <= 999999)){
          display.setTextSize(2);
          display.print((clashTraffic.payload1/1000));
          display.setTextSize(1);
          display.println("KB/s");
      }
      else if ((clashTraffic.payload1 >= 1000000) && (clashTraffic.payload1 <= 99999999)){
          display.setTextSize(2);
          display.print((clashTraffic.payload1/1000000));
          display.setTextSize(1);
          display.println("MB/s");
      }
      else{
          display.print((clashTraffic.payload1/100000000));
          display.println("GB/s");
      }
      
      
//      display.println(upval);
      display.println("");
      display.println("");
      display.print("Down:  ");
      if ((clashTraffic.payload2 >= 0) && (clashTraffic.payload2 <= 1000)){
          display.setTextSize(2);
          display.print(clashTraffic.payload2);
          display.setTextSize(1);
          display.println("B/s");
      }
      else if ((clashTraffic.payload2 >= 1001) && (clashTraffic.payload2 <= 999999)){
          display.setTextSize(2);
          display.print((clashTraffic.payload2/1000));
          display.setTextSize(1);
          display.println("KB/s");
      }
      else if ((clashTraffic.payload2 >= 1000000) && (clashTraffic.payload2 <= 999999999)){
          display.setTextSize(2);
          display.print((clashTraffic.payload2/1000000));
          display.setTextSize(1);
          display.println("MB/s");
      }
      else{
          display.setTextSize(2);
          display.print((clashTraffic.payload2/100000000));
          display.setTextSize(1);
          display.println("GB/s");
      }


      
//      JSONVar downval = myTraffic["down"];
//      display.println(downval);
      display.display();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
}

String httpGETRequest(const char* serverName) {
  HTTPClient http; 
  http.begin(serverName);
  http.addHeader("Authorization", "Bearer 123456");
  int httpResponseCode = http.GET(); 
  String payload = "{}"; 
  if (httpResponseCode>0) {
//    Serial.print("HTTP Response code: ");
//    Serial.println(httpResponseCode);
//    Serial.println("Proxy Mode Recieved");
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  return payload;
}



payload httpGETRequest2(const char* serverName) {
  HTTPClient http; 
  http.useHTTP10(true);
  http.begin(serverName);
  http.addHeader("Authorization", "Bearer 123456");
  int httpResponseCode = http.GET();
  payload p;
  p.payload1 = 0; 
  p.payload2 = 0; 
  if (httpResponseCode>0) {
//    Serial.print("HTTP Response code: ");
//    Serial.println(httpResponseCode);
    DynamicJsonDocument doc(128);
    deserializeJson(doc, http.getStream());
//    Serial.println(doc["up"].as<String>());
//    Serial.println(doc["down"].as<String>());
    p.payload1 = doc["up"].as<int>();
    p.payload2 = doc["down"].as<int>();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
//  Serial.println("WTF ARE YOU: ");
//  Serial.println(payload);
  return p;
}
