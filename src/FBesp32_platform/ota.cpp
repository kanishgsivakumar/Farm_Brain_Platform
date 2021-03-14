#include <Arduino.h>
#include <AsyncElegantOTA.h>
#include <AsyncTCP.h>
#include <FBesp32_platform.h>

void Otastart(AsyncWebServer* otaServer)
{
    otaServer->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "\nFarmBrain\nFarm_Brain_platform\nSustenance Agritech Pvt. Ltd");
  });
  AsyncElegantOTA.begin(otaServer);    // Start ElegantOTA
  otaServer->begin();
  Serial.println("HTTP server started");
}