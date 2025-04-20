#ifndef WEB_INTERFACE_H
#define WEB_INTERFACE_H

#include <ESP8266WebServer.h>
#include "ConfigManager.h"

class WebInterface {
public:
  WebInterface(ConfigManager &configManager);
  void begin();
  void handleClient();
  
private:
  ESP8266WebServer server;
  ConfigManager &cfgManager;
  void handleRoot();
  void handleConfigPost();
};

#endif
