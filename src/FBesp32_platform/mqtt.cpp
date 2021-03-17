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

void MQTTconnect(const char* mqtt_server,const uint16_t mqtt_port,PubSubClient* client,char* chipId_s)
{
    client -> setServer(mqtt_server, mqtt_port);
    client -> setCallback(callback);
    while (!client -> connected()) {
        Serial.println("Connecting to MQTT...");
        if (client -> connect(chipId_s)) {
            Serial.println(client -> state());
                client -> publish("outTopic","hello world");
                delay(100);
            Serial.println(client -> state());
                client -> subscribe("/kanishg");
            Serial.println(client -> state());
                delay(400);
        } else {
            Serial.print("failed with state ");
            Serial.print(client -> state());
            delay(2000);
        }
    }
}



void MQTTreconnect(PubSubClient* client,char* chipId_s)
{
    while (!client -> connected()) {
        Serial.println("Reconnecting to MQTT...");
        if (client -> connect(chipId_s)) {
            Serial.println("reconnected");
                client -> publish("outTopic","hello world");
                delay(100);
                client -> subscribe("/kanishg");
                delay(400);
        } else {
            Serial.print("failed with state ");
            Serial.print(client -> state());
            delay(2000);
        }
    }
}
