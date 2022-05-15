/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class class_sensors {

  public: //Variables Públicas
    int temperatura, humedad;            
    int valorLDR = 0; 
    int valorPIR = 0;

 public:  //Métodos Públicos
    void initDHT11( void );
    int obtener_temperatura( void );  
    int obtener_humedad( void );      
    int obtener_luminosidad( void );   
    int obtener_movimiento( void );  
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODOS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//Inicilizar el sensor DHT11
void class_sensors::initDHT11( void ){
  dht.begin();
}

//Método para obtener la temperatura del sensor DHT11
int class_sensors::obtener_temperatura( void ){
  temperatura = dht.readTemperature();
  return temperatura; //Retorna la temperatura
}

 //Método para obtener la humedad del sensor DHT11
int class_sensors::obtener_humedad( void ){
  humedad = dht.readHumidity();
  return humedad; //Retorna la humedad
}

//Método para obtener la luminisidad
int class_sensors::obtener_luminosidad( void ){
  valorLDR = analogRead(LDR_PIN); 
  return valorLDR; //Retorna la luminosidad
}

//Método para obtener el movimiento
int class_sensors::obtener_movimiento( void ){
  valorPIR = digitalRead(PIR_PIN); 
  return valorPIR; //Retorna el movimiento
} 
