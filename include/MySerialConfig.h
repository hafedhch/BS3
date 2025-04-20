#ifndef MY_SERIAL_CONFIG_H
#define MY_SERIAL_CONFIG_H

#include <Arduino.h>

// Use a unique name to avoid conflicts.
struct MySerialConfig {
  uint32_t baud;       // Baud rate (e.g. 4800, 9600, etc.)
  bool inverse;        // If true, signal inversion is enabled.
  uint8_t dataBits;    // Typically 8
  uint8_t parity;      // 0 = none, 1 = odd, 2 = even (not used by SoftwareSerial)
  uint8_t stopBits;    // Typically 1
  size_t bufferSize;   // Buffer size for received data
  
  MySerialConfig(uint32_t b = 4800, bool inv = false, uint8_t db = 8, uint8_t p = 0, uint8_t sb = 1, size_t buf = 256)
    : baud(b), inverse(inv), dataBits(db), parity(p), stopBits(sb), bufferSize(buf) {}
};

#endif
