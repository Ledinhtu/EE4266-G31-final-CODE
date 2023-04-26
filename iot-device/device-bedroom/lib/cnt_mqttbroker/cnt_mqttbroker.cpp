#include "cnt_mqttbroker.h"

// const char* mqtt_server = "192.168.1.132";
extern char* mqtt_server;
extern int mqtt_port ;
extern char* mqtt_id ;
extern char* mqttsub_topic ;
extern char* user ;
extern char* pass ;

extern WiFiClient espClient;
extern PubSubClient client;

extern long lastMsg;
extern char msg[50];
extern int value;

// extern int ledPin;

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(mqtt_id, user, pass)) {
      Serial.println("connected");
      // Subscribe
      client.subscribe(mqttsub_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == mqttsub_topic) {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(ledPin, HIGH);
      client.publish("state/light/device-2", "on");
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(ledPin, LOW);
      client.publish("state/light/device-2", "off");
    }
  }
}