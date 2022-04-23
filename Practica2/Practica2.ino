/*****************************************************************************
*                                                                            *
*      NOMBRE:      Práctica 1.2.                                            *
*      FECHA:       17 de marzo de 2022.                                     *
*      VERSIÓN:     1.0.                                                     *
*                                                                            *
*      AUTOR:       Mondragón Delgado Mezly Zahory
*                   Montaño Ruvalcabe Luis Alberto
*                   Paz Zamora Alfredo
*                   Ramirez Diaz Radames Oswaldo
*                   Ramirez Garcia Carlos Antonio
*                                                                            *
*      E-MAIL:      mmondragon@uco.mx                                        *
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

/*#define SD_CS 5
#define SD_SCK 18
#define SD_MOSI 23
#define SD_MISO 19
File file;

void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}*/

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
      client.subscribe("esp32/#");
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
  control.initRTC();
  //control.initSD(18, 19, 23, 5);
  pinMode(32, OUTPUT); //SENSOR DHT11
  pinMode(15, INPUT); //SENSOR PIR
  pinMode(35, OUTPUT); //BUZZER
  pinMode(34, OUTPUT); //RELAY RSS 
  digitalWrite(34,LOW); //iNICIALIAR RELAY
  pinMode(4, INPUT); //SENSOR LDR
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  /*SPIClass sd_spi(HSPI);
    sd_spi.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  
    if (!SD.begin(SD_CS, sd_spi))
        Serial.println("SD Card: mounting failed.");
    else
        Serial.println("SD Card: mounted.");


  tasks.create_file(SD, "/Data.txt", "Datos obtenidos\n");*/
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
  if(brightness > 800 &&  movement == 1){
      tasks.LED_ON();
      Serial.println("ENCENDER LED");
      }else{
        if (brightness != -1 && movement != -1)
        {
          tasks.LED_OFF();
          Serial.println("APAGAR LED");
        }
      }
  if (temperature!= 0 and humidity !=0)
  {
    Serial.println("IMPRIMIR DATOS");
    tasks.printTempHumDate(temperature, humidity, date);
    
    
    char  buf [300];
    snprintf(buf, sizeof(buf),"{\"time\":\"%d\",\"temp\":%d,\"humedad\":%d}", dateString, temperature, humidity);
    Serial.println(buf);
    client.publish("esp32/data", buf);
  }
  
  if(temperature >= 25)
  {
    tasks.Buzzer_ON();
  }else{
    tasks.Buzzer_OFF();
  }  
delay(1000);
}
