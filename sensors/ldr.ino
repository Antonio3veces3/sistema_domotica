// Pin donde se conectan los leds
int pinLedR = 5;
int pinLedA = 4;
int pinLedV = 14;
// Pin analogico de entrada para el LDR
int pinLDR = 0;
 
// Variable donde se almacena el valor del LDR
int valorLDR = 0;  
 
void setup()
{
  Serial.begin(115200);
  
  // Configuramos como salidas los pines donde se conectan los led
  pinMode(pinLedR, OUTPUT);
  pinMode(pinLedA, OUTPUT);
  pinMode(pinLedV, OUTPUT);
  
}
 
void loop()
{
  // Apagar todos los leds siempre que se inicia el ciclo
  digitalWrite(pinLedR, LOW);
  digitalWrite(pinLedA, LOW);
  digitalWrite(pinLedV, LOW);
 
  // Guardamos el valor leido del ADC en una variable
  // El valor leido por el ADC (voltaje) aumenta de manera directamente proporcional
  // con respecto a la luz percibida por el LDR
  valorLDR= analogRead(pinLDR);
  
  // Devolver el valor leido a nuestro monitor serial en el IDE de Arduino
  Serial.println(valorLDR);
 
  // Encender los leds apropiados de acuerdo al valor de ADC
  if(valorLDR < 820)
  {
    digitalWrite(pinLedR, HIGH);
  }
  if(valorLDR > 830 && valorLDR < 999)
  {
    digitalWrite(pinLedA, HIGH);
  }
  if(valorLDR > 1000)
  {
    digitalWrite(pinLedV, HIGH);
  }
  // Esperar unos milisegundos antes de actualizar
  delay(2000);
}
