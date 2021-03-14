#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <PubSubClient.h>

extern uint32_t getUniqueID();
extern bool Wificonnect(AsyncWebServer webServer, DNSServer dnsServer);
extern void MQTTconnect(const char* mqtt_server,const uint16_t mqtt_port,PubSubClient* client);
extern void Otastart(AsyncWebServer* otaServer);
