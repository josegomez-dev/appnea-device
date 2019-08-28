#ifndef ESP_XYZ_H
#define ESP_XYZ_H

#include "JsonXYZ.h"
#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <PubSubClient.h>
#include <functional>

class ESP_XYZ 
{
	public:
		ESP_XYZ();
		bool connectAP(const char* ssid, const char* pass);
		int getRSSI();
		void softReset();
		void setTimeout(uint32_t timeout);
		int readResponse(String* response);

		bool connectServer(const char* server, int port);
		int httpPost(const char* server, const char* path, int port, String body, String *response);
		int httpGet(const char* server, const char* path, int port, String *response);
		void MQTTSetServer(String server, int port);
		void MQTTSetServer(String server, int port, String user, String pass);
		void MQTTConfig(String id, int retries = 1, int delay_ms = 100);
	#if defined(ESP32)
		void MQTTSetCallback(MQTT_CALLBACK_SIGNATURE);
	#else
		void MQTTSetCallback(std::function<void(char*, uint8_t*, unsigned int)> callback);
	#endif
		bool MQTTPublish(String topic, String msg);
		bool MQTTPublish(String topic, String msg, boolean retained);
		bool MQTTSubscribe(String topic);
		void MQTTLoop();
		bool MQTTConnected();
		bool MQTTReconnect(String id, int retries = 1, int delay_ms = 100);
		
	private:
		uint global_timeout = 5000;
		String mqtt_id = "";
		int mqtt_retries = 1, mqtt_delay_ms = 100;
		WiFiClient clientESP;
		PubSubClient clientMQTT;
		String mqtt_server = "";
		String mqtt_user = "";
		String mqtt_pass = "";
		int mqtt_port = 1883;
};

#endif
