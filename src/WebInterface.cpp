#include "WebInterface.h"

WebInterface::WebInterface(ConfigManager &configManager)
  : server(80), cfgManager(configManager) {
}

void WebInterface::begin() {
  // Serve configuration page at root
  server.on("/", HTTP_GET, [this]() {
    handleRoot();
  });
  
  // Handle configuration changes via POST
  server.on("/config", HTTP_POST, [this]() {
    handleConfigPost();
  });
  
  server.begin();
  Serial.println("Web server started.");
}

void WebInterface::handleClient() {
  server.handleClient();
}

void WebInterface::handleRoot() {
  String html = "<!DOCTYPE html><html><head><meta charset='utf-8'><title>NMEA Converter Config</title>";
  html += "<style>";
  html += "body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; background-color: #f4f6f9; margin:0; padding: 0; }";
  html += "header { background-color: #007BFF; color: #fff; padding: 20px; text-align: center; }";
  html += "form { background: #fff; max-width: 600px; margin: 30px auto; padding: 20px; border-radius: 10px; box-shadow: 0 4px 6px rgba(0,0,0,0.1); }";
  html += "h2 { color: #007BFF; margin-bottom: 20px; }";
  html += "label { display: block; margin-bottom: 5px; font-weight: bold; }";
  html += "input[type='number'], select { width: 100%; padding: 7px; margin-left : -10px; margin-bottom: 10px; border: 1px solid #ccc; border-radius: 5px; }";
  html += "input[type='checkbox'] { margin-right: 10px; }";
  html += "button { background-color: #007BFF; color: #fff; border: none; padding: 10px 20px; border-radius: 5px; cursor: pointer; font-size: 16px; }";
  html += "button:hover { background-color: #0056b3; }";
  html += "</style></head><body>";
  html += "<header><h1> NMEA Converter Configuration</h1></header>";
  
  html += "<form method='POST' action='/config'>";
  
  // RS232 settings
  html += "<h2>RS232 Configuration</h2>";
  html += "<label for='rs232_baud'>Baud Rate</label>";
  html += "<input type='number' id='rs232_baud' name='rs232_baud' value='" + String(cfgManager.rs232Config.baud) + "' required>";
  html += "<label for='rs232_inverse'><i class='fa-solid fa-toggle-on'></i> Inverse</label>";
  html += "<input type='checkbox' id='rs232_inverse' name='rs232_inverse' " + String(cfgManager.rs232Config.inverse ? "checked" : "") + ">";
  html += "<label for='rs232_dataBits'>Data Bits</label>";
  html += "<input type='number' id='rs232_dataBits' name='rs232_dataBits' value='" + String(cfgManager.rs232Config.dataBits) + "' required>";
  html += "<label for='rs232_parity'>Parity (0=None, 1=Odd, 2=Even)</label>";
  html += "<input type='number' id='rs232_parity' name='rs232_parity' value='" + String(cfgManager.rs232Config.parity) + "' required>";
  html += "<label for='rs232_stopBits'>Stop Bits</label>";
  html += "<input type='number' id='rs232_stopBits' name='rs232_stopBits' value='" + String(cfgManager.rs232Config.stopBits) + "' required>";
  html += "<label for='rs232_bufferSize'>Buffer Size</label>";
  html += "<input type='number' id='rs232_bufferSize' name='rs232_bufferSize' value='" + String(cfgManager.rs232Config.bufferSize) + "' required>";
  
  // RS422 settings
  html += "<h2>RS422 Configuration</h2>";
  html += "<label for='rs422_baud'>Baud Rate</label>";
  html += "<input type='number' id='rs422_baud' name='rs422_baud' value='" + String(cfgManager.rs422Config.baud) + "' required>";
  html += "<label for='rs422_inverse'><i class='fa-solid fa-toggle-on'></i> Inverse</label>";
  html += "<input type='checkbox' id='rs422_inverse' name='rs422_inverse' " + String(cfgManager.rs422Config.inverse ? "checked" : "") + ">";
  html += "<label for='rs422_dataBits'>Data Bits</label>";
  html += "<input type='number' id='rs422_dataBits' name='rs422_dataBits' value='" + String(cfgManager.rs422Config.dataBits) + "' required>";
  html += "<label for='rs422_parity'>Parity (0=None, 1=Odd, 2=Even)</label>";
  html += "<input type='number' id='rs422_parity' name='rs422_parity' value='" + String(cfgManager.rs422Config.parity) + "' required>";
  html += "<label for='rs422_stopBits'>Stop Bits</label>";
  html += "<input type='number' id='rs422_stopBits' name='rs422_stopBits' value='" + String(cfgManager.rs422Config.stopBits) + "' required>";
  html += "<label for='rs422_bufferSize'>Buffer Size</label>";
  html += "<input type='number' id='rs422_bufferSize' name='rs422_bufferSize' value='" + String(cfgManager.rs422Config.bufferSize) + "' required>";
  
  html += "<button type='submit'><i class='fa-solid fa-save'></i> Save Configuration</button>";
  html += "</form>";
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

void WebInterface::handleConfigPost() {
  // Check for all required fields in both RS232 and RS422 sections
  if (server.hasArg("rs232_baud") && server.hasArg("rs232_dataBits") &&
      server.hasArg("rs232_parity") && server.hasArg("rs232_stopBits") &&
      server.hasArg("rs232_bufferSize") &&
      server.hasArg("rs422_baud") && server.hasArg("rs422_dataBits") &&
      server.hasArg("rs422_parity") && server.hasArg("rs422_stopBits") &&
      server.hasArg("rs422_bufferSize")) {

    // Parse RS232 configuration
    uint32_t baud232 = server.arg("rs232_baud").toInt();
    uint8_t dataBits232 = server.arg("rs232_dataBits").toInt();
    uint8_t parity232 = server.arg("rs232_parity").toInt();
    uint8_t stopBits232 = server.arg("rs232_stopBits").toInt();
    size_t buf232 = server.arg("rs232_bufferSize").toInt();
    bool inv232 = (server.arg("rs232_inverse") == "on");

    // Parse RS422 configuration
    uint32_t baud422 = server.arg("rs422_baud").toInt();
    uint8_t dataBits422 = server.arg("rs422_dataBits").toInt();
    uint8_t parity422 = server.arg("rs422_parity").toInt();
    uint8_t stopBits422 = server.arg("rs422_stopBits").toInt();
    size_t buf422 = server.arg("rs422_bufferSize").toInt();
    bool inv422 = (server.arg("rs422_inverse") == "on");

    // Update RS232 config
    cfgManager.rs232Config.baud = baud232;
    cfgManager.rs232Config.dataBits = dataBits232;
    cfgManager.rs232Config.parity = parity232;
    cfgManager.rs232Config.stopBits = stopBits232;
    cfgManager.rs232Config.bufferSize = buf232;
    cfgManager.rs232Config.inverse = inv232;

    // Update RS422 config
    cfgManager.rs422Config.baud = baud422;
    cfgManager.rs422Config.dataBits = dataBits422;
    cfgManager.rs422Config.parity = parity422;
    cfgManager.rs422Config.stopBits = stopBits422;
    cfgManager.rs422Config.bufferSize = buf422;
    cfgManager.rs422Config.inverse = inv422;
    
    // Save configurations persistently
    cfgManager.save();
    
    server.send(200, "application/json", "{\"status\":\"ok\"}");
  } else {
    server.send(400, "application/json", "{\"error\":\"Missing parameters\"}");
  }
}
