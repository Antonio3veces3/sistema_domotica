/*****************************************************************************
*                                                                            *
*      NOMBRE:      Práctica 2.1.                                            *
*      FECHA:       16 de mayo de 2022.                                     *
*      VERSIÓN:     1.1.                                                     *
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
*      como módulos de almacenamiento, visualización de datos y transmisión  *
*      de la información por medio de un broker del servidor mosquitto       *
*      via MQTT                                                              *  
*                                                                            *
******************************************************************************/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~IMPORTACIÓN DE LIBRERÍAS~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "Practica2.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~SETUP - INICIALIZACIÓN~~~~~~~~~~~~~~~~~~~~~~~~*/

void setup(void) {

  Serial.begin(115200); //Configuración del BaudRate

  pinMode(DHT11_PIN, OUTPUT); //SENSOR DHT11 modo salida
  pinMode(PIR_PIN, INPUT); //SENSOR PIR modo entrada
  pinMode(BUZZER_PIN, OUTPUT); //BUZZER modo salida
  pinMode(RELAY_PIN, OUTPUT); //RELAY RSS  modo salida
  digitalWrite(RELAY_PIN,LOW); //Inicia el relay encendido

  //Inicializar la configuración de los dispositivos 
  tasks.init_devices();

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~FUNCIÓN PRINCIPAL~~~~~~~~~~~~~~~~~~~~~~~~*/

void loop(void){

  RTC.getDataTime();
  mqtt.reconnect_MQTT();
    
  //int movement = tasks.get_movement(); //Obtiene el valor del movimiento
  //int brightness = tasks.get_brightness();  //Obtiene el valor de la luminosidad
  //int temperature = tasks.get_temperature(); //Obtiene  valor de la temperatura
  //int humidity = tasks.get_humidity(); //Obtiene valor de humedad  

  if(tasks.get_brightness() != -1 and tasks.get_movement()!= -1){
    if(tasks.brightness > 360 and tasks.isMov == 1){
      tasks.LED_ON(); //Funcion que enciende el LED
      Serial.println("ENCENDER LED");
      tasks.save_file("Foco encendido", "Se detecto movimiento"); //Guarda el dato en el JSON
      tasks.publish_MQTT(); //Publica la infomación por MQTT 
    }else{
      tasks.LED_OFF(); //Funcion que apaga el LED
    }
  }
  

  if (tasks.get_temperature()!= 0 or tasks.get_humidity() !=0){
    tasks.printData(tasks.temperature, tasks.humidity, tasks.brightness); //Imprime los datos en el LCD
    tasks.save_file("", ""); //Guarda el dato en el JSON
    tasks.publish_MQTT(); //Publica la infomación por MQTT
  }
    

  if(tasks.temperature >= 40)
  {
    tasks.Buzzer_ON(); //Enciende el buzzer
    Serial.println("ENCIENDE BUZZER");
    tasks.save_file("Buzzer encendido", "Temperatura alta"); //Guarda el dato en el JSON
    tasks.publish_MQTT();  //Publica la infomación por MQTT
  }
  else{
    tasks.Buzzer_OFF(); //Apaga el buzzer
  }  
}
  
