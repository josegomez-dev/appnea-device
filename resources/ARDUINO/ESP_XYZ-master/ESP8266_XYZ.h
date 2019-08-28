#ifndef ESP8266_XYZ_H
#define ESP8266_XYZ_H

#include "JsonXYZ.h"
#include <Arduino.h>


#define OK_MSG "OK"
#define ERROR_MSG "ERROR"
#define DC1 "+"//0x11
#define DC2 "-"//0x12

#define ESP_TIMEOUT "ETO"
#define SER_TIMEOUT "STO"
#define ARG_SSID "AP"
#define ARG_PASS "PASS"

#define ARG_HTTP_SRV "HSRV"
#define ARG_HTTP_PATH "HPATH"
#define ARG_HTTP_PORT "HPORT"

#define CM_TEST 0
#define CM_SOFT_RESET 1
#define CM_SER_TO 2
#define CM_ESP_TO 3
#define CM_CONNECT_AP 4

#define CM_HTTP_GET 20
#define CM_HTTP_POST_1 21
#define CM_HTTP_POST_2 22

class ESP8266_XYZ 
{
	public:
		ESP8266_XYZ(Stream *s = &Serial, int rst = -1);
		bool hardReset();

		bool espTest();
		bool softReset();
		bool setEspSerialTimeout(int espSerTimeout);
		bool setEspNetTimeout(int espNetTimeout);
		bool connectAP(String ssid, String pass);
		
		void printCommand(int commandCode);
		void printCommand(int commandCode, String args);

		int readResponse(String* response);

		int httpPost(String server, String path, int port, String jsonMsg, String *response);
		int httpGet(String server, String path, int port, String *response);
		
	private:
		bool find_serial(int ser_timeout, String str);
		void readSerialContent(int ser_timeout);
		bool connectServer(String server, int port);
		String configJson = "";
		int rst;
		String serial_content = "";
		Stream *stream;
};

#endif
