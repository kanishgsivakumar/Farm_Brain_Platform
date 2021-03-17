#include <Arduino.h>
#include <FBesp32_platform.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <stdlib.h>
#include <cstdlib>




AsyncWebServer otaServer(3223);

const char* mqtt_server = "test.mosquitto.org";
const uint16_t mqtt_port = 1883;
WiFiClient espClient;
PubSubClient client(espClient);

StaticJsonDocument<128> packet;
char data[128];

uint32_t chipId = getUniqueID();
char chipId_s[20] ;


void setup() {
	Serial.begin(9600);
  while (WiFi.status() != WL_CONNECTED)
  {
    Wificonnect();
    delay(1000);
  }
  delay(2500);
  MQTTconnect(mqtt_server,mqtt_port,&client,itoa(chipId,chipId_s,10));
  Otastart(&otaServer,itoa(chipId,chipId_s,10));
}

void loop() {
  client.loop();
  while (WiFi.status() != WL_CONNECTED)
  {
    Wificonnect();
    delay(1000);
  }

  if (!client.connected()) {
    MQTTreconnect(&client,itoa(chipId,chipId_s,10));
    delay(1000);
  }

  packet["IP"] =  WiFi.localIP().toString();
  packet["UID"] = chipId;
  packet["Device"] =  ESP.getChipModel();
  serializeJson( packet,  &data,  100);
  if (client.publish("outtopic",data))
  {
    Serial.println("Published");
  }
  else
  {
    Serial.println("Error");
  }
  delay(1000);
  Serial.println(data);

}
