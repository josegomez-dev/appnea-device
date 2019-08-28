#include "ESP8266_XYZ_StandAlone.h"

ESP8266_XYZ esp;

uint32_t serial_timeout = 500;
String msg = "";

String post_srv = "";
String post_path  = "";
int post_port = 80;

#define OK_MSG "OK"
#define ERROR_MSG "ERROR"

#define ESP_TIMEOUT "ETO"
#define SER_TIMEOUT "STO"
#define AP "AP"
#define PASS "PASS"

#define HTTP_SRV "HSRV"
#define HTTP_PATH "HPATH"
#define HTTP_PORT "HPORT"

#define DC1 '+'//0x11
#define DC2 '-'//0x12

#define CM_TEST 0
#define CM_SOFT_RESET 1
#define CM_SER_TO 2
#define CM_ESP_TO 3
#define CM_CONNECT_AP 4

#define CM_HTTP_GET 20
#define CM_HTTP_POST_1 21
#define CM_HTTP_POST_2 22

void setup() {
  Serial.begin(19200);
  response_ok();
}

void loop() {
  if(Serial.available()){
    int command_code = at_validator(&msg);
    if(command_code == -1){
      //response_error();
    }
    command_mgr(command_code);
  }
  
  yield();
  
}

int at_validator(String* msg){

  bool command = false;
  bool msg_flag = false;
  char command_code[4];
  int command_type = -1;
  uint32_t t = millis();
  int i = 0;
  
  while ((millis() - t) < serial_timeout) {
    if(Serial.available()){
      char c = Serial.read();
      //Se lee el código de estado de 3 dígitos
      if(command && i < 3 && c != DC2){  //caracter siguiente debe ser DC2 (ver tabla ASCII)
        command_code[i] = c;
        i++;
      }

      if(c == DC1 && !command){      //caracter debe ser DC1 (ver tabla ASCII)
        command = true;
      }

      if(i == 3){
        command_code[i] = '\0';
        command_type = atoi(command_code);
        i++;
      }

      if(msg_flag) {
        msg->concat(c);
      } else if(c == DC2){
          msg_flag = true;
      }
      if(c == '\n'){
          break;
      }
    }
    yield();
  }
  return command_type;
}

void command_mgr(int command){
  if(command < 20){
    //Llamar comandos de configuración
    config_commands(command);
  } else if(command < 40){
    //Llamar comandos HTTP
    http_commands(command);
  } else if(command < 60){
    //Llamar comandos MQTT
  }
}

bool response_ok(){
  Serial.println(OK_MSG);
  msg = "";
  return true;
}

bool response_error(){
  Serial.println(ERROR_MSG);
  msg = "";
  return false;
}

void config_commands(int code){
  switch (code){
    case CM_TEST:
      //Serial.println("TEST");
      response_ok();
      break;
    case CM_SOFT_RESET:
      //Serial.println("SOFT RESET");
      esp.softReset();
      break;
    case CM_SER_TO:
      //Serial.println("SERIAL TIMEOUT");
      ser_timeout();
      break;
    case CM_ESP_TO:
      //Serial.println("NET TIMEOUT");
      esp_timeout();
      break;
    case CM_CONNECT_AP:
      //Serial.println("CONNECT AP");
      connect_ap();
      break;
  }
}

bool connect_ap (){
  bool connection_status = false;
  String ap = getJsonStr(msg, AP);
  String pass = getJsonStr(msg, PASS);
  //Serial.println(ap);
  //Serial.println(pass);
   connection_status = esp.connectAP(ap.c_str(), pass.c_str());
  if(connection_status){
    return response_ok();
  } else {
    return response_error();
  }
}

bool ser_timeout(){
  int timeout = getJsonInt(msg, SER_TIMEOUT);
  if(timeout <= 0){
    return response_error();
  } else {
    serial_timeout = timeout;
    return response_ok();
  }
}

bool esp_timeout(){
  int timeout = getJsonInt(msg, ESP_TIMEOUT);
  //Serial.println(timeout);
  if(timeout <= 0){
    return response_error();
  } else {
    esp.setTimeout(timeout);
    return response_ok();
  }
}


void http_commands(int code){
  switch (code){
    case CM_HTTP_GET:
      //Serial.println("HTTP GET");
      http_get();
      break;
    case CM_HTTP_POST_1:
      //Serial.println("HTTP POST CONFIG");
      http_post_config();
      break;
    case CM_HTTP_POST_2:
      //Serial.println("HTTP POST");
      http_post();
      break;
  }
}

bool http_get(){
  
  String http_server = getJsonStr(msg, HTTP_SRV);
  String http_path = getJsonStr(msg, HTTP_PATH);
  int http_port = getJsonInt(msg, HTTP_PORT);
  
  String http_response = "";
  int http_resp_code = 0;
  
  http_resp_code = esp.httpGet(http_server.c_str(), http_path.c_str(), http_port, &http_response);
  Serial.println(http_resp_code);
  Serial.println(http_response);

  msg = "";
}

void http_post_config(){

  post_srv = getJsonStr(msg, HTTP_SRV);
  post_path = getJsonStr(msg, HTTP_PATH);
  post_port = getJsonInt(msg, HTTP_PORT);
  
  msg = "";
  //response_ok();
}

void http_post(){
  String http_response = "";
  int http_resp_code = 0;
  
  http_resp_code = esp.httpPost(post_srv.c_str(), post_path.c_str(), post_port, msg, &http_response);
  Serial.println(http_resp_code);
  Serial.println(http_response);

  String post_srv = "";
  String post_path = "";
  int post_port = 80;
  msg = "";
}




