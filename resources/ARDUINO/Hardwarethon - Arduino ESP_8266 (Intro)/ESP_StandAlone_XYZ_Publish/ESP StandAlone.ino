//Se incluye biblioteca para el uso de ESP8266 independiente
#include "ESP_XYZ_StandAlone.h"

//Creación del objeto esp que controla las funciones de red
ESP_XYZ esp;

//Almacenamiento de los datos de la red inalámbrica
char* ssid = "RED";
char* pass = "PASS";

//Almacenamiento de los datos del servidor MQTT
String server = "test.cloudmqtt.com";
String user = "t3sT";
String srv_pass = "t3sT_p@sS";
int port = 2420;

//Almacenamiento del ID del dispositivo
String device_id = "Dispositivo1";

//Almacenamiento de topic MQTT
String topic = "topic/something";

String topicSub = "topicSub/something";

const int buttonPin1 = 13;
const int buttonPin2 = 14;

void setup() {
  //Se inicializa el puerto Serial en 19200 baudios para comunicación con la computadora
  Serial.begin(19200);

  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
   
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

  esp.MQTTSubscribe(topicSub);
  
  esp.MQTTSetCallback(mqtt_callback);
}

void loop() {
  int buttonState1 = digitalRead(buttonPin1);
  int buttonState2 = digitalRead(buttonPin2);
  
  //Se crea un String para construir el mensaje JSON
  String json_msg = "";

  //Se agregan las variables necesarias al JSON
  jsonInit(&json_msg);
  //Argumentos posibles solo pueden ser String, float o int
  addToJson(&json_msg, "millis", int(millis())); 

  if (buttonState1 == HIGH) {
    addToJson(&json_msg, "direction", "1");
  } else {
    if (buttonState2 == HIGH) {
      addToJson(&json_msg, "direction", "2");
    }
  }
  
  jsonClose(&json_msg);

  if ((buttonState1 == HIGH) || (buttonState2 == HIGH)) {
    //Se ejecuta una solicitud HTTP POST y se almacena el código de respuesta
    bool published = esp.MQTTPublish(topic, json_msg);
    
    if (published) {
       Serial.println("Bazinga!");
    } else {
      Serial.println("Fuuck!");
    }
  }

  while((buttonState1 == HIGH) || (buttonState2 == HIGH)) {
    buttonState1 = digitalRead(buttonPin1);
    buttonState2 = digitalRead(buttonPin2);

    if ((buttonState1 == LOW) && (buttonState2 == LOW)) {
      Serial.println("Button Released!");
    }
  }  
  
  //Se libera la memoria asociada al mensaje JSON
  jsonClear(&json_msg);

  //Se imprime el código y cuerpo de la respuesta
  // Serial.println(published);
  
  //Pausa de un segundo en la ejecución del programa
  delay(100);

  esp.MQTTLoop();
}

void mqtt_callback(char* topic, byte* payload, unsigned int len) {
  //Notifica en puerto UART la recepción de un mensaje
  Serial.print("Mensaje recibido [");
  Serial.print(topic);
  Serial.print("] ");

  //Se imprime el mensaje caracter por caracter
  for (int i = 0; i < len; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

