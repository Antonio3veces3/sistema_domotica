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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~SETUP - INICIALIZACIÓN~~~~~~~~~~~~~~~~~~~~~~~~*/

void setup(void) {

  Serial.begin(115200); //Configuración del BaudRate

  pinMode(DHT11_PIN, OUTPUT); //SENSOR DHT11 modo salida
  pinMode(PIR_PIN, INPUT); //SENSOR PIR modo entrada
  pinMode(BUZZER_PIN, OUTPUT); //BUZZER modo salida
  pinMode(RELAY_PIN, OUTPUT); //RELAY RSS  modo salida
  digitalWrite(RELAY_PIN,LOW); //Inicia el relay encendido

  //Inicializar la configuración de los dispositivos
  RTC.initRTC();
  MSD.initMicroSD();
  tasks.init_devices();
  mqtt.setup_WiFi ( );
  mqtt.set_MQTT_server ( );
  
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~FUNCIÓN PRINCIPAL~~~~~~~~~~~~~~~~~~~~~~~~*/

void loop ( void ) {

  RTC.getDataTime();
    
  int movement = tasks.get_movement(); //Obtiene el valor del movimiento
  int brightness = tasks.get_brightness();  //Obtiene el valor de la luminosidad
  int temperature = tasks.get_temperature(); //Obtiene  valor de la temperatura
  int humidity = tasks.get_humidity(); //Obtiene valor de humedad  

  if(brightness > 340 and  movement  == 1){
      tasks.LED_ON(); //Funcion que enciende el LED
      Serial.println("ENCENDER LED");
      tasks.save_file("Foco encendido", "Se detectó movimiento");
      tasks.publish_MQTT();
    }
    else{
      if (brightness != -1 or movement != -1)
      {
        tasks.LED_OFF(); //Funcion que apaga el LED 
        Serial.println("APAGAR LED");
        tasks.save_file("Foco apagado", "No se detectó movimiento");
        tasks.publish_MQTT();
      }
    }

  if (temperature!= 0 or humidity !=0)
    tasks.printData(temperature, humidity, brightness); //Imprime los datos en el LCD

  if(temperature >= 40)
  {
    tasks.Buzzer_ON(); //Enciende el buzzer
    Serial.println("ENCIENDE BUZZER");
    tasks.save_file("Buzzer encendido", "No se detectó movimiento");
    tasks.publish_MQTT();
  }
  else{
    tasks.Buzzer_OFF(); //Apaga el buzzer
    Serial.println("APAGA BUZZER");
    tasks.save_file("Buzzer apagado", "No se detectó movimiento");
    tasks.publish_MQTT();
  }  
  delay(1000);
}
  
