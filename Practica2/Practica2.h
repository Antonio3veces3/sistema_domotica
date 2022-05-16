/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ARCHIVO HEADER~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~LIBRERIAS y PINES UTILIZADOS~~~~~~~~~~~~~~~~~~~~~~*/

//Librería para conectar via WiFi la ESP32
#include <WiFi.h>
  WiFiClient ESP32_WIFI;
  
//Librería para conectar la ESP32 por MQTT
#include <PubSubClient.h>
  PubSubClient client ( ESP32_WIFI );

//Librería para usar la LCD mediante el módulo I2C
#include <LiquidCrystal_I2C.h>
  LiquidCrystal_I2C lcd(0x27, 16, 2); //Configura la LCD a 16x2

//Definición de pines de los dispositivos utilizados
#define PIR_PIN 15
#define BUZZER_PIN 26
#define RELAY_PIN 25
#define LDR_PIN 39
#define DHT11_PIN 32
#define MICROSD_PIN 5

//Se define la extensión del archivo almacenado en la SD
#define EXTENSION ".json"

//Librería para hacer uso del buzzer
#include <Config.h>
#include <EasyBuzzer.h> 

//Librería para hacer uso del sensor DHT11
#include <DHT.h>
#include <DHT_U.h>
  DHT dht(DHT11_PIN, DHT11); //Se instancia el sensor en el pin 32 de la ESP32

//Librería para hacer uso del objeto JSON
#include <ArduinoJson.h>

//Librería para hacer uso de la SD
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

//Librería para hacer uso del RTC
#include "RTClib.h"
 RTC_DS1307 rtc; //Se instancia el RTC
 
File microSD_file; //Se define el archivo con el que se va a trabajar en la SD

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~IMPORTACIÓN DE CLASES~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "RTC.h"
 class_rtc RTC;                 //Importa la clase RTC

#include "Sensors.h";
 class_sensors sensor;          //Importa la clase de sensores

#include "Actuators.h";
 class_actuators actuator;      //Importa la clase de actuadores

#include "MicroSD.h"
 class_microSD MSD;          //Importa la clase de la microSD

#include "LCD.h"              
 class_lcd LCD;                //Importa la clase de LCD

#include "MQTT.h"
 class_MQTT mqtt;              //Importa la clase de MQTT

#include "Tasks.h";
 class_tasks tasks;             //Importa la clase de tasks
