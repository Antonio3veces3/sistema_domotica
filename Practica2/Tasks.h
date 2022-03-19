class class_tasks{
  public:
    unsigned long timeTemp = 0;
    unsigned long timeHum = 0;
    unsigned long intervaloTemp = 5000;
    unsigned long intervaloHum = 7000;

  public:
    float get_temperature( void );
    float get_humidity( void );
};

float class_tasks::get_temperature( void ){
  if((millis() - timeTemp) >= intervaloTemp ){
    timeTemp = millis();
    float tempSensor = sensor.obtener_temperatura();
    Serial.print("Temperatura: ");
    Serial.println(tempSensor);
    return tempSensor;
  }else{
    return 0;
  }
}

float class_tasks::get_humidity( void ){
  if((millis() - timeHum) >= intervaloHum ){
    timeHum = millis();
    float humSensor = sensor.obtener_humedad();
    Serial.print("Humedad: ");
    Serial.println(humSensor);
    return humSensor;
  }else{
     return 0;
  }
}
