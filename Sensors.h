/*~~~~~~~~~~~~~~~~~~~~~~~~IMPORTACIÓN DE LIBRERÍAS~~~~~~~~~~~~~~~~~~~~~~~~~*/

//Sensor de temperatura y humedad DHT11
#include <DHT.h>
#include <DHT_U.h>

//Sensor de luminosidad LDR
//Sensor de movimiento PIR
//Actuador Buzzer Activo
//Actuador Relay de Estado Solido 

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class class_sensors {

  public:                                   //Variables Públicas
    float temperatura, humedad;            //Reciben la temperatura y humedad del sensor DHT11

 public:                                  //Métodos Públicas
   float obtener_temperatura ( void );   //Método para obtener la temperatura del sensor DHT11
   float obtener_humedad ( void );       //Método para obtener la humedad del sensor DHT11
   void beginDHT11 ( void );
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PINES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//Sensor de temperatura y humedad DHT11
DHT dht( 4, DHT11 );
//Sensor de luminosidad LDR
//Sensor de movimiento PIR
//Actuador Buzzer Activo
//Actuador Relay de Estado Solido 

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CONFIGURACION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODOS~~~~~~~~~~~~~~~~~~~~~~~*/

void beginDHT11 ( void ){
  dht.begin();
}


//Sensor de temperatura y humedad DHT11
float class_sensors::obtener_temperatura ( void ){
  temperatura = dht.readTemperature();
  return temperatura;
}

float class_sensors::obtener_humedad ( void ){
  humedad = dht.readHumidity();
  return humedad;
}

//Sensor de luminosidad LDR
//Sensor de movimiento PIR
//Actuador Buzzer Activo
//Actuador Relay de Estado Solido 
