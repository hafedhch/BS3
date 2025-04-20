#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <Arduino.h>
#include <EEPROM.h>
#include "MySerialConfig.h"

#define EEPROM_SIZE 512   // Define the total size for EEPROM storage


class ConfigManager {
public:
  MySerialConfig rs232Config;
  MySerialConfig rs422Config;
  
  ConfigManager();
  void load(); 
  void save(); 
};

#endif
