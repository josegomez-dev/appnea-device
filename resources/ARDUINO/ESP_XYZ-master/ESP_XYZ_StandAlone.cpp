#include "ESP_XYZ_StandAlone.h"
#define DEBUG

ESP_XYZ::ESP_XYZ(void){
	clientESP=WiFiClient();
	clientMQTT=PubSubClient(clientESP);
}

bool ESP_XYZ::connectAP(const char* ssid, const char* pass){
	uint32_t t = millis();
	//if(WiFi.status() == WL_CONNECTED){
		//return true;
	//}
	//WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, pass);
  	while (WiFi.status() != WL_CONNECTED && (millis() - t) < global_timeout) {
    	delay(100);//10 -> 100
  	}
	#ifdef DEBUG
	  	Serial.println(WiFi.localIP());
	  	Serial.println(WiFi.status());
	  	Serial.println(WiFi.SSID());
	  	Serial.println(WiFi.gatewayIP());
	#endif
  	return (WiFi.status() == WL_CONNECTED); 
}

int ESP_XYZ::getRSSI(){//Agregada 
	return WiFi.RSSI();
}

void ESP_XYZ::softReset(){
	ESP.restart();
}

void ESP_XYZ::MQTTSetServer(String server, int port){
	this->mqtt_server=server;
	this->mqtt_port=port;
}

void ESP_XYZ::MQTTSetServer(String server, int port, String user, String pass){
	this->mqtt_server=server;
	this->mqtt_port=port;
	this->mqtt_user=user;
	this->mqtt_pass=pass;
}

void ESP_XYZ::MQTTConfig(String id, int retries, int delay_ms){
	this->mqtt_id=id;
	this->mqtt_retries=retries;
	this->mqtt_delay_ms=delay_ms;
}

#if defined(ESP32)
void ESP_XYZ::MQTTSetCallback(MQTT_CALLBACK_SIGNATURE) {
	clientMQTT.setCallback(callback);
}
#else
void ESP_XYZ::MQTTSetCallback(std::function<void(char*, unsigned char*, unsigned int)> callback) {
	clientMQTT.setCallback(callback);
}
#endif

bool ESP_XYZ::MQTTPublish(String topic, String msg){
	if(!MQTTConnected()){
		if (!MQTTReconnect(mqtt_id.c_str(), mqtt_retries, mqtt_delay_ms)){
			return false;
		}
	}
	clientMQTT.publish(topic.c_str(), msg.c_str());
	return true;
}

bool ESP_XYZ::MQTTPublish(String topic, String msg, boolean retained){
	if(!MQTTConnected()){
		if (!MQTTReconnect(mqtt_id.c_str(), mqtt_retries, mqtt_delay_ms)){
			return false;
		}
	}

	clientMQTT.publish(topic.c_str(), msg.c_str(), retained);
	return true;
}

bool ESP_XYZ::MQTTSubscribe(String topic){
	if(!MQTTConnected()){
		if (!MQTTReconnect(mqtt_id.c_str(), mqtt_retries, mqtt_delay_ms)){
			return false;
		}
	}
	return clientMQTT.subscribe(topic.c_str());
}

void ESP_XYZ::MQTTLoop(){
	clientMQTT.loop();
}

bool ESP_XYZ::MQTTConnected(){
	return clientMQTT.connected();
}

bool ESP_XYZ::MQTTReconnect(String id, int retries, int delay_ms){
	int i=0;
	clientMQTT.setServer(mqtt_server.c_str(), mqtt_port);
	while (!clientMQTT.connected()) {
		#ifdef DEBUG
				Serial.print("Attempting MQTT connection...");
		#endif
		if (clientMQTT.connect(id.c_str(),mqtt_user.c_str(),mqtt_pass.c_str())) {
			#ifdef DEBUG
					Serial.println("connected");
			#endif
		} else {
			#ifdef DEBUG
				Serial.print("failed, rc=");
				Serial.print(clientMQTT.state());
				Serial.println(" try again in 5 seconds");
			#endif
			delay(delay_ms);
		}
		if(i<retries){
			i++;
		}else{
			return false;
		}
	}
	return true;
}



////////////////////Fuera de mantenimiento, retomar para solicitudes HTTP


int ESP_XYZ::readResponse(String* response) {

	//Banderas de control del parseo
	bool line_blank = true;
	bool http_body = false;
	bool in_status = false;

	//Variables de soporte
	char status_code[4];
	int i = 0;
	int code = 0;
	uint32_t t = millis();

	//Se lee caracter por caracter de acuerdo con las distintas partes
	//de un response HTTP
	while ((millis() - t) < global_timeout) {
	    if (clientESP.available()) {

	    	char c = clientESP.read();

		    //Luego del primer espacio se encuentra el cÃ³digo de estado
		    if(c == ' ' && !in_status){
		        in_status = true;
		    }

		    //Se lee el código de estado de 3 dígitos
		    if(in_status && i < 3 && c != ' '){////Qué pasa si el código es de 4 digitos???
		        status_code[i] = c;
		        i++;
		    }

		    //Se parsea el código de char* a int
		    if(i == 3){
		        status_code[i] = '\0';
		        code = atoi(status_code);
		    }

		    if(http_body){
		    	//Si se detecta el cuerpo de la respuesta
		    	//se escribe en response (si existe)
		   		if(response != NULL){
		   			response->concat(c);
		   			if(c == '}'){
		   				break;
		   			}
		   		} else {
		   			break;
		   		}

		    } else {	
		    	//Condiciones para detectar el cuerpo de la respuesta
		        if (c == '\n' && line_blank) {
		            http_body = true;
		        }
		        if (c == '\n') {
		            line_blank = true;
		        } else if (c != '\r') {
		            line_blank = false;
		        }
		    }
	    }
	    yield();
	}

	clientESP.stop();
	response->remove(0,response->indexOf('{'));
	response->remove(response->indexOf('}')+1);

	#ifdef DEBUG 
	    	//Serial.println(*response);
	#endif
  	return code;
}


bool ESP_XYZ::connectServer(const char* server, int port){
	uint32_t t = millis();
	bool connected = false;
	#ifdef DEBUG
		Serial.println(server);
		Serial.println(port);
	#endif
	do {
    	connected = clientESP.connect(server, port);
    	delay(100);
  	} while (!connected && (millis() - t) < global_timeout);
  	return connected;
}

int ESP_XYZ::httpPost(const char* server, const char* path, int port, String body, String *response){
	if(connectServer(server, port)){
		#ifdef DEBUG 
			Serial.println("Connected to server");
		#endif

	} else {
		#ifdef DEBUG 
			Serial.println("Connection Failure");
		#endif
		clientESP.stop();
		return -2;
	}

	//POST  HTTP/1.1\r\nHost: \r\nConnection: close\r\nAccept: application/json\r\nContent-Type: application/json\r\nContent-Length:\r\n\r\n

	//Solicitud HTTP al servidor
	//Header
	clientESP.print(F("POST "));
	clientESP.print(path);
	clientESP.print(F(" HTTP/1.1\r\nHost: "));
	clientESP.print(server);
	clientESP.print(F(":"));
	clientESP.print(port);
	clientESP.print(F("\r\nConnection: close\r\nAccept: application/json\r\nContent-Type: application/json\r\nContent-Length: "));
	clientESP.print(body.length());
	clientESP.print(F("\r\n\r\n"));
	clientESP.print(body);

	#ifdef DEBUG
		Serial.print(F("POST "));
		Serial.print(path);
		Serial.print(F(" HTTP/1.1\r\nHost: "));
		Serial.print(server);
		Serial.print(F(":"));
		Serial.print(port);
		Serial.print(F("\r\nConnection: close\r\nAccept: application/json\r\nContent-Type: application/json\r\nContent-Length: "));
		Serial.print(body.length());
		Serial.print(F("\r\n\r\n"));
		Serial.print(body);
	#endif

	return readResponse(response);
	
}

int ESP_XYZ::httpGet(const char* server, const char* path, int port, String *response){
	if(connectServer(server, port)){
		#ifdef DEBUG 
			Serial.println("Connected to server");
		#endif

	} else {
		#ifdef DEBUG
			Serial.println("Connection Failure");
		#endif
		clientESP.stop();
		return -2;
	}
	//GET  HTTP/1.1\r\nHost: \r\n\r\n
	//Solicitud HTTP al servidor
	//Header
    clientESP.print(F("GET "));
    clientESP.print(path);
    clientESP.print(F(" HTTP/1.1\r\nHost: "));
	clientESP.print(server);
	clientESP.print(F(":"));
	clientESP.print(port);
	clientESP.print(F("\r\n\r\n"));

	#ifdef DEBUG
		Serial.print(F("GET "));
	    Serial.print(path);
	    Serial.print(F(" HTTP/1.1\r\nHost: "));
		Serial.print(server);
		Serial.print(F(":"));
		Serial.print(port);
		Serial.print(F("\r\n\r\n"));
	#endif

	//Se obtiene el código de estado de la solicitud
	return readResponse(response);
}

void ESP_XYZ::setTimeout(uint32_t timeout){
	global_timeout = timeout;
}
