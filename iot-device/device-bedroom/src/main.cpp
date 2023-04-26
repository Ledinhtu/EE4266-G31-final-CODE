#include <Arduino.h>

#include "cnt_mqttbroker.h"
#include "connect_wifi.h"
#include "read_dht.h"

// Digital pin connected to the DHT sensor
#define DHTPIN 4    
#define DHTTYPE    DHT11     // DHT 11
#define BUTTON 0

 /******************** CONNECT_WIFI_H *****************************/
// const char* ssid = "Quy Hien";
// const char* password = "12345678";
// const char* ssid = "Wifi Free";
// const char* password = "66668888";
const char* ssid = "heeeheee";
const char* password = "heeeheee";
 /******************** CONNECT_WIFI_H *****************************/


 /******************** CNT_MQTTBROKER_H *****************************/
// const char* mqtt_server = "192.168.1.132";
// const char* mqtt_server = "192.168.1.6";
const char* mqtt_server = "192.168.105.100";
const int mqtt_port = 1883;
const char* mqtt_id = "ESP32-bedroom";
const char* mqttsub_topic = "esp32/output2";
const char* user = "light-bedroom";
const char* pass = "matteo";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
bool led_status = false;
const int ledPin = 2;
 /******************** CNT_MQTTBROKER_H *****************************/


DHT dht(DHTPIN, DHTTYPE);

// float temperature = 0;
// float humidity = 0;

bool isPress = false;
void IRAM_ATTR button_isr() {
  isPress = true;
}

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(BUTTON, button_isr, FALLING);


  dht.begin();

  setup_wifi();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (isPress) {
    led_status = !led_status;

    digitalWrite(ledPin, led_status);
    if (led_status) {
      client.publish("state/light/device-2", "on");
    } else {
      client.publish("state/light/device-2", "off");
    }
     
    isPress = false;
  }
}
