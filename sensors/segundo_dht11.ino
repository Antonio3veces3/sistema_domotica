#include <DHT.h>

DHT dht(D2, DHT11);

float f = 0.0;
float k = 0.0;
 
void setup() {
  Serial.begin(115200);
  Serial.println("Prueba del sensor DHT11");
  dht.begin();
}
 
void loop() {
  delay(2000);

  float t = dht.readTemperature();

  f = (t * 9/5) + 32;
  k =  t + 273.15;
 
  if (isnan(t)) {
    Serial.println("Falla al leer el sensor DHT11!");
    return;
  }
 
  // IMPRIMIR RESULTADO
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println("°C");
  Serial.print("Temperatura: ");
  Serial.print(f);
  Serial.println("°F");
  Serial.print("Temperatura: ");
  Serial.print(k);
  Serial.println("°K");
  Serial.println("----------------------");
  
}
