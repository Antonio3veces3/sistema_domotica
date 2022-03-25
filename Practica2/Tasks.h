class class_tasks{
  public:
    unsigned long timeTemp = 0;
    unsigned long timeHum = 0;
    unsigned long intervaloTemp = 5000;
    unsigned long intervaloHum = 7000;
    unsigned long timeLdr = 0;
    unsigned long intervaloLdr = 2000;

  public:
    float get_temperature( void );
    float get_humidity( void );
    int get_brightness (void);
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
