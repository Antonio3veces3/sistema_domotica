/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ARCHIVO HEADER~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~LIBRERIAS y PINES UTILIZADOS~~~~~~~~~~~~~~~~~~~~~~*/

#include <WiFi.h>                  //Librería para conectar vía WiFi la ESP32
  WiFiClient ESP32_WIFI;            //Instancia el cliente para utilizar el módulo WIFI de la placa ESP32
  
#include <PubSubClient.h>               //Librería para conectar la ESP32 por MQTT
  PubSubClient client ( ESP32_WIFI );   //Instancia el cliente (ESP32_WIFI) para conectarse a MQTT
  
#include <LiquidCrystal_I2C.h>          //Librería para usar la LCD mediante el módulo I2C
  LiquidCrystal_I2C lcd(0x27, 16, 2);   //Se instancia la LCD 

#include "RTClib.h"         //Librería para hacer uso del RTC
 RTC_DS1307 rtc;            //Se instancia el RTC

#include <Wire.h>         //Librería para establecer comunicación con dispositivos que usan el protocolo I2C
#include <SPI.h>          //Librería para establecer comunicación con dispositivos que usan el protocolo SPI
#include <SD.h>            //Librería para escribir y leer en tarjetas SD
#include <EasyBuzzer.h>   //Librería para hacer uso del buzzer
#include <ArduinoJson.h>  //Librería para hacer uso del objeto JSON

//Definición de pines de los dispositivos utilizados
#define PIR_PIN 15
#define BUZZER_PIN 26
#define RELAY_PIN 25
#define LDR_PIN 39
#define DHT11_PIN 32
#define MICROSD_PIN 5

#define EXTENSION ".json"  //Se define la extensión del archivo almacenado en la SD
File microSD_file; //Se define el archivo con el que se va a trabajar en la SD

//Librerías para hacer uso del sensor DHT11
#include <DHT.h>
#include <DHT_U.h>
  DHT dht(DHT11_PIN, DHT11); //Se instancia el sensor en el pin 32 de la ESP32

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~IMPORTACIÓN DE CLASES~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "RTC.h"
 class_rtc RTC;                 //Importa la clase RTC

#include "Sensors.h";
 class_sensors sensor;          //Importa la clase de sensores

#include "Actuators.h";
 class_actuators actuator;      //Importa la clase de actuadores

#include "MicroSD.h"
 class_microSD MSD;          //Importa la clase de la microSD

#include "MQTT.h"
 class_MQTT mqtt;              //Importa la clase de MQTT

#include "Tasks.h";
 class_tasks tasks;             //Importa la clase de tasks
