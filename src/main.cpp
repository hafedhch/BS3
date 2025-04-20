#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <LittleFS.h>
#include "ConfigManager.h"
#include "RS232Handler.h"
#include "RS422Handler.h"
#include "WebInterface.h"

// Replace these with your actual WiFi credentials
const char* ssid = "Hafedh";
const char* password = "00060375";

ConfigManager configManager;
RS232Handler *rs232Handler;
RS422Handler *rs422Handler;
WebInterface *webInterface;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting NMEA Converter...");

  if (!LittleFS.begin()) {
    Serial.println("LittleFS mount failed");
  }

  // Load configuration (using default values for demo)
  configManager.load();

  // Initialize RS232 and RS422 handlers with current configurations
  rs232Handler = new RS232Handler(configManager.rs232Config);
  rs422Handler = new RS422Handler(configManager.rs422Config);
  
  rs232Handler->begin();
  rs422Handler->begin();


  // Set WiFi mode to Access Point
  WiFi.mode(WIFI_AP);
  // Start the access point 
  WiFi.softAP(ssid, password);

  Serial.print("Access Point started. IP address: ");
  Serial.println(WiFi.softAPIP());

  // Start the web server for configuration
  webInterface = new WebInterface(configManager);
  webInterface->begin();
}

void loop() {
  
  if (rs232Handler->available() > 0) {
    int received_byte = rs232Handler->read();
    rs422Handler->write(received_byte);
  }
  
  if (rs422Handler->available() > 0) {
    int received_byte = rs422Handler->read();
    rs232Handler->write(received_byte);
  }

  // Handle web server requests
  webInterface->handleClient();
  delay(10);
}
