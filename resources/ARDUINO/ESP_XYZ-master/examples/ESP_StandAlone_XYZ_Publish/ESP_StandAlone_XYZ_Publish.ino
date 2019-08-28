//Se incluye biblioteca para el uso de ESP8266 independiente
#include "ESP_XYZ_StandAlone.h"

//Creación del objeto esp que controla las funciones de red
ESP_XYZ esp;

//Almacenamiento de los datos de la red inalámbrica
char* ssid = "NombreRed";
char* pass = "contrasena123";

//Almacenamiento de los datos del servidor MQTT
String server = "m12.cloudmqtt.com";
String user = "bjakjzet";
String srv_pass = "Ja0pHkgWxr6l";
int port = 17269;

//Almacenamiento del ID del dispositivo
String device_id = "Dispositivo1";

//Almacenamiento de topic MQTT
String topic = "imagine/mi_tema";

void setup() {
  //Se inicializa el puerto Serial en 19200 baudios para comunicación con la computadora
  Serial.begin(19200);

  //Esperar conexión con la computadora
  while(!Serial);

  //Si no hay conexión al punto de acceso, termina ejecución
  while(!esp.connectAP(ssid, pass));

  //Se imprime un mensaje verificando el correcto funcioonamiento del dispositivo
  Serial.println("Configuracion exitosa");

  //Se establece el id del dispositivo
  esp.MQTTConfig(device_id);

  //Se configura el servidor destino
  esp.MQTTSetServer(server, port, user, srv_pass);
}

void loop() {

  //Se crea un String para construir el mensaje JSON
  String json_msg = "";

  //Se agregan las variables necesarias al JSON
  jsonInit(&json_msg);
  //Argumentos posibles solo pueden ser String, float o int
  addToJson(&json_msg, "adc", analogRead(A0));
  addToJson(&json_msg, "millis", int(millis())); 
  jsonClose(&json_msg);

  //Se ejecuta una solicitud HTTP POST y se almacena el código de respuesta
  bool published = esp.MQTTPublish(topic, json_msg);
  
  //Se libera la memoria asociada al mensaje JSON
  jsonClear(&json_msg);

  //Se imprime el código y cuerpo de la respuesta
  Serial.println("Mensaje publicado: ");
  Serial.println(published);
  
  //Pausa de un segundo en la ejecución del programa
  delay(1000);
}
