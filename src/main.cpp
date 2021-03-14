#include <Arduino.h>
#include <FBesp32_platform.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>



uint32_t chipId = getUniqueID();

AsyncWebServer webServer(80);
AsyncWebServer otaServer(3223);
DNSServer dnsServer;

const char* mqtt_server = "test.mosquitto.org";
const uint16_t mqtt_port = 1883;
WiFiClient espClient;
PubSubClient client(espClient);

StaticJsonDocument<128> packet;
char data[128];

void setup() {
	Serial.begin(9600);
  while (WiFi.status() != WL_CONNECTED)
  {
    Wificonnect(webServer,dnsServer);
    delay(1000);
  }
  MQTTconnect(mqtt_server,mqtt_port,&client);
  Otastart(&otaServer);
}

void loop() {
  while (WiFi.status() != WL_CONNECTED)
  {
    Wificonnect(webServer,dnsServer);
    delay(1000);
  }

  if (!client.connected()) {
    MQTTconnect(mqtt_server,mqtt_port,&client);
    delay(100);
  }

  client.loop();

  packet["IP"] =  WiFi.localIP().toString();
  packet["UID"] = chipId;
  packet["Device"] =  ESP.getChipModel();
  serializeJson( packet,  &data,  100);
  client.publish("outtopic",data);
  delay(1000);
  Serial.println(data);

}

