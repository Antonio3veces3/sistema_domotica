class class_tasks{
  public:
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

  public:
    float get_temperature( void );
    float get_humidity( void );
    int get_brightness (void);
    int get_movement ( void );
    void LED_ON (void);
    void LED_OFF (void);
    void Buzzer_ON (void);
    void Buzzer_OFF (void);
    void decision (void);
    void printTempHum (float temp, float hum);
};

float class_tasks::get_temperature( void ){
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

float class_tasks::get_humidity( void ){
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
    int brightness = sensor.obtener_luminosidad();
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


void class_tasks::LED_ON (void){
  actuadores.EncenderLED();
}
void class_tasks::LED_OFF (void){
  actuadores.ApagarLED();
}
void class_tasks::Buzzer_ON (void){
  
  for(int i =1;i<=5;i++)
  {
    actuadores.EncenderBuzzer();
    delay(2000);
  }
  
}

void class_tasks::Buzzer_OFF( void ){
  actuadores.ApagarBuzzer();
}

void class_tasks::printTempHum (float temp, float hum){
  actuadores.imprimirLCD(temp, hum);
}
