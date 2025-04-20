#include "ConfigManager.h"

ConfigManager::ConfigManager()
  : rs232Config(4800, false, 8, 0, 1, 256), rs422Config(4800, false, 8, 0, 1, 256) {
  // Default configurations;
}

void ConfigManager::load() {
// Initialize EEPROM with the defined size
  EEPROM.begin(EEPROM_SIZE);

  // Read the RS232 configuration from EEPROM address 0
  EEPROM.get(0, rs232Config);
  
  // Read the RS422 configuration from EEPROM at the next available address.
  EEPROM.get(sizeof(MySerialConfig), rs422Config);
}

void ConfigManager::save() {
  // Initialize EEPROM with the defined size
  EEPROM.begin(EEPROM_SIZE);

  // Write the RS232 configuration to EEPROM at address 0
  EEPROM.put(0, rs232Config);

  // Write the RS422 configuration to EEPROM starting at the next available address
  EEPROM.put(sizeof(MySerialConfig), rs422Config);
  
  // Commit changes to EEPROM (on ESP8266, EEPROM emulation requires this)
  EEPROM.commit();
}
