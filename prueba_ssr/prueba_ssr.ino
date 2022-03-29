void setup() {
  Serial.begin(115200);
  pinMode(12, OUTPUT); //Pin 5, D1 ESP8266, D5 Pin 5 ESP32
}

void loop() {
  digitalWrite(12,LOW);  
  delay(1000);
  digitalWrite(12,HIGH);  
  delay(1000);
}
