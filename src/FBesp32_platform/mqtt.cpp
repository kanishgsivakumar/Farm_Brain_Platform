#include <WiFi.h>
#include <PubSubClient.h>

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}  

void MQTTconnect(const char* mqtt_server,const uint16_t mqtt_port,PubSubClient* client)
{
    client -> setServer(mqtt_server, mqtt_port);
    client -> setCallback(callback);
    while (!client -> connected()) {
        Serial.println("Connecting to MQTT...");
        if (client -> connect("arduinoClient")) {
            Serial.println("connected");
                client -> publish("outTopic","hello world");
                client -> subscribe("/kanishg");
                delay(500);
        } else {
            Serial.print("failed with state ");
            Serial.print(client -> state());
            delay(2000);
        }
    }
}


