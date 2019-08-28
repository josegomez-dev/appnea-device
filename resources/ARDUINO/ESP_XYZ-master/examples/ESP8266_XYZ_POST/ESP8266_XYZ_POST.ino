//Se incluye biblioteca para el uso de ESP8266 + Arduino
#include <ESP8266_XYZ.h>

//Se incluye SoftwareSerial para comuniación en serie con ESP8266
#include <SoftwareSerial.h>

//Creación del objeto SoftwareSerial, con pin 2 como RX y pin 3 como TX  
SoftwareSerial espSerial(2,3);

//Creación del objeto esp que maneja los comandos para ESP8266, con pin 4 como RST
ESP8266_XYZ esp(&espSerial, 4);

//Almacenamiento de los datos de la red inalámbrica
String ssid = "NombreRed";
String pass = "contrasena123";

//Almacenamiento de los datos del servidor al que se le hacen solicitudes
String server = "hwserver.herokuapp.com";
String path = "/post";
int port = 80;

void setup() {
  //Se inicializa el puerto SoftwareSerial en 19200 baudios para el ESP8266
  espSerial.begin(19200);

  //Se inicializa el puerto Serial en 19200 baudios para comunicación con la computadora
  espSerial.begin(19200);

  //Esperar conexión con la computadora
  while(!Serial);

  //Si el ESP8266 no responde, termina ejecución
  while(!esp.espTest());

  //Si no hay conexión al punto de acceso, termina ejecución
  while(!esp.connectAP(ssid, pass));

  //Se imprime un mensaje verificando el correcto funcioonamiento del dispositivo
  Serial.println("Configuracion exitosa");
}

void loop() {
  //Se crea un String para almacenar el cuerpo de la respuesta de la solicitud
  String response_body = "";

  //Se crea un String para construir el mensaje JSON
  String json_msg = "";

  //Se agregan las variables necesarias al JSON
  jsonInit(&json_msg);
  //Argumentos posibles solo pueden ser String, float o int
  addToJson(&json_msg, "adc", analogRead(A0));
  addToJson(&json_msg, "millis", int(millis())); 
  jsonClose(&json_msg);

  //Se ejecuta una solicitud HTTP POST y se almacena el código de respuesta
  int response_code = esp.httpPost(server, path, port, json_msg, &response_body);

  //Se libera la memoria asociada al mensaje JSON
  jsonClear(&json_msg);

  //Se imprime el código y cuerpo de la respuesta
  Serial.println(response_code);
  Serial.println(response_body);
  
  //Pausa de un segundo en la ejecución del programa
  delay(1000);
}
