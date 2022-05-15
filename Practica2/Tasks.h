/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class class_tasks{

  public: //Variables Públicas
    unsigned long intervaloMQTT = 15000, timeMQTT = 0;
    unsigned long intervaloDL = 15000, timeDL = 0;
    unsigned long intervaloTemp = 5000, timeTemp = 0;  //Intervalo de tiempo temperatura
    unsigned long intervaloHum = 5000, timeHum = 0;   //Intervalo de tiempo humedad
    unsigned long intervaloLdr = 1000, timeLdr = 0;   //Intervalo de tiempo sensor LDR
    unsigned long intervaloMov = 1000, timeMov = 0;  //Intervalo de tiempo sensor PIR
    
  public: //Métodos Públicos
    void init_devices( void );
    int get_temperature( void );
    int get_humidity( void );
    int get_brightness( void );
    int get_movement( void );
    void LED_ON( void );
    void LED_OFF( void );
    void Buzzer_ON( void );
    void Buzzer_OFF( void );
    void printData( int, int, int );
    void publish_MQTT ( void );
    void save_file( String, String );
};


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODOS~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void class_tasks::init_devices( void ){

  RTC.initRTC();
  MSD.initMicroSD();
  LCD.initLCD();
  actuator.initBuzzer();
  sensor.initDHT11();
  mqtt.setup_WiFi ( );
  mqtt.set_MQTT_server ( );
  
}

//Obtiene la temperatura cada 5 segundos
int class_tasks::get_temperature( void ){
  if((millis() - timeTemp) >= intervaloTemp ){ //Intervalo de 5 segundos
    timeTemp = millis(); //Guarda el tiempo actual
    int temperature = sensor.obtener_temperatura(); //Obtiene temperatura
    Serial.print("Temperatura: ");
    Serial.println(temperature);
    return temperature; //Retorna temperatura
  }else{
    return 0;
  }
}

//Obtiene la humedad cada 5 segundos
int class_tasks::get_humidity( void ){
  if((millis() - timeHum) >= intervaloHum ){ //Intervalo de 5 segundos
    timeHum = millis(); //Guarda el tiempo actual
    int humidity = sensor.obtener_humedad(); //Obtiene humedad
    Serial.print("Humedad: ");
    Serial.println(humidity);
    return humidity; //Retorna humedad
  }else{
     return 0;
  }
}

//Obtiene la luminosidad cada 1 segundo
int class_tasks::get_brightness( void ){
  if((millis() - timeLdr) >= intervaloLdr){ //Intervalo de 1 segundo
    timeLdr = millis();  //Guarda el tiempo actual
    int brightness = map(sensor.obtener_luminosidad(), 0, 1000, 0, 100); //Mapea valores de luminosidad
    Serial.println("Luminosidad: " + String(brightness));
    return brightness; //retorna la luminosidad
  }else{ 
    return -1;
  }
}

//Obtiene el movimiento cada 1 segundo
int class_tasks::get_movement( void ){
  if((millis() - timeMov) >= intervaloMov){ //Intervalo de 1 segundo
    timeMov = millis();
    int isMov = sensor.obtener_movimiento(); //Obtiene valor de movimiento
    Serial.print("Hay movimiento: ");
    Serial.println(isMov);
    return isMov; //Retorna valor de movimiento
  }else{
    return -1;
  }
}

//Enciende el LED
void class_tasks::LED_ON( void ){
  actuator.EncenderLED();
}

//Apaga el LED
void class_tasks::LED_OFF( void ){
  actuator.ApagarLED();
}

//Enciende el buzzer
void class_tasks::Buzzer_ON( void ){
  for(int i =1;i<=5;i++)
  {
    actuator.EncenderBuzzer();
  }
}

//Apaga el buzzer
void class_tasks::Buzzer_OFF( void ){
  actuator.ApagarBuzzer();
}

//Imprime valores obtenidos en la LCD
void class_tasks::printData( int temp, int hum, int lum ){
  LCD.printLCD(temp, hum, lum);
}

void class_tasks::publish_MQTT( void ){
  if((millis() - timeMQTT) >= intervaloMQTT){ //Intervalo de 5 segundo
    mqtt.reconnect_MQTT ( );
    mqtt.publish_MQTT ( );
    timeMQTT = millis();  //Guarda el tiempo actual   
  }
}

void class_tasks::save_file( String accion, String advertencia ){
  
  if( ( millis() - timeDL ) >= intervaloDL ){
    MSD.create_json(accion, advertencia);
    timeDL = millis();
  }
}
