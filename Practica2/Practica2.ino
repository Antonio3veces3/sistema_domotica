/*****************************************************************************
*                                                                            *
*      NOMBRE:      Práctica 2.1.                                            *
*      FECHA:       25 de marzo de 2022.                                     *
*      VERSIÓN:     1.0.                                                     *
*                                                                            *
*      AUTOR:       Mondragón Delgado Mezly Zahory                           *
*                   Montaño Ruvalcaba Luis Alberto                           *
*                   Paz Zamora Alfredo                                       *
*                   Ramírez Díaz Radames Oswaldo                             *
*                   Ramírez García Carlos Antonio                            *
*                                                                            *
*      E-MAIL:      mmondragon@ucol.mx                                       *
*                   lmontano@ucol.mx                                         *
*                   apaz0@ucol.mx                                            *
*                   rramirez31@ucol.mx                                       *
*                   cramirez28@ucol.mx                                       *
*                                                                            *
*      COMPAÑÍA:    Universidad de Colima - Facultad de Telemática.          *
*                                                                            *
*      uC:          ESP832.                                                  *
*      Nombre:      ESP832.                                                  *
*                                                                            *
******************************************************************************
*                                                                            *
*      DESCRIPCIÓN DEL PROGRAMA: Arquitectura de software para implementar   *
*      un sistema en la dómotica haciendo uso de sensores y actuadores asi   *
*      como módulos de almacenamiento, visualización de datos y transmición  *
*      de la información por medio de un broker del servidor mosquitto       *
*      via MQTT                                                              *  
*                                                                            *
******************************************************************************/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~IMPORTACIÓN DE LIBRERÍAS~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "Practica2.h"

//Librería para manejo de String
#include <cstring>

//Librería wifi esp32
#include <WiFi.h>
#include <PubSubClient.h>


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~CONEXIÓN MQTT~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
const char* ssid = "zaholy"; //Nombre de la red WiFi
const char* password = "pelusatony"; //Password de la red WiFi

const char* mqtt_server = "test.mosquitto.org"; //Dirección de Broker mosquitto.

//Crear cliente MQTT con la librería PubSubClient
WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0; //Almacenar último mensaje recibido

//Crear buffer char para mensajes recibidos
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

//Función conexión a red WiFi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectado a "); //Imprime el nombre de la red WiFi
  Serial.println(ssid);  

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); //Iniciar la conexíon a la red WiFi

  while (WiFi.status() != WL_CONNECTED) { //Verificar si la red WiFi esta disponible
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi conectado"); //Imprime la conexión exitosa a la red WiFi
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP()); //Imprime la dirección IP asignada
}

//Función para recibir tramas MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje del tema [");
  Serial.print(topic); //Imprime el topic de la trama MQTT
  Serial.print("] : ");
  
  String message;
  for (int i = 0; i < length; i++) {
    message = message + (char) payload[i]; //Concatena el mensaje en un String
  }
  Serial.print(message); //Imprime el mensaje recibido
  Serial.println();
}

//Función para reconectarse a MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando la conexión MQTT...");
    String clientId = "ESP32Client-"; //Crea id del cliente MQTT
    clientId += String(random(0xffff), HEX); //Concatena un numero random hexadecimal
    if (client.connect(clientId.c_str())) {
      Serial.println("conectado");
      client.subscribe("esp32-RALMT/#"); //Se suscribe y escucha las tramas
    } else {
      Serial.print("fallido, rc =");
      Serial.print(client.state()); //Imprime estado del cliente
      Serial.println(" inténtalo de nuevo en 5 segundos");
      delay(5000);
    }
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~SETUP - INICIALIZACIÓN~~~~~~~~~~~~~~~~~~~~~~~~*/

void setup(void) {

  Serial.begin(115200); //Configuración del BaudRate

  //Inicializar la configuración de los dispositivos
  RTC.initRTC();
  microSD.initMicroSD();
  sensor.initDHT11();
  lcd.
  actuator.initBuzzer();

  pinMode(32, OUTPUT); //SENSOR DHT11 modo salida
  pinMode(15, INPUT); //SENSOR PIR modo entrada
  pinMode(26, OUTPUT); //BUZZER modo salida
  pinMode(25, OUTPUT); //RELAY RSS  modo salida
  digitalWrite(25,LOW); //Inicia el relay encendido

  setup_wifi(); //Conectarse a WiFi
  client.setServer(mqtt_server, 1883); //Usar el puerto 1883
  client.setCallback(callback); //Establece la función para recibir mensajes

  tasks.create_file(SD, "/Clima.txt", "Datos obtenidos\n"); //Crea un archivo y agrega una línea de texto
  tasks.create_file(SD, "/Acciones.txt", "Datos obtenidos\n"); //Crea un archivo y agrega una línea de texto
  tasks.create_file(SD, "/Advertencias.txt", "Datos obtenidos\n"); //Crea un archivo y agrega una línea de texto
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~FUNCIÓN PRINCIPAL~~~~~~~~~~~~~~~~~~~~~~~~*/

void loop ( void ) {
  //Se conecta al Broker MQTT Mosquitto
  if (!client.connected()) {
    reconnect();
  }

  client.loop(); //Procesar las tramas MQTT
    
  String date =  tasks.get_date();
  int movement = tasks.get_movement(); //Obtiene el valor del movimiento
  int brightness = tasks.get_brightness();  //Obtiene el valor de la luminosidad
  int temperature = tasks.get_temperature(); //Obtiene  valor de la temperatura
  int humidity = tasks.get_humidity(); //Obtiene valor de humedad  

  int n = date.length(); //Longitud de la variable date
  char dateString[n+1]; //Crea un char buffer char
  strcpy(dateString, date.c_str()); //Guarda el string en un buffer char

   if(brightness > 340 and  movement  == 1){
      tasks.LED_ON(); //Funcion que enciende el LED
      Serial.println("ENCENDER LED");
      char accion[500];
      strcpy(accion, tasks.create_json_action(date, "Foco encendido").c_str()); //Crea un JSON y se guarda en el buffer de accion
      client.publish("esp32-RALMT/accion", accion); //Publica un JSON en el topic /accion
      tasks.append_file(SD, "/Acciones.txt", accion); //Agrega el JSON al archivo Acciones.txt
 
      char advertencia[500];
      strcpy(advertencia, tasks.create_json_warning(date, "Se detecto movimiento").c_str());//Crea un JSON de advertencia y se guarda en el buffer advertencia
      client.publish("esp32-RALMT/advertencia", advertencia); //Publica un JSON en el topic /advertencia
      tasks.append_file(SD, "/Advertencias.txt", advertencia); //Agrega el JSON al archivo Advertencias.txt

       }else{
         if (brightness != -1 or movement != -1)
        {
          tasks.LED_OFF(); //Funcion que apaga el LED 
          Serial.println("APAGAR LED");
          
          char accion[500];
          strcpy(accion, tasks.create_json_action(date, "Foco apagado").c_str()); //Crea un JSON de accion y se guarda en el buffer accion
          client.publish("esp32-RALMT/accion", accion); //Publica un JSON en el topic /accion
          tasks.append_file(SD, "/Acciones.txt", accion); //Agrega el JSON al archivo Acciones.txt 
         }
       }
    if (temperature!= 0 or humidity !=0)
  {
    tasks.printTempHumDate(temperature, humidity, date); //Imprime los datos en el LCD
    Serial.println("DATOS RECOPILADOS");

    char clima[500];
    strcpy(clima, tasks.create_json_temp_hum(date, temperature, humidity).c_str()); //Crea un JSON de clima  y se guarda en el buffer clima
    client.publish("esp32-RALMT/clima", clima); //Publica un JSON en el topic /clima 
    tasks.append_file(SD, "/Clima.txt", clima); //Agrega el JSON al archivo Clima.txt
   }
  
  if(temperature >= 40)
  {
    tasks.Buzzer_ON(); //Enciende el buzzer
    char accion[500];
    strcpy(accion, tasks.create_json_action(date,"Buzzer encendido").c_str()); //Crea un JSON de accion y se guarda en el buffer accion
    client.publish("esp32-RALMT/accion", accion); //Publica un JSON en el topic /accion
    tasks.append_file(SD, "/Acciones.txt", accion);   //Agrega el JSON al archivo Acciones.txt 
 
    char advertencia[500];
    strcpy(advertencia, tasks.create_json_warning(date, "Temperatura muy alta").c_str()); //Crea un JSON de advertencia y se guarda en el buffer advertencia
    client.publish("esp32-RALMT/advertencia", advertencia); //Publica un JSON en el topic /advertencia
    tasks.append_file(SD, "/Advertencias.txt", advertencia); //Agrega el JSON al archivo Advertencias.txt 
 
   }else{
    tasks.Buzzer_OFF(); //Apaga el buzzer
    
    char accion[500];
    strcpy(accion, tasks.create_json_action(date,"Buzzer apagado").c_str()); //Crea un JSON de accion y se guarda en el buffer accion
    client.publish("esp32-RALMT/accion", accion); //Publica un JSON en el topic /accion
    tasks.append_file(SD, "/Acciones.txt", accion);  //Agrega el JSON al archivo Acciones.txt
  }  
  delay(1000);
}
  
