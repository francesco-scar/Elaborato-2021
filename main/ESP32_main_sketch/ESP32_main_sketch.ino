#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "secrets.h"

//#define DEFAULT_MATRIX_TEST

#define FORMAT_FILESYSTEM false
#include <SPIFFS.h>

#define GRADIENT_DESCENT_ITERATIONS 512

#define SCK 23                  // Clock pin
#define SDIO 22                 // Serial Data Input/Output (half-duplex)

#define DIR_H 33                // Direction pin for horiziontal motor
#define STEP_H 32               // Step pin for horiziontal motor
#define ENABLE_H 13             // Enable pin for horizzontal motor (active low)

#define DIR_V 14                // Direction pin for vertical motor
#define STEP_V 12               // Step pin for vertical motor
#define ENABLE_V 13             // Enable pin for vertical motor (active low)

// Set web server port number to 80
WebServer server(80);


uint32_t last_t = 0;


void setup() {
  pinMode(SCK, OUTPUT);       // Clock is always under master control
  pinMode(SDIO, INPUT);       // High Z
  pinMode(DIR_H, OUTPUT);
  pinMode(STEP_H, OUTPUT);
  pinMode(ENABLE_H, OUTPUT);
  pinMode(DIR_V, OUTPUT);
  pinMode(STEP_V, OUTPUT);
  pinMode(ENABLE_V, OUTPUT);

  digitalWrite(DIR_H, LOW);
  digitalWrite(STEP_H, LOW);
  digitalWrite(ENABLE_H, HIGH);
  digitalWrite(DIR_V, LOW);
  digitalWrite(STEP_V, LOW);
  digitalWrite(ENABLE_V, HIGH);
  Serial.begin(115200);


  SPIFFS.begin();
  {
    File root = SPIFFS.open("/");
    File file = root.openNextFile();
    while (file) {
      String fileName = file.name();
      size_t fileSize = file.size();
      Serial.printf("FS File: %s, size: %s\n", fileName.c_str(), formatBytes(fileSize).c_str());
      file = root.openNextFile();
    }
    Serial.printf("\n");
  }

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
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
  
  #ifndef DISABLE_LCD
    init_display();
  #endif

  mDNS("solar_cooker");

  server.on("/getImageMatrix", HTTP_GET, imageMatrixRequest);
  server.on("/moveStepper", HTTP_GET, moveStepperHandler);
  server.on("/disableStepper", HTTP_GET, disableStepperHandler);
  server.on("/getTemperature", HTTP_GET, getTemperature);
  
  server.onNotFound([]() {
    if (!handleFileRead(server.uri())) {
      server.send(404, "text/plain", "FileNotFound");
    }
  });

  server.begin();
  #ifndef DEFAULT_MATRIX_TEST
    Serial.print("Get first image... ");
    getImageMatrix();
    Serial.println("Done!");
  #endif
}

void loop() {
  server.handleClient();
  delay(200);

  #ifndef DISABLE_LCD
    updateLCD();
  #endif
}
