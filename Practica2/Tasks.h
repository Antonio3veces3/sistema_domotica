/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class class_tasks{

  public:   //Variables Públicas
    unsigned long timeTemp = 0;
    unsigned long timeHum = 0;
    unsigned long intervaloTemp = 5000;
    unsigned long intervaloHum = 5000;
    unsigned long timeLdr = 0;
    unsigned long intervaloLdr = 1000;
    unsigned long timeMov = 0;
    unsigned long intervaloMov = 1000;
    unsigned long timeDecision = 0;
    unsigned long intervaloDecision = 1000;

  public:   //Métodos Públicos
    int get_temperature(void);
    int get_humidity(void);
    int get_brightness(void);
    int get_movement(void);
    void LED_ON(void);
    void LED_OFF(void);
    void Buzzer_ON(void);
    void Buzzer_OFF(void);
    void decision(void);
    void printTempHumDate(int temp, int hum, String date);
    String get_date(void);
    void create_file(fs::FS &fs, const char * path, const char * message);
    void append_file( fs::FS &fs, const char * path, const char * message);
    String create_json_temp_hum(String date, int temp, int hum);
    String create_json_action(String date, String action);
    String create_json_warning(String date, String warning);
};


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODOS~~~~~~~~~~~~~~~~~~~~~~~*/

int class_tasks::get_temperature(void){
  if((millis() - timeTemp) >= intervaloTemp ){
    timeTemp = millis();
    float temperature = sensor.obtener_temperatura();
    Serial.print("Temperatura: ");
    Serial.println(temperature);
    return temperature;
  }else{
    return 0;
  }
}

int class_tasks::get_humidity(void){
  if((millis() - timeHum) >= intervaloHum ){
    timeHum = millis();
    float humidity = sensor.obtener_humedad();
    Serial.print("Humedad: ");
    Serial.println(humidity);
    return humidity;
  }else{
     return 0;
  }
}

int class_tasks::get_brightness(void){
  if((millis() - timeLdr) >= intervaloLdr){
    timeLdr = millis();
    //int bns = sensor.obtener_luminosidad();
    int brightness = map(sensor.obtener_luminosidad(), 0, 1000, 0, 100);
    Serial.println("Luminosidad: " + String(brightness));
    return brightness;
  }else{
    return -1;
  }
}

int class_tasks::get_movement(void){
  if((millis() - timeMov) >= intervaloMov){
    timeMov = millis();
    int isMov = sensor.obtener_movimiento();
    Serial.print("Hay movimiento: ");
    Serial.println(isMov);
    return isMov;
  }else{
    return -1;
  }
}

void class_tasks::LED_ON(void){
  actuadores.EncenderLED();
}
void class_tasks::LED_OFF(void){
  actuadores.ApagarLED();
}
void class_tasks::Buzzer_ON(void){
  
  for(int i =1;i<=5;i++)
  {
    actuadores.EncenderBuzzer();
    delay(2000);
  }
}

void class_tasks::Buzzer_OFF(void){
  actuadores.ApagarBuzzer();
}

void class_tasks::printTempHumDate(int temp, int hum, String date){
  control.imprimirLCD(temp, hum, date);
}

String class_tasks::get_date(void){
  return control.getDataTime();
}

void class_tasks::create_file(fs::FS &fs, const char * path, const char * message){
  control.createFile(fs, path, message);
}

void class_tasks::append_file(fs::FS &fs, const char * path, const char * message){
  control.appendFile(fs, path, message);
}

String class_tasks::create_json_temp_hum(String date, int temp, int hum){
  return control.crear_json_temp_hum(date, temp, hum);
}

String class_tasks::create_json_action(String date, String action){
  return control.crear_json_action( date, action);
}

String class_tasks::create_json_warning(String date, String warning){
  return control.crear_json_warning( date, warning);
}
