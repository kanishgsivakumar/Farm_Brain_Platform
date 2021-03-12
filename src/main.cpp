#include <Arduino.h>
#include <FBesp32_platform.h>
#include <ESPAsync_WiFiManager.h>              //https://github.com/khoih-prog/ESPAsync_WiFiManager
AsyncWebServer webServer(80);
DNSServer dnsServer;

uint32_t chipId = getUniqueID();
uint8_t led_server = 33;
uint8_t led_wifi = 25;

void setup() {
	Serial.begin(9600);
  pinMode(led_wifi,OUTPUT);
  Serial.print("\nStarting Async_AutoConnect_ESP32_minimal on " + String(ARDUINO_BOARD)); Serial.println(ESP_ASYNC_WIFIMANAGER_VERSION);
  char APname[20] ="" ;
  ESPAsync_WiFiManager ESPAsync_wifiManager(&webServer, &dnsServer,"ENV_Node" );
  //ESPAsync_wifiManager.resetSettings();   //reset saved settings
  ESPAsync_wifiManager.setAPStaticIPConfig(IPAddress(192,168,132,1), IPAddress(192,168,132,1), IPAddress(255,255,255,0));
  ESPAsync_wifiManager.autoConnect("ENV_Node");
  if (WiFi.status() == WL_CONNECTED) 
  {
    Serial.print(F("Connected. Local IP: ")); Serial.println(WiFi.localIP());
    digitalWrite(led_wifi,HIGH);
  }
  else 
  {
    Serial.println(ESPAsync_wifiManager.getStatus(WiFi.status()));
  }
}

void loop() {
	Serial.printf("ESP32 Chip model = %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
	Serial.printf("This chip has %d cores\n", ESP.getChipCores());
  Serial.print("Chip ID: "); Serial.println(chipId);
  Serial.print(F("Connected. Local IP: ")); Serial.println(WiFi.localIP());
  
	delay(3000);


}

