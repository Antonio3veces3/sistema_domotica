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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ BANDERAS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~IMPORTACIÓN DE LIBRERÍAS~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
 
#include "Sensors.h"



/*~~~~~~~~~~~~~~~~~~~~~~~INSTANCIAR UNA CLASE PARA USARLA~~~~~~~~~~~~~~~~~~~~~~~*/
  /*
   * (Nombre de la clase) + (espacio en blanco) + (nombre de la instancia) + (;)
   * Ejemplo:
   * class_ejemplo cj;
   */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


class_sensores cs;        // Instancia clase "class_ejemplo".
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CONFIGURACIÓN INICIAL~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void setup( void ) {

  Serial.begin ( 115200 ); // Configuración BaudRate, un sistema puede tener varios puertos seriales físicos.
  dht.begin();

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~CICLO INFINITO DE TRABAJO~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void loop ( void ) {
  
  //delay ( 2000 );            // Retraso en milisegundos.
  //cs.obtener_temperatura();
  //cs.obtener_humedad();

 
  //cj.metodo_ejemplo1 (  );      // Llamar método de una clase (requiere ser instanciada) [Instancia]+[.]+[Nombre del método].
  //Serial.print("Este es un mensaje sin salto de línea"); // mensaje por puerto serial sin salto de línea.
  //Serial.println("Este es un mensaje con salto de línea"); // mensaje por puerto serial con salto de línea.

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~Formatos de impresión númerica~~~~~~~~~~~~~~~~~~~~~~~~~~*/  
  //Serial.println(78, BIN); // Salida: "1001110"
  //Serial.println(78, OCT); // Salida: "116"
  //Serial.println(78, DEC); // Salida: "78"
  //Serial.println(78, HEX); // Salida: "4E"
  
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Truncamiento de decimales~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/ 
  //Serial.println(1.23456, 0); // Salida "1"
  //Serial.println(1.23456, 2); // Salida "1.23"
  //Serial.println(1.23456, 4); // Salida "1.2345"
  
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Leer información de un puerto Serial físico~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/ 
  
}
