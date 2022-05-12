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


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~CONEXIÓN MQTT~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
unsigned long lastMsg = 0; //Almacenar último mensaje recibido

//Crear buffer char para mensajes recibidos
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~SETUP - INICIALIZACIÓN~~~~~~~~~~~~~~~~~~~~~~~~*/

void setup(void) {

  Serial.begin(115200); //Configuración del BaudRate

  //Inicializar la configuración de los dispositivos
  RTC.initRTC();
  microSD.initMicroSD();
  sensor.initDHT11();
  lcd.
  actuator.initBuzzer();
  mqtt.setup_WiFi ( );
  mqtt.set_MQTT_server ( );

  pinMode(32, OUTPUT); //SENSOR DHT11 modo salida
  pinMode(15, INPUT); //SENSOR PIR modo entrada
  pinMode(26, OUTPUT); //BUZZER modo salida
  pinMode(25, OUTPUT); //RELAY RSS  modo salida
  digitalWrite(25,LOW); //Inicia el relay encendido


  tasks.create_file(SD, "/Clima.txt", "Datos obtenidos\n"); //Crea un archivo y agrega una línea de texto
  tasks.create_file(SD, "/Acciones.txt", "Datos obtenidos\n"); //Crea un archivo y agrega una línea de texto
  tasks.create_file(SD, "/Advertencias.txt", "Datos obtenidos\n"); //Crea un archivo y agrega una línea de texto
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~FUNCIÓN PRINCIPAL~~~~~~~~~~~~~~~~~~~~~~~~*/

void loop ( void ) {
    
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
  
