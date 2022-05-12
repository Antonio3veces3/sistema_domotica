/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class class_tasks{

  public: //Variables Públicas
    unsigned long timeTemp = 0;
    unsigned long timeHum = 0;
    unsigned long intervaloTemp = 5000; //Intervalo de tiempo temperatura
    unsigned long intervaloHum = 5000;  //Intervalo de tiempo humedad
    unsigned long timeLdr = 0;
    unsigned long intervaloLdr = 1000;  //Intervalo de tiempo sensor LDR
    unsigned long timeMov = 0;
    unsigned long intervaloMov = 1000;  //Intervalo de tiempo sensor PIR
    unsigned long intervaloMQTT = 5000, timeMQTT = 0;
    

  public: //Métodos Públicos
    int get_temperature(void);
    int get_humidity(void);
    int get_brightness(void);
    int get_movement(void);
    void LED_ON(void);
    void LED_OFF(void);
    void Buzzer_ON(void);
    void Buzzer_OFF(void);
    void printTempHumDate(int temp, int hum, String date);
    String get_date(void);
    void create_file(fs::FS &fs, const char * path, const char * message);
    void append_file( fs::FS &fs, const char * path, const char * message);
    String create_json_temp_hum(String date, int temp, int hum);
    String create_json_action(String date, String action);
    String create_json_warning(String date, String warning);
    void taskMQTT ( void );
};


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODOS~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//Obtiene la temperatura cada 5 segundos
int class_tasks::get_temperature(void){
  if((millis() - timeTemp) >= intervaloTemp ){ //Intervalo de 5 segundos
    timeTemp = millis(); //Guarda el tiempo actual
    float temperature = sensor.obtener_temperatura(); //Obtiene temperatura
    Serial.print("Temperatura: ");
    Serial.println(temperature);
    return temperature; //Retorna temperatura
  }else{
    return 0;
  }
}

//Obtiene la humedad cada 5 segundos
int class_tasks::get_humidity(void){
  if((millis() - timeHum) >= intervaloHum ){ //Intervalo de 5 segundos
    timeHum = millis(); //Guarda el tiempo actual
    float humidity = sensor.obtener_humedad(); //Obtiene humedad
    Serial.print("Humedad: ");
    Serial.println(humidity);
    return humidity; //Retorna humedad
  }else{
     return 0;
  }
}

//Obtiene la luminosidad cada 1 segundo
int class_tasks::get_brightness(void){
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
int class_tasks::get_movement(void){
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
void class_tasks::LED_ON(void){
  actuator.EncenderLED();
}

//Apaga el LED
void class_tasks::LED_OFF(void){
  actuator.ApagarLED();
}

//Enciende el buzzer
void class_tasks::Buzzer_ON(void){
  for(int i =1;i<=5;i++)
  {
    actuator.EncenderBuzzer();
  }
}

//Apaga el buzzer
void class_tasks::Buzzer_OFF(void){
  actuator.ApagarBuzzer();
}

//Imprime valores obtenidos en la LCD
void class_tasks::printTempHumDate(int temp, int hum, String date){
  lcd.printLCD(temp, hum, date);
}

//Obtiene los valores de la fecha y hora
String class_tasks::get_date(void){
  return RTC.getDataTime();
}

void class_tasks::taskMQTT( void ){

  if((millis() - timeMQTT) >= intervaloMQTT){ //Intervalo de 1 segundo
    mqtt.reconnect_MQTT ( );
    mqtt.publish_MQTT ( );
    timeMQTT = millis();  //Guarda el tiempo actual   
  }else{ 
    return -1;
  }
}

/*//Crea el JSON con la fecha, hora, temperatura y humedad
String class_tasks::create_json_temp_hum(String date, int temp, int hum){
  return control.crear_json_temp_hum(date, temp, hum);
}

//Crea el JSON con fecha, hora y las acciones realizadas
String class_tasks::create_json_action(String date, String action){
  return control.crear_json_action( date, action);
}

//Crea el JSON con la fecha, hora y advertencias emitidas
String class_tasks::create_json_warning(String date, String warning){
  return control.crear_json_warning( date, warning);
}*/
