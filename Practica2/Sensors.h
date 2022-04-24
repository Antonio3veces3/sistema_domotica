/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~IMPORTACIÓN DE LIBRERÍAS~~~~~~~~~~~~~~~~~~~~~~~~~*/

//Librerías para sensor DHT11
#include <DHT.h>
#include <DHT_U.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class class_sensors {

  public: //Variables Públicas
    int temperatura, humedad;            
    int valorLDR = 0; 
    int valorPIR = 0;

 public:  //Métodos Públicos
    int obtener_temperatura(void);  
    int obtener_humedad(void);      
    int obtener_luminosidad(void);   
    int obtener_movimiento(void);  
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CONFIGURACION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

DHT dht( dht11, DHT11 ); //Crea instancia DHT11

//Inicilizar el sensor DHT11
void beginDHT11 ( void ){
  dht.begin();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODOS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//Método para obtener la temperatura del sensor DHT11
int class_sensors::obtener_temperatura ( void ){
  temperatura = dht.readTemperature();
  return temperatura; //Retorna la temperatura
}

 //Método para obtener la humedad del sensor DHT11
int class_sensors::obtener_humedad ( void ){
  humedad = dht.readHumidity();
  return humedad; //Retorna la humedad
}

//Método para obtener la luminisidad
int class_sensors::obtener_luminosidad ( void ){
  valorLDR = analogRead(ldr); 
  return valorLDR; //Retorna la luminosidad
}

//Método para obtener el movimiento
int class_sensors::obtener_movimiento ( void ){
  valorPIR = digitalRead(pir); 
  return valorPIR; //Retorna el movimiento
} 
