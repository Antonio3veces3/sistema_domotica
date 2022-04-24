/*~~~~~~~~~~~~~~~~~~~~~~~~~~~ARCHIVO HEADER~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~DEFINICIÓN DE GPIOS~~~~~~~~~~~~~~~~~~~~~~~~*/
#define dht11 32  //GPIO Sensor DHT11
#define pir 15    //GPIO Sensor PIR
#define relay 34  //GPIO Relay
#define ldr 39    //GPIO Sensor LDR
#define buzzer 26 //GPIO Buzzer

#define SD_CS 5    //GPIO pin SD_CS
#define SD_SCK 18  //GPIO pin SD_SCK
#define SD_MOSI 23 //GPIO pin SD_MOSI
#define SD_MISO 19 //GPIO pin SD_MISO

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~IMPORTACIÓN DE CLASES~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "DataController.h";
class_data_controller control; //Importa la clase controller

#include "Actuators.h";
class_actuators actuadores;    //Importa la clase de actuadores

#include "Sensors.h";
class_sensors sensor;          //Importa la clase de sensores

#include "Tasks.h";
class_tasks tasks;             //Importa la clase de tasks



