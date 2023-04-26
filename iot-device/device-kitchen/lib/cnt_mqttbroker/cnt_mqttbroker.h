#ifndef CNT_MQTTBROKER_H
#define CNT_MQTTBROKER_H
#include <Arduino.h>

// Import required libraries
#include "WiFi.h"
#include <PubSubClient.h>


extern const int ledPin;

void reconnect() ;
void callback(char* topic, byte* message, unsigned int length);

#endif