/*~~~~~~~~~~~~~~~~~~~~~~~~IMPORTACIÓN DE LIBRERÍAS~~~~~~~~~~~~~~~~~~~~~~~~~*/
//Sensor de temperatura y humedad DHT11
#include <DHT.h>
#include <DHT_U.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class class_sensors {

  public:                                   //Variables Públicas
    int temperatura, humedad;            //Reciben la temperatura y humedad del sensor DHT11
    int valorLDR = 0;                    // Variable donde se almacena el valor del LDR
    int valorPIR = 0;

 public:                                  //Métodos Públicas
    int obtener_temperatura ( void );   //Método para obtener la temperatura del sensor DHT11
    int obtener_humedad ( void );       //Método para obtener la humedad del sensor DHT11
    int obtener_luminosidad ( void );   //Método para obtener la luminisidad
    int obtener_movimiento ( void );   //Método para obtener el movimiento

    void beginDHT11 ( void );            //Método para inicilizar el sensor DHT11
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CONFIGURACION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//Sensor de temperatura y humedad DHT11
DHT dht( 32, DHT11 ); //PIN DHT11

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODOS~~~~~~~~~~~~~~~~~~~~~~~*/

void beginDHT11 ( void ){
  dht.begin();
}

//Sensor de temperatura y humedad DHT11
int class_sensors::obtener_temperatura ( void ){
  temperatura = dht.readTemperature();
  return temperatura;
}

int class_sensors::obtener_humedad ( void ){
  humedad = dht.readHumidity();
  return humedad;
}

//Sensor de luminosidad LDR
int class_sensors::obtener_luminosidad ( void ){
  valorLDR = analogRead(4); //PIN LDR
  return  valorLDR;
  
}

//Sensor de detección movimiento PIR
int class_sensors::obtener_movimiento ( void ){
  valorPIR = digitalRead(15); //PIN PIR
  return valorPIR;
} 
