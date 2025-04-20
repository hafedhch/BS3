#ifndef RS232_HANDLER_H
#define RS232_HANDLER_H

#include <Arduino.h>
#include "ConfigManager.h"
#include "MySerialConfig.h"
#include <SoftwareSerial.h>

// Define RS232 pins (change these as needed for your wiring)
#define RS232_RX_PIN D5
#define RS232_TX_PIN D6

class RS232Handler {
public:
  RS232Handler(MySerialConfig &config);
  void begin();
  void updateConfig(MySerialConfig &config);
  void handle();           // Read incoming data
  void write(uint8_t data);
  
  int available();         // Return number of available bytes
  int read();              // Read one byte

private:
  SoftwareSerial *ss;
  MySerialConfig currentConfig;
};

#endif
