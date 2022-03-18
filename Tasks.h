#define INTERVALO_TEMP 5000
#define INTERVALO_HUM 7000

class class_tasks{
  public:
    unsigned long time_1 = 0;
    unsigned long time_2 = 0;
    unsigned long currentMillis = 0;

  public:
    float get_temperature();
    float get_humidity();
};

//each 5 seconds
float class_tasks::get_temperature(){
  if( currentMillis > (time_1 + INTERVALO_TEMP) ){
    time_1 = currentMillis;
    Serial.println(" 5 segundos");
    return sensor.obtener_temperatura();
  }
}
//each 7 seconds
float class_tasks::get_humidity(){

  if( currentMillis > (time_2 + INTERVALO_HUM) ){
    time_2 = currentMillis;
    Serial.println(" 7 segundos");
    return sensor.obtener_humedad();
  }
}

