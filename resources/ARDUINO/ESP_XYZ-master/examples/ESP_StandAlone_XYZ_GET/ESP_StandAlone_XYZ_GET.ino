//Se incluye biblioteca para el uso de ESP8266 de manera independiente
#include "ESP_XYZ_StandAlone.h"

//Creación del objeto esp para controlar funciones de red
ESP_XYZ esp;

//Almacenamiento de los datos de la red inalámbrica
char* ssid = "NombreRed";
char* pass = "contrasena123";

//Almacenamiento de los datos del servidor al que se le hacen solicitudes
char* server = "hwserver.herokuapp.com";
char* path = "/post";
int port = 80;

void setup() {
  //Se inicializa el puerto Serial en 19200 baudios para comunicación con la computadora
  Serial.begin(19200);

  //Esperar conexión con la computadora
  while(!Serial);

  //Si no hay conexión al punto de acceso, termina ejecución
  while(!esp.connectAP(ssid, pass));

  //Se imprime un mensaje verificando el correcto funcioonamiento del dispositivo
  Serial.println("Configuracion exitosa");
}

void loop() {
  //Se crea un String para almacenar el cuerpo de la respuesta de la solicitud
  String response_body = "";

  //Se ejecuta una solicitud HTTP GET y se almacena el código de respuesta
  int response_code = esp.httpGet(server, path, port, &response_body);

  //Se imprime el código y cuerpo de la respuesta
  Serial.println(response_code);
  Serial.println(response_body);
  
  //Pausa de un segundo en la ejecución del programa
  delay(1000);
}
