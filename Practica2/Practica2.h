/*~~~~~~~~~~~~~~~~~~~~~~~~~~~ARCHIVO HEADER~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~IMPORTACIÓN DE LIBRERIAS~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <WiFi.h>
  WiFiClient ESP32_WIFI;
  
#include <PubSubClient.h>
  PubSubClient client ( ESP32_WIFI );

#include <LiquidCrystal_I2C.h>
  LiquidCrystal_I2C lcd(0x27, 16, 2); //Configura la LCD a 16x2

#define PIR_PIN 15
#define BUZZER_PIN 26
#define RELAY_PIN 25
#define LDR_PIN 39
#define DHT11_PIN 32
#define MICROSD_PIN 5
#define EXTENSION ".json"

#include <Config.h>
#include <EasyBuzzer.h> 

#include <DHT.h>
#include <DHT_U.h>
  DHT dht(DHT11_PIN, DHT11);

#include <Wire.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <SD.h>
#include "RTClib.h"
 RTC_DS1307 rtc;
 
File microSD_file;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~IMPORTACIÓN DE CLASES~~~~~~~~~~~~~~~~~~~~~~~~*/

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
