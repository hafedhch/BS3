#ifndef RS422_HANDLER_H
#define RS422_HANDLER_H

#include <Arduino.h>
#include "ConfigManager.h"
#include "MySerialConfig.h"
#include <SoftwareSerial.h>

// Define RS422 pins (change these as needed for your wiring)
#define RS422_RX_PIN D1
#define RS422_TX_PIN D2

class RS422Handler {
public:
  RS422Handler(MySerialConfig &config);
  void begin();
  void updateConfig(MySerialConfig &config);
  void handle();
  void write(uint8_t data);
  
  int available();         // Return number of available bytes
  int read();              // Read one byte
private:
  SoftwareSerial *ss;
  MySerialConfig currentConfig;
};

#endif
