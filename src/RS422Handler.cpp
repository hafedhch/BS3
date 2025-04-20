#include "RS422Handler.h"

RS422Handler::RS422Handler(MySerialConfig &config) : currentConfig(config) {
  ss = new SoftwareSerial(RS422_RX_PIN, RS422_TX_PIN);
}

void RS422Handler::begin() {
  ss->begin(currentConfig.baud);
}

void RS422Handler::updateConfig(MySerialConfig &config) {
  currentConfig = config;
  ss->end();
  ss->begin(currentConfig.baud);
}

void RS422Handler::handle() {
  while (ss->available()) {
    uint8_t c = ss->read();
    Serial.print("RS422 Received: ");
    Serial.println(c, HEX);
  }
}

void RS422Handler::write(uint8_t data) {
    ss->write(data);
  }
  
  int RS422Handler::available() {
    return ss->available();
  }
  
  int RS422Handler::read() {
    return ss->read();
  }
