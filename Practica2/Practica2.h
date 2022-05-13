/*~~~~~~~~~~~~~~~~~~~~~~~~~~~ARCHIVO HEADER~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~IMPORTACIÓN DE CLASES~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <ArduinoJson.h>

#include <LiquidCrystal_I2C.h>

#include <SPI.h>
#include <SD.h>

//Librerías para manejo del módulo RTC
#include <Wire.h>
#include "RTClib.h"

//Librerías para manejo del Buzzer
#include <Config.h>
#include <EasyBuzzer.h> 

//Librerías para sensor DHT11
#include <DHT.h>
#include <DHT_U.h>

//Librerias para MQTT
#include <WiFi.h>
#include <PubSubClient.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~DEFINICIÓN DE PINES Y EXTENSIONES DE ARCHIVOS~~~~~~~~~~~~~~~~~~~~~~~~*/
#define MICROSD_PIN 5
#define BUZZER_PIN 26
#define DHT11_PIN 32
#define PIR_PIN 15
#define RELAY_PIN 25
#define LDR_PIN 39

#define EXTENSION ".json"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~CONFIGURACION~~~~~~~~~~~~~~~~~~~~~~~~*/

RTC_DS1307 rtc;
DHT dht(DHT11_PIN, DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2); //Configura la LCD a 16x2
File microSD_file;
WiFiClient ESP32_WIFI;
PubSubClient client ( ESP32_WIFI );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~IMPORTCIÓN DE CLASES~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "RTC.h"
class_rtc RTC;

#include "MicroSD.h"
class_microSD microSD;

#include "Actuators.h";
class_actuators actuator;    //Importa la clase de actuadores

#include "Sensors.h";
class_sensors sensor;          //Importa la clase de sensores

#include "LCD.h"
class_lcd lcd;

#include "MQTT.h"
class_MQTT mqtt;              //Importa la clase de MQTT

#include "Tasks.h";
class_tasks tasks;             //Importa la clase de tasks
