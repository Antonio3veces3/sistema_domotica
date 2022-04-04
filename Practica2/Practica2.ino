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
*      uC:          ESP8266.                                                 *
*      Nombre:      ESP8266.                                                 *
*                                                                            *
******************************************************************************
*                                                                            *
*      DESCRIPCIÓN DEL PROGRAMA: Arquitectura de software para explorar      *
*      un poco el uso de métodos y clases para la resolución de problemas.   *  
*                                                                            *
******************************************************************************/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ BANDERAS ~~~~~~~~~~~~~~*/


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~IMPORTACIÓN DE LIBRERÍAS~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "Practica2.h"


void setup( void ) {

  Serial.begin ( 115200 );
  beginDHT11();
  initLCD();
  pinMode(12, OUTPUT); //SENSOR DHT11
  pinMode(13, INPUT); //SENSOR PIR
  pinMode(14, OUTPUT); //BUZZER
  pinMode(0, OUTPUT); //RELAY RSS 
  digitalWrite(12,LOW);
}

void loop ( void ) {
  
  /*tasks.get_temperature();
  tasks.get_humidity();
  tasks.get_brightness();
  tasks.get_motion(); 
  tasks.get_movement();*/

  //SI JALA
  int movement = tasks.get_movement();
  int brightness = tasks.get_brightness();
  float temperature = tasks.get_temperature();
  float humidity = tasks.get_humidity();

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
  if (temperature!= 0 or humidity !=0)
  {
    Serial.println("IMPRIMIR DATOS");
    tasks.printTempHum(temperature, humidity);
  }
  

  if(temperature >= 25.00)
  {
    tasks.Buzzer_ON();
  }else{
    tasks.Buzzer_OFF();
  }  
delay(1000);
}
