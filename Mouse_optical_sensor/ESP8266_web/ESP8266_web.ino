#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "sensor_functions.h"
#include "secrets.h"

#define SCK 4                 // Clock pin
#define SDIO 0                // Serial Data Input/Output (half-duplex)


//Libraries
#include <ESP8266WiFi.h>//https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/ESP8266WiFi.h
//Constants
#define LED 2
//Parameters
String request;
String nom = "ESP8266";
//Objects
WiFiServer server(80);

void handleRequest(WiFiClient client, String request) { /* function handleRequest */
  ////Handle web client request
  if (request.indexOf("/getImageMatrix") > 0)  {
    uint8_t matrix[18 * 18];
    getImageMatrix(matrix);
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); //  do not forget this one
    for (uint16_t i = 0; i < 18 * 18; i++) {
      client.print(matrix[i]);
      if (i != 18 * 18 - 1) {
        client.print(",");
      } else {
        client.println();
      }
    }
    client.println();
  }
}
void webpage(WiFiClient client) { /* function webpage */
  ////Send wbepage to client
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  //  client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
  //  client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
  client.println("</head>");
  client.println("<body>");
  client.print("<script type='text/javascript' src='");
  client.print(EXTERNAL_JS_FILE_REF);
  client.println("'></script>");
  client.println("</body></html>");
  client.println();
  delay(1);
}

void setup() {
  pinMode(SCK, OUTPUT);       // Clock is always under master control
  pinMode(SDIO, INPUT);       // High Z
/*
  Serial.begin(115200);

  while (millis() < 2000 && !Serial.available()) {
    Serial.println("Optical mouse hack!");;
  }*/

  write(0x00, 0b00000001);


  delay(1000);

  Serial.begin(115200);
  Serial.println(F("Initialize System"));
  //Init ESPBrowser
  Serial.print(F("Connecting to ")); Serial.println(ssid);
  WiFi.begin(ssid, password);
  // Connect to Wifi network.
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500); Serial.print(F("."));
  }
  server.begin();
  Serial.println();
  Serial.println(F("ESPBrowser initialized"));
  Serial.print(F("IP Address: "));
  Serial.println(WiFi.localIP());
  //Init WiFi server
  server.begin();
  /*
    uint8_t current_config = read(0x00);
    println_full_bin(current_config);
    delay(1);
    write(0x00, 0b00000001);
    delay(1);
    println_full_bin(read(0));
  */

  /*
    write(0x08, 0xff);

    int i = 0;
    while (i <= 324){
      delay(1);
      byte data = read(0x08);
      if (data & 0b01000000){
        Serial.print("Pixel data: ");
        if (data & 0b10000000){
          print_full_bin(data);
          Serial.println("   <-- First pixel");
        } else {
          println_full_bin(data);
        }
        i++;
      }
    }*/
}

void loop() {
  /*
    Serial.print("Product ID: ");
    Serial.print(read(0x01), BIN);
    Serial.print("   Inverse product ID: ");
    Serial.println(read(0x11), BIN);
  */
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  if (request != "GET / HTTP/1.1") {
    handleRequest(client, request);
  } else {
    webpage(client);//Return webpage
  }
  Serial.println("Loop");
}
