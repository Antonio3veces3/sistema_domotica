/*****************************************************************************
*                                                                            *
*      NOMBRE:      Práctica 2.1.                                            *
*      FECHA:       25 de marzo de 2022.                                     *
*      VERSIÓN:     1.0.                                                     *
*                                                                            *
*      AUTOR:       Mondragón Delgado Mezly Zahory
*                   Montaño Ruvalcabe Luis Alberto
*                   Paz Zamora Alfredo
*                   Ramirez Diaz Radames Oswaldo
*                   Ramirez Garcia Carlos Antonio
*                                                                            *
*      E-MAIL:      mmondragon@ucol.mx                                        *
*      COMPAÑÍA:    Universidad de Colima - Facultad de Telemática.          *
*                                                                            *
*      uC:          ESP832.                                                 *
*      Nombre:      ESP832.                                                 *
*                                                                            *
******************************************************************************
*                                                                            *
*      DESCRIPCIÓN DEL PROGRAMA: Arquitectura de software para explorar      *
*      un poco el uso de métodos y clases para la resolución de problemas.   *  
*                                                                            *
******************************************************************************/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~IMPORTACIÓN DE LIBRERÍAS~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "Practica2.h"
#include <ArduinoJson.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include "FS.h"
#include "SD.h"
#include "SPI.h"

//Libreria wifi esp32
#include <WiFi.h>
#include <PubSubClient.h>

#define SD_CS 5
#define SD_SCK 18
#define SD_MOSI 23
#define SD_MISO 19

const char* ssid = "zaholy";
const char* password = "pelusatony";

const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

int value = 0;

void setup_wifi() {
  delay(10);
  // Empezamos por conectarnos a una red WiFi
  Serial.println();
  Serial.print("Conectado a ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje del tema [");
  Serial.print(topic);
  Serial.print("] : ");
  
  String message;
  for (int i = 0; i < length; i++) {
    message = message + (char) payload[i];
  }
  Serial.print(message);
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando la conexión MQTT...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("conectado");
      client.subscribe("esp32-RALMT/#");
    } else {
      Serial.print("fallido, rc =");
      Serial.print(client.state());
      Serial.println(" inténtalo de nuevo en 5 segundos");
      delay(5000);
    }
  }
}

void setup( void ) {

  Serial.begin ( 115200 );
  beginDHT11();
  initLCD();
  actuadores.initBuzzer();
  control.initRTC();
  pinMode(32, OUTPUT); //SENSOR DHT11
  pinMode(15, INPUT); //SENSOR PIR
  pinMode(26, OUTPUT); //BUZZER
  pinMode(25, OUTPUT); //RELAY RSS 
  digitalWrite(25,LOW); //INICIALIAR RELAY

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  SPIClass sd_spi(HSPI);
    sd_spi.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  
    if (!SD.begin(SD_CS, sd_spi))
        Serial.println("SD Card: mounting failed.");
    else
        Serial.println("SD Card: mounted.");

  tasks.create_file(SD, "/Data.txt", "Datos obtenidos\n");
}

void loop ( void ) {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  String date = tasks.get_date();
  int movement = tasks.get_movement();
  int brightness = tasks.get_brightness();
  int temperature = tasks.get_temperature();
  int humidity = tasks.get_humidity();

  int n = date.length();
  char dateString[n+1];
  strcpy(dateString, date.c_str());

  if(brightness > 340 and  movement == 1){
      tasks.LED_ON();
      Serial.println("ENCENDER LED");
      char accion[500];
      strcpy(accion, tasks.create_json_action(date, "Foco encendido").c_str());
      client.publish("esp32-RALMT/accion", accion);
      tasks.append_file(SD, "/Data.txt", accion);

      char advertencia[500];
      strcpy(advertencia, tasks.create_json_warning(date, "Se detecto movimiento").c_str());
      client.publish("esp32-RALMT/advertencia", advertencia);
      tasks.append_file(SD, "/Data.txt", advertencia);
      }else{
        if (brightness != -1 or movement != -1)
        {
          tasks.LED_OFF();
          Serial.println("APAGAR LED");
          
          char accion[500];
          strcpy(accion, tasks.create_json_action(date, "Foco apagado").c_str());
          client.publish("esp32-RALMT/accion", accion);
          tasks.append_file(SD, "/Data.txt", accion);
        }
      }
  if (temperature!= 0 and humidity !=0)
  {
    tasks.printTempHumDate(temperature, humidity, date);
    Serial.println("DATOS RECOPILADOS");

    char clima[500];
    strcpy(clima, tasks.create_json_temp_hum(date, temperature, humidity).c_str());
    client.publish("esp32-RALMT/clima", clima);
    tasks.append_file(SD, "/Data.txt", clima);
  }
  
  if(temperature >= 40)
  {
    tasks.Buzzer_ON();
    char accion[500];
    strcpy(accion, tasks.create_json_action(date,"Buzzer encendido").c_str());
    client.publish("esp32-RALMT/accion", accion);
    tasks.append_file(SD, "/Data.txt", accion);

    char advertencia[500];
    strcpy(advertencia, tasks.create_json_warning(date, "Temperatura muy alta").c_str());
    client.publish("esp32-RALMT/advertencia", advertencia);
    tasks.append_file(SD, "/Data.txt", advertencia);

  }else{
    tasks.Buzzer_OFF();
    
    char accion[500];
    strcpy(accion, tasks.create_json_action(date,"Buzzer apagado").c_str());
    client.publish("esp32-RALMT/accion", accion);
    tasks.append_file(SD, "/Data.txt", accion);
  }  
delay(1000);
}
