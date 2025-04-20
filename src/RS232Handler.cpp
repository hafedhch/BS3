#include "RS232Handler.h"

RS232Handler::RS232Handler(MySerialConfig &config) : currentConfig(config) {
  // Create SoftwareSerial instance using defined RS232 pins.
  ss = new SoftwareSerial(RS232_RX_PIN, RS232_TX_PIN);
}

void RS232Handler::begin() {
  ss->begin(currentConfig.baud);
  // Note: Standard SoftwareSerial does not support inversion or custom framing.
}

void RS232Handler::updateConfig(MySerialConfig &config) {
  currentConfig = config;
  ss->end();
  ss->begin(currentConfig.baud);
}

void RS232Handler::handle() {
  while (ss->available()) {
    uint8_t c = ss->read();
    // For demo purposes, print received byte to hardware Serial.
    Serial.print("RS232 Received: ");
    Serial.println(c, HEX);
    // Optionally, forward data to RS422.
  }
}

void RS232Handler::write(uint8_t data) {
    ss->write(data);
  }
  
  int RS232Handler::available() {
    return ss->available();
  }
  
  int RS232Handler::read() {
    return ss->read();
  }
