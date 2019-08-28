#include "ESP8266_XYZ.h"
//#define DEBUG 1
#define STD_TO 100
#define MED_TO 200
#define LNG_TO 300
#define PRINT_DELAY 250
#define AP_TO 2000


bool ESP8266_XYZ::hardReset() {
	pinMode(rst, OUTPUT); 
  	if(rst < 0) {
  		return false;
  	}
	digitalWrite(rst, LOW);
	delay(100);                 
	digitalWrite(rst, HIGH);
	return find_serial(STD_TO, "OK");   
}

void ESP8266_XYZ::readSerialContent(int ser_timeout){
	uint32_t t = millis();
	while((millis() - t) < ser_timeout){
		if(stream->available()){
			char tmp = char(stream->read());
			serial_content += tmp;
			#ifdef DEBUG
				Serial.print(tmp);
			#endif
		}
	}
	
}

bool ESP8266_XYZ::find_serial(int ser_timeout, String str) {
	readSerialContent(ser_timeout);
	if (serial_content.indexOf(str) != -1)
	{	
		serial_content = "";
	   	return true; 
	}
	serial_content = "";
	return false;               
}

void ESP8266_XYZ::printCommand(int commandCode)
{
	String msg = "";

	//Delimitadores y comando
	msg.concat(DC1);
	if(commandCode < 100){
		msg.concat(0);
	}
	if(commandCode < 10){
		msg.concat(0);
	}
	msg.concat(commandCode);
	msg.concat(DC2);

	stream->print(msg);
	delay(PRINT_DELAY);
}

void ESP8266_XYZ::printCommand(int commandCode, String args)
{
	//Delimitadores y comando
	printCommand(commandCode);
	//Argumentos
	stream->println(args);
	jsonClear(&configJson);
	delay(PRINT_DELAY);
}

bool ESP8266_XYZ::espTest()
{
	//Comando de prueba
	printCommand(CM_TEST);
	
	return find_serial(STD_TO, OK_MSG);
}

bool ESP8266_XYZ::softReset()
{
	//Comando para reiniciar el sistema
	printCommand(CM_SOFT_RESET);

	return find_serial(LNG_TO, "OK");
}

bool ESP8266_XYZ::setEspSerialTimeout(int espSerTimeout)
{
	
	jsonInit(&configJson);
	addToJson(&configJson, SER_TIMEOUT, espSerTimeout);
	jsonClose(&configJson);

	//Comando para reiniciar el sistema
	printCommand(CM_SER_TO, configJson);

	return find_serial(STD_TO, "OK");
}

bool ESP8266_XYZ::setEspNetTimeout(int espNetTimeout)
{
	jsonInit(&configJson);
	addToJson(&configJson, ESP_TIMEOUT, espNetTimeout);
	jsonClose(&configJson);

	//Comando para reiniciar el sistema
	printCommand(CM_ESP_TO, configJson);

	return find_serial(STD_TO, "OK");
}

bool ESP8266_XYZ::connectAP(String ssid, String pass){

	jsonInit(&configJson);
	addToJson(&configJson, ARG_SSID, ssid);
	addToJson(&configJson, ARG_PASS, pass);
	jsonClose(&configJson);

	//Comando para conectar a red WiFi
	printCommand(CM_CONNECT_AP, configJson);

	return find_serial(AP_TO, OK_MSG);
}


int ESP8266_XYZ::httpGet(String server, String path, int port, String *response){

	jsonInit(&configJson);
	addToJson(&configJson, ARG_HTTP_SRV, server);
	addToJson(&configJson, ARG_HTTP_PATH, path);
	addToJson(&configJson, ARG_HTTP_PORT, port);
	jsonClose(&configJson);

	printCommand(CM_HTTP_GET, configJson);

	//delay(150); //Parece no ser necesario

	int response_code = stream->readStringUntil('\n').toInt();
	readSerialContent(STD_TO);
	response->concat(serial_content);
	serial_content = "";

	return response_code;
}

int ESP8266_XYZ::httpPost(String server, String path, int port, String jsonMsg, String *response){

	jsonInit(&configJson);
	addToJson(&configJson, ARG_HTTP_SRV, server);
	addToJson(&configJson, ARG_HTTP_PATH, path);
	addToJson(&configJson, ARG_HTTP_PORT, port);
	jsonClose(&configJson);

	printCommand(CM_HTTP_POST_1, configJson);

	//delay(1000); //Debe ser LARGO

	printCommand(CM_HTTP_POST_2, jsonMsg);

	//delay(50); //Parece no ser necesario

	int response_code = stream->readStringUntil('\n').toInt();
	readSerialContent(STD_TO);
	response->concat(serial_content);
	serial_content = "";

	return response_code;
}


ESP8266_XYZ::ESP8266_XYZ(Stream *s, int rst_pin) 
{
	//Asigna el objeto Stream y el pin de reset del ESP8266
	stream = s;
	rst = rst_pin;
	//hardReset();
}
