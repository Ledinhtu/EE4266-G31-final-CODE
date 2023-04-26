#include "cnt_mqttbroker.h"

extern char* mqtt_server;
extern int mqtt_port ;
extern char* mqtt_id ;
extern char* mqttsub_topic ;
extern char* user ;
extern char* pass ;
extern char* mess ;

extern WiFiClient espClient;
extern PubSubClient client;

extern long lastMsg;
extern char msg[50];
extern int value;

extern bool led_status;

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(mqtt_id, user, pass)) {
      Serial.println("connected");
      // Subscribe
      client.subscribe(mqttsub_topic);//
      client.subscribe("esp/test");
      client.subscribe("esp/test1");
      client.subscribe("esp/test2");
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

  if (String(topic) == mqttsub_topic) {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(ledPin, HIGH);
      led_status = true;
      client.publish("state/light/device-3", "on");
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(ledPin, LOW);
      led_status = false;
      client.publish("state/light/device-3", "off");
    }
  }
  else if (String(topic) == "esp/test") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(4, HIGH);
      client.publish("state/light/test", "on");
    }
    if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(4, LOW);
      client.publish("state/light/test", "off");
    }
  }
  else if (String(topic) == "esp/test1") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(4, HIGH);
      client.publish("state/light/test", "on");
    }
    if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(4, LOW);
      client.publish("state/light/test", "off");
    }
  }
  else if (String(topic) == "esp/test2") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(4, HIGH);
      client.publish("state/light/test", "on");
    }
    if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(4, LOW);
      client.publish("state/light/test", "off");
    }
  }
}